#include "Kernel.hpp"

void EventBus::process() {
    // Placeholder del bus de eventos del sistema.
}

void Kernel::tick(float dt) {
    (void)dt;
    m_eventBus.process();
    // Kernel: coordina, no calcula ciencia ni renderiza.
}

void Kernel::setTimeMultiplier(float multiplier) {
    m_config.timeMultiplier = multiplier;
}
