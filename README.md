# NEW-NEW-QUANTUM / S.I.C.P

Base arquitectónica de simulación cuántica + render OpenGL, organizada en capas:

- `science/` (modelo cuántico y señales)
- `interface/` (mapeo semántico a parámetros visuales)
- `graphics/` (renderer, shaders, escena)
- `core/` (engine y ciclo de vida)

## Estado actual
- Fase 1-2 completadas a nivel de contratos y separación modular.
- Runtime gráfico con bootstrap de contexto (GLFW+GLAD), shader runtime y FBO.
- Render de campo cuántico actualmente en `GL_POINTS` (paso intermedio antes de cubos instanciados completos).

## Arranque rápido
Consulta `GUIA_COMANDOS_DEPURACION.md` para comandos de build, ejecución y depuración.
