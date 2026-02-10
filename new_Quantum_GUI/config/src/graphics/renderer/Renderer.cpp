#include "Renderer.hpp"
#include <glad/glad.h>

// Definir el quad para dibujar la textura de la escena
static float quadVertices[] = {
    // Posiciones   // UV
    -1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f,  1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f
};

void Renderer::init(unsigned int width, unsigned int height) {
    // ... (inicialización de m_mainShader y m_camera) ...

    m_sceneFBO = new Framebuffer(width, height);
    // Cargar el shader de post-procesado (ej: bloom.frag)
    m_postProcessShader = new Shader("shaders/postprocess/quad.vert", "shaders/postprocess/bloom.frag"); 
    m_postProcessShader->use();
    m_postProcessShader->setInt("u_SceneTexture", 0); // La textura de la escena va a la unidad 0
    m_postProcessShader->setInt("u_BlurredTexture", 1); // Si tuvieras un shader de blur, iría aquí

    // Configurar VAO/VBO para el quad de post-procesado
    unsigned int quadVBO;
    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(m_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void Renderer::beginSceneRender() {
    m_sceneFBO->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el FBO
}

void Renderer::endSceneRender() {
    m_sceneFBO->unbind(); // Volver al framebuffer por defecto
}

void Renderer::renderPostProcess(float bloomIntensity) {
    // Ahora dibujamos la textura del FBO en la pantalla
    m_postProcessShader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_sceneFBO->getTextureID());
    m_postProcessShader->setFloat("u_BloomIntensity", bloomIntensity);

    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6); // Dibujar el quad
    glBindVertexArray(0);
}