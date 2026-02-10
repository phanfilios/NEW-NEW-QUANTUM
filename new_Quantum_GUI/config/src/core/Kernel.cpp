#include "Kernel.hpp"

void Kernel::tick(float dt) {
    // 1. Despachar eventos de sistema si los hay
    m_eventBus->process();

    // 2. Ejecutar la lógica de paso de tiempo (Ciencia)
    // Aquí podrías aplicar un multiplicador de tiempo si quieres cámara lenta
    float simulationTime = dt * m_config.timeMultiplier;
    
    // 3. El Kernel solo "avisa" que el tiempo pasó
    // No necesita saber qué hace el QuantumState, solo que debe evolucionar
}