#include "Engine.hpp"

#include "interface/VisualMapper.hpp"
#include <algorithm>
#include <chrono>

bool Window::initialize(unsigned int width, unsigned int height, const char* title) {
    (void)width;
    (void)height;
    (void)title;
    m_initialized = true;
    m_frameCount = 0;
    return true;
}

bool Window::shouldClose() const {
    return !m_initialized || m_frameCount > 600;
}

void Window::swapBuffers() {
    if (m_initialized) {
        ++m_frameCount;
    }
}

void Window::pollEvents() {
    // Placeholder de integración real con GLFW/SDL.
}

void Window::shutdown() {
    m_initialized = false;
}

bool Engine::initialize() {
    if (!m_window.initialize(1280, 720, "S.I.C.P")) {
        return false;
    }

    m_renderer.init(1280, 720);
    m_cubeField.init(256);
    m_initialized = true;
    return true;
}

void Engine::run() {
    if (!m_initialized && !initialize()) {
        return;
    }

    using clock = std::chrono::steady_clock;
    auto lastTick = clock::now();

    while (!m_window.shouldClose()) {
        auto now = clock::now();
        std::chrono::duration<float> delta = now - lastTick;
        float dt = std::min(delta.count(), 0.1f);
        lastTick = now;

        m_kernel.tick(dt);

        m_neuroInterface.poll();
        const BrainWaves waves = m_signalProcessor.process(m_neuroInterface.getRawSignal(), dt);
        m_quantumState.evolve(waves, dt);
        const RenderUpdate visualData = VisualMapper::map(m_quantumState);

        m_renderer.beginSceneRender();
        m_renderer.clear();
        m_cubeField.update(visualData.scale, visualData.rotationSpeed, dt);
        m_renderer.submit(m_cubeField, visualData.color);
        m_renderer.endSceneRender();

        m_renderer.clear();
        m_renderer.renderPostProcess(visualData.bloomIntensity);

        m_window.swapBuffers();
        m_window.pollEvents();
    }

    shutdown();
}

void Engine::shutdown() {
    m_renderer.shutdown();
    m_window.shutdown();
    m_initialized = false;
}
