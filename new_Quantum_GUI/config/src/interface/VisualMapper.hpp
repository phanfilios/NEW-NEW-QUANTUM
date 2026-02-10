#pragma once
#include "science/quantum/QuantumState.hpp"
#include <glm/glm.hpp>

struct RenderUpdate {
    glm::vec4 color;
    float scale;
    float rotationSpeed;
    float bloomIntensity; // <-- Nuevo
};

class VisualMapper {
public:
    static RenderUpdate map(const QuantumState& qState) {
        RenderUpdate ru;
        float coh = qState.getCoherence();
        
        // ... (resto de mapeo de color, escala, rotación) ...

        // Mapeo: Coherencia -> Intensidad de Bloom
        // Solo hay bloom si la coherencia supera un umbral
        ru.bloomIntensity = glm::smoothstep(0.5f, 1.0f, coh); 
        
        return ru;
    }
};