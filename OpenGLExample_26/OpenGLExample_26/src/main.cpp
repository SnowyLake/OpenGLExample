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
#include "../include/window_manager.h"
#include "../include/builtin_obj.h"
#include "../include/framebuffers_manager.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "assimp-vc142-mt.lib")

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
const std::string EXAMPLE_NAME = "FrameBuffers";

int main()
{
    WindowManager windowMgr(SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME, nullptr, nullptr, true);
    windowMgr.SetCallback();

    //configure global OpenGL state
    //-----------------------------
    glEnable(GL_DEPTH_TEST);

    //shaders
    //-------
    GLShader defaultShader("shaders/framebuffers.vert", "shaders/framebuffers.frag");
    GLShader screenShader("shaders/screen.vert", "shaders/screen.frag");

    //scene objects
    //-------------
    std::vector<BuiltInObject> cubes(2, BuiltInObject(BIOType::OBJ_CUBE));
    BuiltInObject plane(BIOType::OBJ_PLANE);

    //set framebuffers
    //----------------
    FramebuffersManager FBMgr(SCR_WIDTH, SCR_HEIGHT);
    FBMgr.CreateScreenQuad();

    //shader config
    //-------------
    defaultShader.Use();
    defaultShader.SetInt("texture1", 0);
    screenShader.Use();
    screenShader.SetInt("screenTexture", 0);

    //window config
    //-------------
    glfwSetWindowPos(windowMgr.window, 300, 100);
    glfwShowWindow(windowMgr.window);
    
    //draw as wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //render loop
    //-----------
    while (!glfwWindowShouldClose(windowMgr.window))
    {
        windowMgr.ProcessInput();

        //render
        //------
        //bind to framebuffer and draw scene as we normally would to color texture
        FBMgr.Bind();
        glEnable(GL_DEPTH_TEST);

        //make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
        //first
        model = glm::translate(model, glm::vec3(-1.0f, -1.001f, -1.0f));
        cubes.at(0).BuiltInObjRender(defaultShader, model, view, projection, true);
        //second
        model = glm::translate(model, glm::vec3(2.0f, -1.0001f, 0.0f));
        cubes.at(1).BuiltInObjRender(defaultShader, model, view, projection, true);
        glDisable(GL_CULL_FACE);    //close Face culling

        //now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        FBMgr.UnBind();
        glDisable(GL_DEPTH_TEST);   //disable depth test so screen-space quad isn't discarded due to depth test.
        //clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);
        FBMgr.Render(screenShader);

        glfwSwapBuffers(windowMgr.window);
        glfwPollEvents();
    }

    for (auto& i : cubes)
    {
        i.Delete();
    }
    plane.Delete();
    FBMgr.Delete();

    glfwTerminate();
    return 0;
}

