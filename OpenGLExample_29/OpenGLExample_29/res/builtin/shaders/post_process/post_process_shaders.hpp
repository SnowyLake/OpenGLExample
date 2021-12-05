#pragma once
struct PostProcessShaders
{
	static const char* DefaultVert;		//Ĭ��vert
	static const char* DefaultFrag;		//Ĭ��frag
	static const char* Inversion;		//��Ƭ
	static const char* Grayscale;		//�ҶȻ�
	static const char* Sharpen;			//��
	static const char* Blur;			//ģ��
	static const char* Edge_Detection;	//��Ե���

};

inline const char* PostProcessShaders::DefaultVert			= "res/builtin/shaders/post_process/DefaultVert.vert";
inline const char* PostProcessShaders::DefaultFrag			= "res/builtin/shaders/post_process/DefaultFrag.frag";
inline const char* PostProcessShaders::Inversion			= "res/builtin/shaders/post_process/Inversion.frag";
inline const char* PostProcessShaders::Grayscale			= "res/builtin/shaders/post_process/Grayscale.frag";
inline const char* PostProcessShaders::Sharpen				= "res/builtin/shaders/post_process/Sharpen.frag";
inline const char* PostProcessShaders::Blur					= "res/builtin/shaders/post_process/Blur.frag";
inline const char* PostProcessShaders::Edge_Detection		= "res/builtin/shaders/post_process/Edge_Detection.frag";
