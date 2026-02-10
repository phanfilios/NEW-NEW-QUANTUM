#pragma once
#include <map>
#include <string>

struct BrainWaves {
    float alpha; // Relajación (8-13 Hz)
    float beta;  // Concentración (13-30 Hz)
    float gamma; // Procesamiento cognitivo alto (>30 Hz)
};

class NeuroInterface {
public:
    void poll() {
        // En esta versión, simulamos la oscilación biológica
        m_rawSignal = simulateBiologicalNoise();
    }

    float getRawSignal() const { return m_rawSignal; }

private:
    float m_rawSignal = 0.0f;
    float simulateBiologicalNoise(); // Implementado en el .cpp
};