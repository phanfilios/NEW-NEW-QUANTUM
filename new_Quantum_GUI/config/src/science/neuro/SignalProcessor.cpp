#include "SignalProcessor.hpp"
#include <cmath>

BrainWaves SignalProcessor::process(float rawSignal, float dt) {
    static float accumulator = 0.0f;
    accumulator += dt;

    BrainWaves waves;
    // Extraemos frecuencias mediante una simulación de filtros pasa-banda
    waves.alpha = (std::sin(accumulator * 10.0f) * 0.5f + 0.5f) * rawSignal;
    waves.beta  = (std::sin(accumulator * 20.0f) * 0.5f + 0.5f) * rawSignal;
    waves.gamma = (std::sin(accumulator * 40.0f) * 0.5f + 0.5f) * rawSignal;

    return waves;
}