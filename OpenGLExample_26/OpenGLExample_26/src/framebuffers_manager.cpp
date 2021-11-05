#include "../include/framebuffers_manager.h"

//screen quad
std::vector<float> FramebuffersManager::quadVertices = {  //vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
       // positions   // texCoords
       -1.0f,  1.0f,  0.0f, 1.0f,
       -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

       -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

FramebuffersManager::FramebuffersManager(unsigned int width, unsigned int height)
{
    glGenFramebuffers(1, &this->FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
    SetTexColorBuffer(width, height);
    SetRBO(width, height);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FramebuffersManager::~FramebuffersManager()
{}

void FramebuffersManager::CreateScreenQuad()
{
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &this->quadVBO);

    glBindVertexArray(this->quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, this->quadVertices.size() * sizeof(decltype(this->quadVertices)::value_type), &this->quadVertices.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(decltype(this->quadVertices)::value_type), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(decltype(this->quadVertices)::value_type), (void*)(2 * sizeof(decltype(this->quadVertices)::value_type)));
    
    whetherCreateScreenQuad = true;;
}

void FramebuffersManager::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
}

void FramebuffersManager::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FramebuffersManager::Render(GLShader shader)
{
    shader.Use();
    glBindVertexArray(this->quadVAO);
    glBindTexture(GL_TEXTURE_2D, texColorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FramebuffersManager::Delete()
{
    if (whetherCreateScreenQuad)
    {
        glDeleteVertexArrays(1, &this->quadVAO);
        glDeleteBuffers(1, &this->quadVBO);
    }
    glDeleteFramebuffers(1, &this->FBO);
    glDeleteRenderbuffers(1, &this->RBO);
}

//create a color attachment texture
void FramebuffersManager::SetTexColorBuffer(unsigned int width, unsigned int height)
{
    glGenTextures(1, &this->texColorbuffer);
    glBindTexture(GL_TEXTURE_2D, this->texColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texColorbuffer, 0);
}

//create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
void FramebuffersManager::SetRBO(unsigned int width, unsigned int height)
{
    glGenRenderbuffers(1, &this->RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->RBO);
}
