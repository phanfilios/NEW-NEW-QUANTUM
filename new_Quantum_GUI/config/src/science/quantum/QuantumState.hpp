#pragma once
#include <glm/glm.hpp>

class QuantumState {
public:
    void evolve(float dt) {
        // Simulación de precesión de Larmor simplificada
        m_phase += m_omega * dt;
        m_bloch.x = std::sin(m_phase);
        m_bloch.y = std::cos(m_phase);
        m_bloch.z = std::cos(m_phase * 0.5f);
    }

    float getCoherence() const { 
        return glm::length(m_bloch); 
    }
    
    glm::vec3 getVector() const { return m_bloch; }

private:
    glm::vec3 m_bloch{1.0f, 0.0f, 0.0f};
    float m_phase = 0.0f;
    float m_omega = 1.2f; // Velocidad angular
};