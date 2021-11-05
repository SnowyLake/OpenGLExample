#include <map>
#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gl_camera.h>
#include <gl_shader.h>
#include "../include/create_window.h"
#include "../include/builtin_obj.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "assimp-vc142-mt.lib")

//setting
const unsigned int SCR_WIDTH  = 1200;
const unsigned int SCR_HEIGHT = 800;
const std::string EXAMPLE_NAME = "Blending";

//vegetation pos
std::vector<glm::vec3> vegetationsPos = {
    glm::vec3(-1.5f, -1.0f,  0.51f),
    glm::vec3( 1.5f, -1.0f,  0.51f),
    glm::vec3( 0.0f, -1.0f,  0.70f),
    glm::vec3(-0.3f, -1.0f, -2.30f),
    glm::vec3( 0.5f, -1.0f, -0.60f)
};
//windows pos
std::vector<glm::vec3> windowsPos = {
    glm::vec3(-1.5f, -1.0f,  0.55f),
    glm::vec3(1.5f, -1.0f,  0.51f),
    glm::vec3(0.0f, -1.0f,  0.70f),
    glm::vec3(-0.3f, -1.0f, -2.30f),
    glm::vec3(0.5f, -1.0f, -0.60f)
};
int main()
{
    WindowManager windowMgr(SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME, nullptr, nullptr, true);
    windowMgr.SetCallback();

    //configure global OpenGL state
    //-----------------------------
    glEnable(GL_DEPTH_TEST);                            //开启深度测试
    glDepthFunc(GL_LESS);                               //在片段深度值小于缓冲深度值时通过测试
    //glEnable(GL_STENCIL_TEST);                         //开启模板测试
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);               //禁用模板缓冲写入，参考值为1，掩码为0xFF
    //glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);         //当两项测试未全部通过的，仅保留模板缓冲值，当全部通过时，将存储的模板值设置为参考值
    glEnable(GL_BLEND);                                 //开启混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //使用源颜色向量的alpha作为源因子，使用1−alpha作为目标因子
    

    //build and compile shaders
    //-------------------------
    GLShader defaultShader("shaders/default_shader.vert", "shaders/default_shader.frag");

    //scene objects
    //-------------
    std::vector<BuiltInObject> cubes(2, BuiltInObject(BIOType::OBJ_CUBE));
    std::vector<BuiltInObject> vegetations(5, BuiltInObject(BIOType::OBJ_VEGETATION));
    std::vector<BuiltInObject> windows(5, BuiltInObject(BIOType::OBJ_WINDOW));
    BuiltInObject plane(BIOType::OBJ_PLANE);

    //shader config
    //-------------
    defaultShader.Use();
    defaultShader.SetInt("texture1", 0);

    //window config
    //-------------
    glfwSetWindowPos(windowMgr.window, 300, 100);
    glfwShowWindow(windowMgr.window);

    while(!glfwWindowShouldClose(windowMgr.window))
    {
        windowMgr.ProcessInput();

        //sort windows before rendering
        std::map<float, glm::vec3> sorted;
        for (size_t i = 0; i < windows.size(); i++)
        {
            float distance = glm::length(camera.Position - windowsPos.at(i));
            sorted.emplace(distance, windowsPos.at(i));
        }

        //set color
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //set MVP Matrix
        defaultShader.Use();
        auto model = glm::mat4(1.0f);
        auto view = camera.GetViewMatrix();
        int _width, _height; glfwGetFramebufferSize(windowMgr.window, &_width, &_height);
        auto projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(_width) / static_cast<float>(_height), 0.1f, 100.0f);

        //plane render
        plane.BuiltInObjRender(defaultShader, model, view, projection);
        //cube render
        glEnable(GL_CULL_FACE);     //open Face culling
        //两种剔除正面的方案
        //glFrontFace(GL_CW);       //告诉OpenGL现在顺时针顺序代表的是正向面
        //glCullFace(GL_FRONT);     //只剔除正向面
        //first
        model = glm::translate(model, glm::vec3(-1.0f, -1.001f, -1.0f));
        cubes.at(0).BuiltInObjRender(defaultShader, model, view, projection, true);
        //second
        model = glm::translate(model, glm::vec3(2.0f, -1.0001f, 0.0f));
        cubes.at(1).BuiltInObjRender(defaultShader, model, view, projection, true);
        glDisable(GL_CULL_FACE);    //close Face culling

        //vegetation
        for(size_t i = 0; i < vegetations.size(); i++)
        {
            model = glm::translate(model, vegetationsPos.at(i));
            for(size_t j = 0; j < 6; j++)
            {
                model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                vegetations.at(i).BuiltInObjRender(defaultShader, model, view, projection);
            }
            model = glm::mat4(1.0f);
        }
        //windows
        for (auto iter = sorted.rbegin(); iter != sorted.rend(); iter++) 
        {
            int count = 0;
            model = glm::translate(model, iter->second);
            windows.at(count++).BuiltInObjRender(defaultShader, model, view, projection, true);
        }

        glfwSwapBuffers(windowMgr.window);
        glfwPollEvents();
    }

    for(auto& i : cubes)
    {
        i.DeleteVAO();
        i.DeleteBuffers();
    }
    for(auto& i : vegetations)
    {
        i.DeleteVAO();
        i.DeleteBuffers();
    }
    for (auto& i : windows)
    {
        i.DeleteVAO();
        i.DeleteBuffers();
    }
    plane.DeleteVAO();
    plane.DeleteBuffers();

    glfwTerminate();
    return 0;
}

