#pragma once
#include <glm/glm.hpp>
#include "graphics/api/Shader.hpp"
#include "graphics/api/Framebuffer.hpp" // <-- Nuevo
#include "graphics/scene/Camera.hpp"
#include "graphics/scene/QuantumCubeField.hpp"
#include "interface/VisualMapper.hpp" // Para BloomIntensity

class Renderer {
public:
    // ... métodos existentes ...
    void init(unsigned int width, unsigned int height); // Añadimos dimensiones
    void beginSceneRender(); // Para dibujar la escena a un FBO
    void endSceneRender();   // Para desvincular el FBO
    void renderPostProcess(float bloomIntensity); // <-- Nuevo

private:
    Shader* m_mainShader = nullptr;
    Shader* m_postProcessShader = nullptr; // <-- Nuevo Shader de post-procesado
    Camera* m_camera = nullptr;
    Framebuffer* m_sceneFBO = nullptr; // <-- FBO para la escena
    
    // Malla de un cuadrado que cubre toda la pantalla para el post-procesado
    unsigned int m_quadVAO = 0; 
};