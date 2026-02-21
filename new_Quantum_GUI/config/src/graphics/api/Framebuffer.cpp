#include "Framebuffer.hpp"

#include <iostream>

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
    : m_fbo(0), m_textureColorbuffer(0), m_rboDepthStencil(0), m_width(width), m_height(height) {
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glGenTextures(1, &m_textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<int>(m_width), static_cast<int>(m_height), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);

    glGenRenderbuffers(1, &m_rboDepthStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepthStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, static_cast<int>(m_width), static_cast<int>(m_height));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboDepthStencil);

    m_complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    if (!m_complete) {
        std::cerr << "[Framebuffer] FBO incompleto durante inicializacion." << '\n';
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    if (m_rboDepthStencil != 0) {
        glDeleteRenderbuffers(1, &m_rboDepthStencil);
        m_rboDepthStencil = 0;
    }

    if (m_textureColorbuffer != 0) {
        glDeleteTextures(1, &m_textureColorbuffer);
        m_textureColorbuffer = 0;
    }

    if (m_fbo != 0) {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
