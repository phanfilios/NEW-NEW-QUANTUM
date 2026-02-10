#include "core/Engine.hpp"

int main() {
    // El Engine encapsula toda la complejidad
    Engine engine; 
    
    if (engine.initialize()) {
        engine.run();
    }
    
    return 0;
}