#include "framebuffers_manager.h"

//screen quad
std::vector<float> Quad::quadVertices = {  //vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
       //positions   //texCoords
       -1.0f,  1.0f,  0.0f, 1.0f,
       -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

       -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

FramebuffersManager::FramebuffersManager(GLFWwindow* window)
{
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    auto [_width, _height] = GetFramebufferSize(window);
    SetTexColorBuffer(_width, _height);
    SetRBO(_width, _height);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FramebuffersManager::~FramebuffersManager()
{}

void FramebuffersManager::CreateScreenQuad(unsigned int quadNum)
{
    unsigned int quadVAO;
    unsigned int quadVBO;
    for (size_t i = 0; i < quadNum; i++)
    {
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);

        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, 
                     Quad::quadVertices.size() * sizeof(decltype(Quad::quadVertices)::value_type), &Quad::quadVertices.at(0), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
                              4 * sizeof(decltype(Quad::quadVertices)::value_type), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 
                              4 * sizeof(decltype(Quad::quadVertices)::value_type), (void*)(2 * sizeof(decltype(Quad::quadVertices)::value_type)));

        this->quad.emplace_back(quadVAO, quadVBO);
    }
    if (quadNum != 0)
        m_whetherCreateScreenQuad = true;
}

void FramebuffersManager::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void FramebuffersManager::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FramebuffersManager::Render(Shader shader, unsigned int num, const glm::mat4 transform)
{
    shader.Use();
    shader.SetMat4("transform", transform);
    glBindVertexArray(this->quad.at(num - 1).VAO);
    glBindTexture(GL_TEXTURE_2D, m_texColorbuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

unsigned int FramebuffersManager::GetTexColorBuffer()const
{
    return m_texColorbuffer;
}

void FramebuffersManager::Delete()
{
    if (m_whetherCreateScreenQuad)
    {
        for (auto& i : quad)
        {
            glDeleteVertexArrays(1, &(i.VAO));
            glDeleteBuffers(1, &(i.VBO));
        }
        
    }
    glDeleteFramebuffers(1, &m_FBO);
    glDeleteRenderbuffers(1, &m_RBO);
}

//create a color attachment texture
void FramebuffersManager::SetTexColorBuffer(unsigned int width, unsigned int height)
{
    glGenTextures(1, &m_texColorbuffer);
    glBindTexture(GL_TEXTURE_2D, m_texColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texColorbuffer, 0);
}

//create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
void FramebuffersManager::SetRBO(unsigned int width, unsigned int height)
{
    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
}
