#pragma once
static struct PostProcessShaders
{
	static const char* Inversion;		//¸ºÆ¬
	static const char* Grayscale;		//»Ò¶È»¯
	static const char* Sharpen;			//Èñ»¯
	static const char* Blur;			//Ä£ºý
	static const char* Edge_Detection;	//±ßÔµ¼ì²â
};
const char* PostProcessShaders::Inversion		= "shaders/post_process/Inversion.frag";
const char* PostProcessShaders::Grayscale		= "shaders/post_process/Grayscale.frag";
const char* PostProcessShaders::Sharpen			= "shaders/post_process/Sharpen.frag";
const char* PostProcessShaders::Blur			= "shaders/post_process/Blur.frag";
const char* PostProcessShaders::Edge_Detection  = "shaders/post_process/Edge_Detection.frag";