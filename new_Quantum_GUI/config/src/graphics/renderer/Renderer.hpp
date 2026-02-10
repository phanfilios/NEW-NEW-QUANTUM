#pragma once

#include "graphics/api/Framebuffer.hpp"
#include "graphics/api/Shader.hpp"
#include "graphics/scene/Camera.hpp"
#include "graphics/scene/QuantumCubeField.hpp"

#include <glm/glm.hpp>
#include <memory>

class Renderer {
public:
    void init(unsigned int width, unsigned int height);
    void clear();
    void submit(const QuantumCubeField& field, const glm::vec4& color);
    void beginSceneRender();
    void endSceneRender();
    void renderPostProcess(float bloomIntensity);
    void shutdown();

private:
    std::unique_ptr<Shader> m_mainShader;
    std::unique_ptr<Shader> m_postProcessShader;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Framebuffer> m_sceneFBO;

    unsigned int m_quadVAO = 0;
};
