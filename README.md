

# S.I.C.P — Sistema de Internet Cuántico Personal

still in love you
## Paso 1: generar ejecutable local

Este repositorio ya incluye un `CMakeLists.txt` para compilar un ejecutable de smoke test llamado `sicp_app`.

```bash
cmake -S . -B build
cmake --build build -j
./build/sicp_app
```

## Nota del entorno actual

El ejecutable de este paso usa *stubs locales* para OpenGL (`glad`) y matemáticas tipo `glm`.
Esto permite validar integración de módulos y ciclo de vida del motor sin depender de drivers o librerías externas en esta etapa.
