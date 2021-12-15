#include "frame_buffer.h"

//screen quad
std::vector<float> Quad::Vertices = {  //vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
       //positions   //texCoords
       -1.0f,  1.0f,  0.0f, 1.0f,
       -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

       -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};

FrameBuffer::FrameBuffer(const WindowManager& win)
{
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    std::tie(m_width, m_height) = win.GetSize();
    SetTexBuffer();
    SetRBO();
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{}

void FrameBuffer::CreateScreenQuad(uint quadNum)
{
    unsigned int quadVAO;
    unsigned int quadVBO;
    for (size_t i = 0; i < quadNum; i++)
    {
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);

        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, Quad::Vertices.size() * sizeof(float), Quad::Vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        this->quad.emplace_back(quadVAO, quadVBO);
    }
    if (quadNum != 0)
        m_whetherCreateScreenQuad = true;
}

FrameBuffer& FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glEnable(GL_DEPTH_TEST);
    return *this;
}

void FrameBuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void FrameBuffer::Render(Shader& shader, uint num, const glm::mat4 transform)
{
    shader.Use();
    shader.SetMat4("transform", transform);
    glBindVertexArray(this->quad.at(num - 1).VAO);
    glBindTexture(GL_TEXTURE_2D, m_texBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FrameBuffer::Update(const WindowManager& win)
{
    auto [width, height] = win.GetSize();
    if (width != m_width || height != m_height)
    {
        m_width = width;
        m_height = height;
        if (m_texBuffer)
        {
            glDeleteTextures(1, &m_texBuffer);
            SetTexBuffer();
        }
        if (m_RBO)
        {
            glDeleteRenderbuffers(1, &m_RBO);
            SetRBO();
        }
    }
}

unsigned int FrameBuffer::GetTexBuffer() const
{
    return m_texBuffer;
}

void FrameBuffer::Destory()
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
void FrameBuffer::SetTexBuffer()
{
    glGenTextures(1, &m_texBuffer);
    glBindTexture(GL_TEXTURE_2D, m_texBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texBuffer, 0);
}

//create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
void FrameBuffer::SetRBO()
{
    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
}
