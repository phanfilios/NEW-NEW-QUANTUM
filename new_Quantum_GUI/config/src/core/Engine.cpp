#include "Engine.hpp"
#include "interface/VisualMapper.hpp"
#include <GLFW/glfw3.h>

void Engine::run() {
    if (!init()) return;

    float lastFrame = 0.0f;
    while (!m_window.shouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        if (dt > 0.1f) dt = 0.1f; 

        m_neuroInterface.poll();
        BrainWaves waves = m_signalProcessor.process(m_neuroInterface.getRawSignal(), dt);
        m_quantumState.evolve(waves, dt);
        auto visualData = VisualMapper::map(m_quantumState);

        // --- ETAPA 1: RENDERIZAR LA ESCENA EN UN FBO ---
        m_renderer.beginSceneRender(); // Enlazar el FBO
        m_renderer.clear();
        m_cubeField.update(visualData.scale, visualData.rotationSpeed, dt);
        m_renderer.submit(m_cubeField, visualData.color);
        m_renderer.endSceneRender();   // Desenlazar el FBO

        // --- ETAPA 2: RENDERIZAR EL POST-PROCESADO EN LA PANTALLA ---
        m_renderer.clear(); // Limpiar la pantalla final
        m_renderer.renderPostProcess(visualData.bloomIntensity); // Aplicar bloom
        
        m_window.swapBuffers();
        m_window.pollEvents();
    }
    shutdown();
}