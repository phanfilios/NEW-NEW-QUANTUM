#pragma once

#include "science/neuro/NeuroInterface.hpp"

class SignalProcessor {
public:
    BrainWaves process(float rawSignal, float dt);
};
