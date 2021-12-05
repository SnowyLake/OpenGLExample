#pragma once
struct PostProcessShaders
{
	static const char* DefaultVert;		//默认vert
	static const char* DefaultFrag;		//默认frag
	static const char* Inversion;		//负片
	static const char* Grayscale;		//灰度化
	static const char* Sharpen;			//锐化
	static const char* Blur;			//模糊
	static const char* Edge_Detection;	//边缘检测

};

inline const char* PostProcessShaders::DefaultVert			= "res/builtin/shaders/post_process/DefaultVert.vert";
inline const char* PostProcessShaders::DefaultFrag			= "res/builtin/shaders/post_process/DefaultFrag.frag";
inline const char* PostProcessShaders::Inversion			= "res/builtin/shaders/post_process/Inversion.frag";
inline const char* PostProcessShaders::Grayscale			= "res/builtin/shaders/post_process/Grayscale.frag";
inline const char* PostProcessShaders::Sharpen				= "res/builtin/shaders/post_process/Sharpen.frag";
inline const char* PostProcessShaders::Blur					= "res/builtin/shaders/post_process/Blur.frag";
inline const char* PostProcessShaders::Edge_Detection		= "res/builtin/shaders/post_process/Edge_Detection.frag";
