#include "interface/VisualMapper.hpp"
#include "science/quantum/QuantumState.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>

struct ScenarioResult {
    const char* name;
    BrainWaves waves;
    RenderUpdate update;
    float coherence;
};

ScenarioResult runScenario(const char* name, const BrainWaves& waves) {
    QuantumState state;
    state.evolve(waves, 0.0f);
    const RenderUpdate update = VisualMapper::map(state);
    return ScenarioResult{name, waves, update, state.getCoherence()};
}

int main() {
    const ScenarioResult a = runScenario("A", BrainWaves{0.10f, 0.10f, 0.10f});
    const ScenarioResult b = runScenario("B", BrainWaves{0.60f, 0.60f, 0.60f});
    const ScenarioResult c = runScenario("C", BrainWaves{1.00f, 1.00f, 1.00f});

    const bool scaleOk = (a.update.scale < b.update.scale) && (b.update.scale < c.update.scale);
    const bool bloomOk = (a.update.bloomIntensity < b.update.bloomIntensity) &&
                         (b.update.bloomIntensity < c.update.bloomIntensity);
    const bool rotationOk = (a.update.rotationSpeed < b.update.rotationSpeed) &&
                            (b.update.rotationSpeed < c.update.rotationSpeed);

    std::cout << "Escenario,Coherence,Scale,RotationSpeed,Bloom\n";
    std::cout << std::fixed << std::setprecision(4);
    for (const ScenarioResult& s : {a, b, c}) {
        std::cout << s.name << ',' << s.coherence << ',' << s.update.scale << ','
                  << s.update.rotationSpeed << ',' << s.update.bloomIntensity << "\n";
    }

    if (!(scaleOk && bloomOk && rotationOk)) {
        std::cerr << "Validation failed: expected monotonic increase in scale/rotation/bloom.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Validation passed.\n";
    return EXIT_SUCCESS;
}
