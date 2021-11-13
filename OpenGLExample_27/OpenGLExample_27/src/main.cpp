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
#include "../include/model.h"
#include "../include/builtin_obj.h"
#include "../include/window_manager.h"
#include "../include/skybox_manager.h"
#include "../include/framebuffers_manager.h"
#include "../shaders/post_process/post_process_shaders.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "assimp-vc142-mt.lib")

//setting
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;
const std::string EXAMPLE_NAME = "Skybox";
//camera
GLCamera camera(glm::vec3(0.0f, 10.0f, 20.0f));

//skybox
std::vector<std::string> faces = {
    "res/skybox/right.jpg",
    "res/skybox/left.jpg",
    "res/skybox/top.jpg",
    "res/skybox/bottom.jpg",
    "res/skybox/front.jpg",
    "res/skybox/back.jpg"
};

int main()
{
    //create window
    WindowManager windowMgr(SCR_WIDTH, SCR_HEIGHT, EXAMPLE_NAME, nullptr, nullptr, true);
    windowMgr.SetCallback();

    //create framebuffers
    //----------------
    FramebuffersManager FBMgr(windowMgr.window);
    FBMgr.CreateScreenQuad(1);

    //configure global OpenGL state
    //-----------------------------
    glEnable(GL_DEPTH_TEST);

    //shaders
    //-------
    GLShader reflectionShader("shaders/reflection.vert", "shaders/reflection.frag");
    GLShader refractionShader("shaders/refraction.vert", "shaders/refraction.frag");
    GLShader defaultShader("shaders/default.vert", "shaders/default.frag");
    GLShader skyboxShader("shaders/skybox.vert", "shaders/skybox.frag");
    GLShader screenShader(PostProcessShaders::DefaultVert, PostProcessShaders::DefaultFrag);

    GLShader nanosuitReflShader("shaders/nanosuit_refl.vert", "shaders/nanosuit_refl.frag");
    
    //shader config
    //-------------
    reflectionShader.Use();
    reflectionShader.SetInt("skyboxTex", 0);
    refractionShader.Use();
    refractionShader.SetInt("skyboxTex", 0);
    defaultShader.Use();
    defaultShader.SetInt("texture1", 0);
    skyboxShader.Use();
    skyboxShader.SetInt("skyboxTex", 0);
    screenShader.Use();
    screenShader.SetInt("screenTexture", 0);

    //nanosuitReflShader.Use();
    

    //scene objects
    //-------------
    BuiltInObject cubeWithNormal(BIOType::OBJ_CUBE_WITH_NORMAL);
    BuiltInObject cube(BIOType::OBJ_CUBE);

    Model NanoSuit("res/nanosuit/nanosuit.obj");
    Model NanoSuitRefl("res/nanosuit_reflection/nanosuit.obj");

    //create skybox
    
    SkyboxManager skyboxMgr(faces);

    //draw as wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    windowMgr.Show(300, 100);

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
        //reflectionShader.Use();
        auto model = glm::mat4(1.0f);
        auto view = camera.GetViewMatrix();
        int _width, _height; glfwGetFramebufferSize(windowMgr.window, &_width, &_height);
        auto projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(_width) / static_cast<float>(_height), 0.1f, 100.0f);

        //refraction
        //cube
        refractionShader.Use();
        model = glm::translate(model, glm::vec3(-4.0f, 10.0f, 5.0f));
        auto normalMatrix = glm::transpose(glm::inverse(model));
        refractionShader.SetMat4("normal_matrix", normalMatrix);
        refractionShader.SetVec3("cameraPos", camera.Position);
        cubeWithNormal.BuiltInObjRender(refractionShader, model, view, projection, true, skyboxMgr.GetTexture(), GL_TEXTURE_CUBE_MAP);
        //nanosuit
        refractionShader.Use();
        model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
        normalMatrix = glm::transpose(glm::inverse(model));
        refractionShader.SetMat4("normal_matrix", normalMatrix);
        refractionShader.SetVec3("cameraPos", camera.Position);
        NanoSuit.Render(refractionShader, model, view, projection, true);

        //reflection
        //cube
        reflectionShader.Use();
        model = glm::translate(model, glm::vec3(4.0f, 10.0f, 5.0f));
        normalMatrix = glm::transpose(glm::inverse(model));
        reflectionShader.SetMat4("normal_matrix", normalMatrix);
        reflectionShader.SetVec3("cameraPos", camera.Position);
        cubeWithNormal.BuiltInObjRender(reflectionShader, model, view, projection, true, skyboxMgr.GetTexture(), GL_TEXTURE_CUBE_MAP);
        //nanosuit
        model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
        normalMatrix = glm::transpose(glm::inverse(model));
        reflectionShader.SetMat4("normal_matrix", normalMatrix);
        reflectionShader.SetVec3("cameraPos", camera.Position);
        NanoSuit.Render(reflectionShader, model, view, projection, true);
        
        //nanosuit_reflection
        nanosuitReflShader.Use();
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
        normalMatrix = glm::transpose(glm::inverse(model));
        nanosuitReflShader.SetMat4("normal_matrix", normalMatrix);
        nanosuitReflShader.SetVec3("cameraPos", camera.Position);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxMgr.GetTexture());
        nanosuitReflShader.SetInt("skyboxTex", 4);
        NanoSuitRefl.Render(nanosuitReflShader, model, view, projection, true);

        //glEnable(GL_CULL_FACE);     //open Face culling
        //defaultShader.Use();
        //cube.BuiltInObjRender(defaultShader, model, view, projection, true);
        //glDisable(GL_CULL_FACE);    //close Face culling

        //skybox render
        glDepthFunc(GL_LEQUAL);
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        skyboxMgr.Rneder(skyboxShader, view, projection);
        glDepthFunc(GL_LESS);

        //now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        FBMgr.UnBind();
        glDisable(GL_DEPTH_TEST);   //disable depth test so screen-space quad isn't discarded due to depth test.
        //clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);

        //create transformations
        auto transform = glm::mat4(1.0f); //make sure to initialize matrix to identity matrix first
        FBMgr.Render(screenShader, 1, transform);

        glfwSwapBuffers(windowMgr.window);
        glfwPollEvents();
    }

    cube.Delete();
    FBMgr.Delete();
    skyboxMgr.Delete();

    glfwTerminate();
    return 0;
}

