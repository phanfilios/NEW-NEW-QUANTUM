#pragma once

#include "science/neuro/NeuroInterface.hpp"

struct QuantumVector {
    float x = 1.0f;
    float y = 0.0f;
    float z = 0.0f;
};

class QuantumState {
public:
    void evolve(const BrainWaves& waves, float dt);

    float getCoherence() const;
    QuantumVector getVector() const;

private:
    QuantumVector m_bloch{};
    float m_phase = 0.0f;
    float m_omega = 1.2f;
};
