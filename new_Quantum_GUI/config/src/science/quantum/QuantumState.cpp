#include "QuantumState.hpp"

void QuantumState::evolve(const BrainWaves& waves, float dt) {
    // La onda Beta (concentración) actúa como la "fuerza de bombeo" del sistema
    float pumpForce = waves.beta * 2.0f;
    
    // La onda Alpha (relajación) reduce la decoherencia (estabiliza)
    float stability = waves.alpha * 0.5f;

    m_phase += (m_omega + pumpForce) * dt;
    
    // El vector de Bloch se expande o contrae según el estado mental
    float radius = 0.5f + stability; 
    m_bloch.x = std::sin(m_phase) * radius;
    m_bloch.y = std::cos(m_phase) * radius;
    m_bloch.z = std::sin(m_phase * 0.5f);
}