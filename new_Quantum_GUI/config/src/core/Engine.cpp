#include "Engine.hpp"

#include "interface/VisualMapper.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <chrono>

bool Window::initialize(unsigned int width, unsigned int height, const char* title) {
    if (m_initialized) {
        return true;
    }

    if (glfwInit() != GLFW_TRUE) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windowHandle = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, nullptr, nullptr);
    if (m_windowHandle == nullptr) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_windowHandle);
    m_hasGraphicsContext = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) != 0;
    if (!m_hasGraphicsContext) {
        glfwDestroyWindow(m_windowHandle);
        m_windowHandle = nullptr;
        glfwTerminate();
        return false;
    }

    glfwSwapInterval(1);
    glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
    m_initialized = true;
    return true;
}

bool Window::shouldClose() const {
    return !m_initialized || !m_windowHandle || glfwWindowShouldClose(m_windowHandle);
}

void Window::swapBuffers() {
    if (m_initialized && m_windowHandle) {
        glfwSwapBuffers(m_windowHandle);
    }
}

void Window::pollEvents() {
    if (m_initialized) {
        glfwPollEvents();
    }
}

void Window::shutdown() {
    if (m_windowHandle) {
        glfwDestroyWindow(m_windowHandle);
        m_windowHandle = nullptr;
    }
    if (m_initialized) {
        glfwTerminate();
    }
    m_initialized = false;
    m_hasGraphicsContext = false;
}

bool Window::hasGraphicsContext() const {
    return m_initialized && m_hasGraphicsContext && m_windowHandle != nullptr;
}

bool Engine::initialize() {
    if (!m_window.initialize(1280, 720, "S.I.C.P")) {
        return false;
    }
    if (!m_window.hasGraphicsContext()) {
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
    m_cubeField.shutdown();
    m_renderer.shutdown();
    m_window.shutdown();
    m_initialized = false;
}
