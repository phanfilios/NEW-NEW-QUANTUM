#pragma once

struct BrainWaves {
    float alpha = 0.0f;
    float beta = 0.0f;
    float gamma = 0.0f;
};

class NeuroInterface {
public:
    void poll();
    float getRawSignal() const;

private:
    float m_rawSignal = 0.0f;
    float m_simulationTime = 0.0f;
    float simulateBiologicalNoise();
};
