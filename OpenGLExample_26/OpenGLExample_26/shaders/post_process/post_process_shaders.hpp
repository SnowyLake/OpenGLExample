#pragma once
static struct PostProcessShaders
{
	static const char* Inversion;		//��Ƭ
	static const char* Grayscale;		//�ҶȻ�
	static const char* Sharpen;			//��
	static const char* Blur;			//ģ��
	static const char* Edge_Detection;	//��Ե���
};
const char* PostProcessShaders::Inversion		= "shaders/post_process/Inversion.frag";
const char* PostProcessShaders::Grayscale		= "shaders/post_process/Grayscale.frag";
const char* PostProcessShaders::Sharpen			= "shaders/post_process/Sharpen.frag";
const char* PostProcessShaders::Blur			= "shaders/post_process/Blur.frag";
const char* PostProcessShaders::Edge_Detection  = "shaders/post_process/Edge_Detection.frag";