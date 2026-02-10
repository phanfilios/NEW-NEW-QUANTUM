#pragma once

struct KernelConfig {
    float timeMultiplier = 1.0f;
};

class EventBus {
public:
    void process();
};

class Kernel {
public:
    void tick(float dt);
    void setTimeMultiplier(float multiplier);

private:
    EventBus m_eventBus;
    KernelConfig m_config;
};
