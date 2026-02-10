#pragma once
#include <glad/glad.h>

class Framebuffer {
public:
    Framebuffer(unsigned int width, unsigned int height);
    ~Framebuffer();

    void bind();
    void unbind();
    unsigned int getTextureID() const { return m_textureColorbuffer; }

private:
    unsigned int m_fbo;
    unsigned int m_textureColorbuffer;
    unsigned int m_rboDepthStencil;
    unsigned int m_width, m_height;
};