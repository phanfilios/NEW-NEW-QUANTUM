#include "SignalProcessor.hpp"

#include <algorithm>
#include <cmath>

BrainWaves SignalProcessor::process(float rawSignal, float dt) {
    static float accumulator = 0.0f;
    accumulator += std::max(dt, 0.0f);

    BrainWaves waves;
    waves.alpha = (std::sin(accumulator * 10.0f) * 0.5f + 0.5f) * rawSignal;
    waves.beta = (std::sin(accumulator * 20.0f) * 0.5f + 0.5f) * rawSignal;
    waves.gamma = (std::sin(accumulator * 40.0f) * 0.5f + 0.5f) * rawSignal;

    return waves;
}
