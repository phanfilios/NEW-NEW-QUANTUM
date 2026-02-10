#include "Framebuffer.hpp"

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
    : m_fbo(0), m_textureColorbuffer(0), m_rboDepthStencil(0), m_width(width), m_height(height) {
    // Placeholder: crear FBO real en fase de integración gráfica.
}

Framebuffer::~Framebuffer() = default;

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
