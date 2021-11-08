#pragma once
static struct PostProcessShaders
{
	static const char* DefaultVert;		//默认vert
	static const char* DefaultFrag;		//默认frag
	static const char* Inversion;		//负片
	static const char* Grayscale;		//灰度化
	static const char* Sharpen;			//锐化
	static const char* Blur;			//模糊
	static const char* Edge_Detection;	//边缘检测
};
const char* PostProcessShaders::DefaultVert		= "shaders/post_process/DefaultVert.vert";
const char* PostProcessShaders::DefaultFrag		= "shaders/post_process/DefaultFrag.frag";
const char* PostProcessShaders::Inversion		= "shaders/post_process/Inversion.frag";
const char* PostProcessShaders::Grayscale		= "shaders/post_process/Grayscale.frag";
const char* PostProcessShaders::Sharpen			= "shaders/post_process/Sharpen.frag";
const char* PostProcessShaders::Blur			= "shaders/post_process/Blur.frag";
const char* PostProcessShaders::Edge_Detection  = "shaders/post_process/Edge_Detection.frag";