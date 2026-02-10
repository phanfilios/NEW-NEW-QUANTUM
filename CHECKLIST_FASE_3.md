# ✅ Checklist Fase 3 — S.I.C.P

Este checklist aterriza la **Fase 3 (validación funcional)** después de cerrar Fase 1 y Fase 2.

---

## 0) Preparación rápida

- [ ] Estar en la rama de trabajo correcta.
- [ ] Confirmar que el árbol está limpio.
- [ ] Tener dependencias del entorno disponibles (GLFW/GLAD/GLM/CMake).

Comandos:

```bash
git branch --show-current
git status
```

---

## 1) Validación del loop principal (integración end-to-end)

Objetivo: verificar flujo completo:

`NeuroInterface -> SignalProcessor -> QuantumState -> VisualMapper -> Renderer`

- [ ] `Engine::initialize()` inicializa ventana, renderer y escena.
- [ ] `Engine::run()` ejecuta ciclo sin romperse.
- [ ] `dt` se calcula y clampa para estabilidad temporal.
- [ ] `shutdown()` libera recursos al finalizar.

Evidencia mínima:
- [ ] Log de arranque.
- [ ] Log de al menos 1 ejecución completa.

---

## 2) Validación de límites de arquitectura

Objetivo: mantener separación estricta de responsabilidades.

- [ ] `science/*` no incluye OpenGL (`glad`, `GLFW`, shaders, renderer API).
- [ ] `graphics/*` no depende de semántica cuántica/neuro.
- [ ] `interface/VisualMapper` es el único traductor de estado a parámetros visuales.
- [ ] `Kernel` permanece como coordinador (no calcula ciencia ni renderiza).

Comandos sugeridos:

```bash
rg "#include <glad|#include <GLFW|Renderer|Shader" new_Quantum_GUI/config/src/science
rg "QuantumState|BrainWaves|Neuro" new_Quantum_GUI/config/src/graphics
```

---

## 3) Validación funcional de VisualMapper

Objetivo: comprobar consistencia del mapeo `QuantumState -> RenderUpdate`.

Escenarios mínimos:

### Escenario A — Señal baja / estable
- [ ] `scale` baja-media.
- [ ] `rotationSpeed` contenida.
- [ ] `bloomIntensity` baja.

### Escenario B — Señal oscilante / media
- [ ] variación perceptible en `rotationSpeed`.
- [ ] variación suave en color.
- [ ] bloom intermedio.

### Escenario C — Señal alta
- [ ] aumento claro de bloom.
- [ ] mayor dinamismo visual.
- [ ] comportamiento estable (sin saltos extremos no esperados).

Registro sugerido (tabla):

| Escenario | Entrada (señal/coherencia) | scale | rotationSpeed | color | bloom |
|---|---:|---:|---:|---|---:|
| A |  |  |  |  |  |
| B |  |  |  |  |  |
| C |  |  |  |  |  |

---

## 4) Validación de renderer y recursos

Objetivo: asegurar pipeline de render estable.

- [ ] Render a FBO de escena.
- [ ] Postproceso ejecutado (quad fullscreen + bloom).
- [ ] `Renderer::shutdown()` libera recursos correctamente.
- [ ] Sin crashes al cerrar ventana.

Checks prácticos:
- [ ] No errores OpenGL críticos en ejecución.
- [ ] Recursos creados/destruidos una sola vez por ciclo de vida.

---

## 5) Build y smoke tests

- [ ] Configuración CMake completa.
- [ ] Build sin errores.
- [ ] Ejecución de smoke test (arranca, renderiza, cierra limpio).

Comandos base:

```bash
cmake -S . -B build
cmake --build build
```

---

## 6) Definition of Done (DoD) de Fase 3

La Fase 3 se considera terminada cuando:

- [ ] El loop integrado corre de punta a punta.
- [ ] Se validan los 3 escenarios funcionales.
- [ ] El render (FBO + postprocess) es estable.
- [ ] No se rompe la separación de módulos.
- [ ] Hay evidencia escrita (tabla + notas de ejecución).

---

## 7) Próximo paso después de Fase 3

Con Fase 3 cerrada:

1. Ajuste fino de parámetros de mapeo visual.
2. Pruebas reproducibles automatizadas por escenario.
3. Preparación de Fase 4 (GUI avanzada / integración EEG real según prioridad).

