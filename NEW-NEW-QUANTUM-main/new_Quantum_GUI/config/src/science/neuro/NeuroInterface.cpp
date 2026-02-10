#include "NeuroInterface.hpp"

#include <cmath>

void NeuroInterface::poll() {
    m_simulationTime += 0.016f;
    m_rawSignal = simulateBiologicalNoise();
}

float NeuroInterface::getRawSignal() const {
    return m_rawSignal;
}

float NeuroInterface::simulateBiologicalNoise() {
    const float base = std::sin(m_simulationTime * 1.7f) * 0.25f + 0.5f;
    const float modulation = std::sin(m_simulationTime * 0.37f) * 0.1f;
    return base + modulation;
}
