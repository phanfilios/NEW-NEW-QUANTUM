#include "Renderer.hpp"

#include <glad/glad.h>

static float quadVertices[] = {
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f};

void Renderer::init(unsigned int width, unsigned int height) {
    m_sceneFBO = std::make_unique<Framebuffer>(width, height);
    m_camera = std::make_unique<Camera>();
    m_mainShader = std::make_unique<Shader>("shaders/core/cube_instanced.vert", "shaders/core/cube_instanced.frag");
    m_postProcessShader = std::make_unique<Shader>("shaders/postprocess/quad.vert", "shaders/postprocess/bloom.frag");

    glEnable(GL_DEPTH_TEST);

    m_postProcessShader->use();
    m_postProcessShader->setInt("u_SceneTexture", 0);

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &m_quadVBO);
    glBindVertexArray(m_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::submit(const QuantumCubeField& field, const glm::vec4& color) {
    if (!m_mainShader || !m_camera) {
        return;
    }

    m_mainShader->use();
    m_mainShader->setMat4("u_ViewProjection", m_camera->viewProjection());
    m_mainShader->setVec4("u_Color", color);
    field.draw();
}

void Renderer::beginSceneRender() {
    if (!m_sceneFBO) {
        return;
    }

    m_sceneFBO->bind();
    clear();
}

void Renderer::endSceneRender() {
    if (!m_sceneFBO) {
        return;
    }

    m_sceneFBO->unbind();
}

void Renderer::renderPostProcess(float bloomIntensity) {
    if (!m_postProcessShader || !m_sceneFBO) {
        return;
    }

    m_postProcessShader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_sceneFBO->getTextureID());
    m_postProcessShader->setFloat("u_BloomIntensity", bloomIntensity);

    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::shutdown() {
    m_sceneFBO.reset();
    m_camera.reset();
    m_postProcessShader.reset();
    m_mainShader.reset();

    if (m_quadVBO != 0) {
        glDeleteBuffers(1, &m_quadVBO);
        m_quadVBO = 0;
    }
    if (m_quadVAO != 0) {
        glDeleteVertexArrays(1, &m_quadVAO);
        m_quadVAO = 0;
    }
}
