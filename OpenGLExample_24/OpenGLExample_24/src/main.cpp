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
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

const std::string EXAMPLE_NAME = "Stencil Testing";

int main()
{
    WindowManager windowMgr(SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME, nullptr, nullptr, true);
    windowMgr.SetCallback();

    //configure global OpenGL state
    //-----------------------------
    glEnable(GL_DEPTH_TEST);                     //开启深度测试
    glDepthFunc(GL_LESS);                        //在片段深度值小于缓冲的深度值时通过测试
    glEnable(GL_STENCIL_TEST);                   //开启模板测试
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);         //禁用模板缓冲写入，参考值为1，掩码为0xFF
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);   //当两项测试未全部通过时，仅保留模板缓冲值；当全部通过时，将存储的模板值设置为参考值

    //build and compile shaders
    //-------------------------
    GLShader defaultShader("shader/default_shader.vert", "shader/default_shader.frag");
    GLShader objectOutliningShader("shader/object_outlining_shader.vert", "shader/object_outlining_shader.frag");

    //scene objects
    //-------------
    std::vector<BuiltInObject> cubes =
    {
        BuiltInObject(BIOType::OBJ_CUBE),
        BuiltInObject(BIOType::OBJ_CUBE)
    };
    BuiltInObject plane(BIOType::OBJ_PLANE);

    //shader configuration
    //--------------------
    defaultShader.Use();
    defaultShader.SetInt("texture1", 0);

    //window configuration
    //--------------------
    glfwSetWindowPos(windowMgr.window, 300, 100);
    glfwShowWindow(windowMgr.window);

    //render loop
    //-----------
    while(!glfwWindowShouldClose(windowMgr.window))
    {
        windowMgr.SetPerFrameTimeLogic();
        windowMgr.ProcessInput();
        
        //render
        //------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //set MVP matrix value
        auto model = glm::mat4(1.0f);
        auto view = camera.GetViewMatrix();
        int  width, height; glfwGetFramebufferSize(windowMgr.window, &width, &height);	//When the window scale is changed, the render scale stays the same
        auto projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

        //draw plane as normal, but don't write the plane to the stencil buffer, we only care about the containers. 
        //We set its mask to 0x00 to not write to the stencil buffer.
        glStencilMask(0x00);    //关闭模板缓冲写入
        //plane render
        plane.BuiltInObjRender(defaultShader, model, view, projection);

        //1st. render pass: 
        //draw objects as normal, writing to the stencil buffer
        //-----------------------------------------------------------------------
        glStencilFunc(GL_ALWAYS, 1, 0xFF);      //所有的片段都可以通过模板测试，参考值为1，掩码为0xFF
        glStencilMask(0xFF);                    //启用模板缓冲写入
        //cube render
        //first
        model = glm::translate(model, glm::vec3(-1.0f, -1.001f, -1.0f));
        cubes.at(0).BuiltInObjRender(defaultShader, model, view, projection, true);
        //second
        model = glm::translate(model, glm::vec3(2.0f, -1.0001f, 0.0f));
        cubes.at(1).BuiltInObjRender(defaultShader, model, view, projection, true);

        //2nd. render pass: 
        //now draw slightly scaled versions of the objects, this time disabling stencil writing.
        //Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn,
        //thus only drawing the objects' size differences, making it look like borders.
        //-----------------------------------------------------------------------------------------------------------
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);    //之有不等于(GL_NOTEQUAL)1的片段可以通过模板测试，参考值为1，掩码为0xFF
        glStencilMask(0x00);                    //禁止模板缓冲的写入
        glDisable(GL_DEPTH_TEST);               //禁用深度测试，防止边框被地板覆盖
        //outline render
        float outlineScaleValue = 1.05f;
        //first
        model = glm::translate(model, glm::vec3(-1.0f, -1.001f, -1.0f));
        model = glm::scale(model, glm::vec3(outlineScaleValue, outlineScaleValue, outlineScaleValue));
        cubes.at(0).BuiltInObjRender(objectOutliningShader, model, view, projection, true);
        //second
        model = glm::translate(model, glm::vec3(2.0f, -1.0001f, 0.0f));
        model = glm::scale(model, glm::vec3(outlineScaleValue, outlineScaleValue, outlineScaleValue));
        cubes.at(1).BuiltInObjRender(objectOutliningShader, model, view, projection, true);
        glStencilMask(0xFF);                    //启用模板缓冲写入
        glStencilFunc(GL_ALWAYS, 0, 0xFF);      //所有的片段都可以通过模板测试，参考值为0，掩码为0xFF
        glEnable(GL_DEPTH_TEST);                //启用深度测试

        glfwSwapBuffers(windowMgr.window);
        glfwPollEvents();
    }
    for(auto& i : cubes)
    {
        i.DeleteVAO();
        i.DeleteBuffers();
    }
    plane.DeleteVAO();
    plane.DeleteBuffers();

    glfwTerminate();
    return 0;
}

