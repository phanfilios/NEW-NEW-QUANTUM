#include "QuantumState.hpp"

#include <cmath>

void QuantumState::evolve(const BrainWaves& waves, float dt) {
    const float pumpForce = waves.beta * 2.0f;
    const float stability = waves.alpha * 0.5f;

    m_phase += (m_omega + pumpForce) * dt;

    const float radius = 0.5f + stability;
    m_bloch.x = std::sin(m_phase) * radius;
    m_bloch.y = std::cos(m_phase) * radius;
    m_bloch.z = std::sin(m_phase * 0.5f);
}

float QuantumState::getCoherence() const {
    return std::sqrt(
        (m_bloch.x * m_bloch.x) +
        (m_bloch.y * m_bloch.y) +
        (m_bloch.z * m_bloch.z));
}

QuantumVector QuantumState::getVector() const {
    return m_bloch;
}
