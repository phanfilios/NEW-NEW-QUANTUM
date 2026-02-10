#pragma once

#include "science/quantum/QuantumState.hpp"

#include <algorithm>
#include <glm/glm.hpp>

struct RenderUpdate {
    glm::vec4 color{0.2f, 0.5f, 1.0f, 1.0f};
    float scale = 1.0f;
    float rotationSpeed = 0.75f;
    float bloomIntensity = 0.0f;
};

class VisualMapper {
public:
    static RenderUpdate map(const QuantumState& qState) {
        RenderUpdate ru;
        const float coh = std::clamp(qState.getCoherence(), 0.0f, 2.0f);
        const QuantumVector v = qState.getVector();

        ru.scale = 0.6f + (coh * 0.35f);
        ru.rotationSpeed = 0.3f + std::abs(v.y) * 2.0f;

        const float hueFactor = std::clamp((v.z + 1.0f) * 0.5f, 0.0f, 1.0f);
        ru.color = glm::vec4(0.2f + hueFactor * 0.6f, 0.35f + coh * 0.25f, 1.0f - hueFactor * 0.4f, 1.0f);

        ru.bloomIntensity = glm::smoothstep(0.5f, 1.2f, coh);
        return ru;
    }
};
