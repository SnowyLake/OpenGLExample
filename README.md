# My OpenGLExample
![](https://img.shields.io/badge/License-MIT-write.svg)  ![](https://img.shields.io/badge/Language-C++-darkblue.svg)  ![](https://img.shields.io/badge/Language-GLSL-darkblue.svg) ![](https://img.shields.io/badge/IDE-Visual_Studio-purple.svg) ![](https://img.shields.io/badge/API-OpenGL_3.3-blue.svg)  
  [![](https://img.shields.io/badge/UI_Library-Dear_ImGui-orange.svg)](https://github.com/ocornut/imgui)  [![](https://img.shields.io/badge/API_Library-GLAD-yellow.svg)](https://github.com/Dav1dde/glad)  [![](https://img.shields.io/badge/API_Library-GLFW-yellow.svg)](https://www.glfw.org/download.html)  [![](https://img.shields.io/badge/Math_Library-GLM-yellow.svg)](https://glm.g-truc.net/0.9.8/index.html)  [![](https://img.shields.io/badge/Load_Library-stb__image-yellow.svg)](https://github.com/nothings/stb)  [![](https://img.shields.io/badge/Load_Library-Assimp-yellow.svg)](https://github.com/assimp/assimp)

#### My OpenGL example programs, learn by [LearnOpenGL-CN](https://learnopengl-cn.github.io/).     
- [中文](README-zh.md)      
- [English](README.md)


----
## Example Directory
> **01 ~ 27** is developed using Visual Studio 2019   
> **28 ~ later** has been upgraded to Visual Studio 2022

**Example_01:** Create  a window    
**Example_02:** Draw a triangle     
**Example_03:** Draw a rectangle    
**Example_04:** Draw two triangle    
**Example_05:** Draw two triangle,use different VAO and VBO for their data    
**Example_06:** Draw a yellow triangle and an orange triangle, use two shader programs, the second using a different fragment shader    
**Example_07:** Draw a red triangle that can change color    
**Example_08:** Draw a triangle has three colors    
**Example_09:** Draw a three colors triangle use shader class    
**Example_10:** Draw a wooden box with texture    
**Example_11:** Draw a wooden box with two textures    
**Example_12:** Draw a wooden box with two textures, and can use the up and down keys to change the textures visibility    
**Example_13:** Draw two wooden boxes with two textures, the first one rotates along X, Y and Z axes at the same time and can be moved by direction keys；The second one scales regularly in the upper right corner    
**Example_14:** 
>test1: Draw a 2D wooden box lying on the ground  
test2: Draw a rotating 3D wooden box     
test3: Draw twenty rotating 3D wooden boxes  
test4: Draw twenty 3D wooden boxes, and only the multiple of three wooden boxes rotation

**Example_15:** 
>test1: Create a camera that moves around the scene over time  
test2: Create a camera that can move freely

**Example_16:** Create a lighting scene    
**Example_17:** Phong Lighting Model    
**Example_18:** Phong Lighting Model, A moving point light source that can change color    
**Example_19:** Create a wooden box has diffuse map and specular map    
**Example_20:** Create a spotlight    
**Example_21:** Create a scene who has a directional light, four point lights and a spotlight     
**Example_22:** Load a nanosuit model with Assimp, and refactor the codes to be Object-Oriented    
**Example_23:** Depth Testing, refactor some codes    
**Example_24:** Stencil Testing, use ```#pragma comment``` to link library    
**Example_25:** Blending and Face culling    
**Example_26:** Use Framebuffers and add PostProcessShaders Library    
**Example_27:** Create reflection and refraction shaders, add reflection texture in nanosuit    
**Example_28:** Draw four cubes of different colors using UBO    

----
## Notice or Warning
- **warning:** Examples 15 to 26 have a serious bug in the gl_camera.h, which results in the wrong orientation, such as the y axis being down in the actual program.   
This bug was fixed in example 27 and the following examples, but it has not been fixed in 15 ~ 26. Although the screen is displayed normally through operations such as coordinate transformation and texture inversion, please carefully refer to the relevant code.