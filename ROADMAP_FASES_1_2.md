# S.I.C.P — Roadmap de Ejecución Detallado (Fase 1 y Fase 2)

## Estado de referencia
Este documento ejecuta y aterriza las dos primeras fases:

- **Fase 1:** compilación limpia y contratos mínimos.
- **Fase 2:** separación estricta de responsabilidades entre módulos.

---

## Fase 1 — Compilación limpia y contratos mínimos

### Objetivo
Eliminar contradicciones de interfaz y cerrar archivos base faltantes para que el proyecto tenga una columna vertebral compilable.

### Trabajo aplicado
1. **Contrato unificado de Engine**
   - Se estableció la interfaz `initialize() / run() / shutdown()`.
   - `main.cpp` y `Engine` quedan alineados en la misma convención.

2. **Kernel mínimo coordinador**
   - Se formalizó `Kernel.hpp` y su implementación en `Kernel.cpp`.
   - Se dejó `Kernel` como despachador de eventos y sincronizador temporal.

3. **Cadena neuro completa**
   - Se creó `SignalProcessor.hpp` para declarar el contrato público del procesador.
   - Se agregó `NeuroInterface.cpp` para cerrar la implementación del origen de señal.

4. **QuantumState coherente**
   - Se eliminó la ambigüedad de firma y se dejó una ruta oficial:
     `evolve(const BrainWaves&, float dt)`.
   - Se definieron getters estables para coherencia y vector.

5. **API gráfica cerrada**
   - Se ampliaron contratos faltantes de `Shader` (`setInt`, `setFloat`) y su implementación.
   - Se agregó implementación de `Framebuffer`.
   - Se completaron firmas usadas por `Renderer` (`clear`, `submit`, `shutdown`).

6. **Escena base con contratos explícitos**
   - Se creó `QuantumCubeField.hpp` y se cerró su implementación mínima.
   - Se creó `Camera.hpp` como interfaz mínima de cámara.

7. **Rutas de shaders consistentes**
   - Se agregaron archivos de shader con nombres convencionales:
     - `cube_instanced.vert`
     - `cube_instanced.frag`
     - `quad.vert`
     - `bloom.frag`

### Resultado esperado de Fase 1
- Contratos públicos coherentes entre headers y source files.
- Menor riesgo de errores de enlace por símbolos inexistentes.
- Base estructural lista para validación incremental.

---

## Fase 2 — Separación estricta de responsabilidades

### Objetivo
Refuerzo de arquitectura: ciencia desacoplada del render y render desacoplado de semántica cuántica.

### Trabajo aplicado
1. **Science sin dependencia visual directa**
   - `QuantumState` usa estructuras matemáticas propias (`QuantumVector`) y no depende de OpenGL.

2. **Interface como traductor semántico**
   - `VisualMapper` realiza el mapeo `QuantumState -> RenderUpdate`.
   - Color, escala, velocidad de rotación y bloom quedan centralizados en un único punto.

3. **Renderer agnóstico a ciencia**
   - `Renderer` recibe solo datos visuales (`glm::vec4`, escala, bloom).
   - No conoce `BrainWaves`, ni ecuaciones cuánticas, ni estados neuro.

4. **Kernel y Engine como orquestadores**
   - `Engine` conecta flujo de datos por etapas y evita lógica visual/científica mezclada.
   - `Kernel` conserva rol de coordinación temporal/eventos.

### Resultado esperado de Fase 2
- Flujo limpio: **Science -> Interface -> Graphics**.
- Menor acoplamiento circular.
- Mayor capacidad de pruebas por módulo y mantenimiento.

---

## Siguiente paso recomendado
Una vez verificada compilación del entorno real (GLFW/GLAD/GLM + CMake), avanzar a:

- pruebas de integración del loop,
- checklist de ownership de recursos,
- validación visual reproducible por escenarios de señal.
