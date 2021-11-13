# My OpenGLExample
![](https://img.shields.io/badge/License-MIT-write.svg)  ![](https://img.shields.io/badge/Language-C++-darkblue.svg)  ![](https://img.shields.io/badge/Language-GLSL-darkblue.svg) ![](https://img.shields.io/badge/IDE-Visual_Studio-purple.svg) ![](https://img.shields.io/badge/API-OpenGL_3.3-blue.svg)  
  [![](https://img.shields.io/badge/UI_Library-Dear_ImGui-orange.svg)](https://github.com/ocornut/imgui)  [![](https://img.shields.io/badge/API_Library-GLAD-yellow.svg)](https://github.com/Dav1dde/glad)  [![](https://img.shields.io/badge/API_Library-GLFW-yellow.svg)](https://www.glfw.org/download.html)  [![](https://img.shields.io/badge/Math_Library-GLM-yellow.svg)](https://glm.g-truc.net/0.9.8/index.html)  [![](https://img.shields.io/badge/Load_Library-stb__image-yellow.svg)](https://github.com/nothings/stb)  [![](https://img.shields.io/badge/Load_Library-Assimp-yellow.svg)](https://github.com/assimp/assimp)

#### 我在学习 [LearnOpenGL-CN](https://learnopengl-cn.github.io/) 的过程中编写的一些示例程序.      
- [中文](README-zh.md)      
- [English](README.md)

----
## 示例目录
> **01 ~ 27** 使用 Visual Studio 2019 开发   
> **28 之后** 已升级至 Visual Studio 2022

**Example_01:** 创建一个窗口    
**Example_02:** 绘制一个三角形     
**Example_03:** 绘制一个矩形    
**Example_04:** 绘制两个三角形    
**Example_05:** 使用不同的VAO和VBO绘制两个三角形    
**Example_06:** 使用两个着色器程序绘制一个黄色的三角形和一个橙色的三角形，第二个着色器程序使用了不同的片元着色器    
**Example_07:** 绘制一个可以改变颜色的三角形    
**Example_08:** 绘制一个三角形，将三个顶点设置为红黄蓝三色并进行插值    
**Example_09:** 使用自定义类gl_shader绘制三个三角形    
**Example_10:** 绘制一个包含纹理的木箱    
**Example_11:** 绘制一个包含两种纹理的木箱    
**Example_12:** 绘制一个包含两种纹理的木箱，并可以使用上下键控制纹理的透明度    
**Example_13:** 绘制两个包含两种纹理的木箱，第一个木箱可以同时沿X, Y, Z轴旋转，可以通过方向键移动; 第二个木箱在右上角有规律缩放      
**Example_14:** 
>test1: 绘制一个躺在地上的2D木箱    
test2: 绘制一个旋转中的3D木箱    
test3: 绘制二十个旋转中的3D木箱     
test4: 绘制二十个的3D木箱，并且只有编号是3的倍数的木箱才会旋转

**Example_15:** 
>test1: 创建一个会随着时间的推移在场景周围移动的摄像机    
test2: 创建一个可以自由移动的摄像机

**Example_16:** 创建了一个光照场景    
**Example_17:** 冯氏光照模型    
**Example_18:** 冯氏光照模型, 和一个可以改变颜色的移动点光源    
**Example_19:** 创建一个有漫反射贴图和高光贴图的木箱    
**Example_20:** 创建一个聚光光源    
**Example_21:** 创建一个存在一个定向光源，四个点光源和一个聚光光源的场景       
**Example_22:** 使用Assimp加载纳米服模型，并将代码以面向对象的模式重构    
**Example_23:** 深度测试，重构部分代码    
**Example_24:** 模板测试, 使用 ```#pragma comment``` 来链接库    
**Example_25:** 混合和面剔除    
**Example_26:** 使用帧缓冲并添加PostProcessShaders（后处理）库    
**Example_27:** 创建反射和折射着色器，在纳米服模型中添加反射纹理    
**Example_28:** 使用UBO绘制了四个不同颜色的立方体    

----
## 通知或警告
- **警告：** 示例15 ~ 26的gl_camera.h中含有严重bug，会导致方向错误，比如实际程序中的y轴是朝下的。 
在示例27及之后的示例中修复了这个bug，但在15 ~ 26中还尚未修复，虽然通过如坐标变换和纹理反向等操作使画面正常显示，但相关部分的代码请慎重参考。