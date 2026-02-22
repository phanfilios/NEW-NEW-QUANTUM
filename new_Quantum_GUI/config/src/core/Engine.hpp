#pragma once

#include "core/Kernel.hpp"
#include "graphics/renderer/Renderer.hpp"
#include "graphics/scene/QuantumCubeField.hpp"
#include "science/neuro/NeuroInterface.hpp"
#include "science/neuro/SignalProcessor.hpp"
#include "science/quantum/QuantumState.hpp"

class Window {
public:
    bool initialize(unsigned int width, unsigned int height, const char* title);
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void shutdown();
    bool hasGraphicsContext() const;

private:
    bool m_initialized = false;
    bool m_hasGraphicsContext = false;
    struct GLFWwindow* m_windowHandle = nullptr;
};

class Engine {
public:
    bool initialize();
    void run();
    void shutdown();

private:
    bool m_initialized = false;
    Window m_window;
    Kernel m_kernel;
    NeuroInterface m_neuroInterface;
    SignalProcessor m_signalProcessor;
    QuantumState m_quantumState;
    QuantumCubeField m_cubeField;
    Renderer m_renderer;
};
