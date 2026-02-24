# Guía de comandos: depuración + arranque de simulación (S.I.C.P)

## 1) Verificar conflictos de merge
```bash
rg -n "^(<<<<<<<|=======|>>>>>>>)" -S .
```
Si no imprime nada, no hay marcadores de conflicto pendientes.

## 2) Dependencias necesarias
Necesitas en el sistema:
- `cmake`
- compilador C++17 (`g++` o `clang++`)
- `glfw3`
- `glm`
- `glad` (headers + lib, o integrado como submódulo)

## 3) Build de depuración
Desde la raíz del repo:
```bash
cmake -S new_Quantum_GUI/config -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

## 4) Ejecutar simulación
```bash
./build/sicp_gui
```

## 5) Ejecutar con gdb
```bash
gdb --args ./build/sicp_gui
# dentro de gdb:
run
bt
```

## 6) Checklist rápida antes de depurar
1. `Window::initialize` debe crear contexto OpenGL (GLFW + GLAD).
2. `Renderer::submit` debe emitir draw (ya llama `field.draw()`).
3. `Shader` debe compilar/linkear sin errores de ruta.
4. `Framebuffer` debe reportar `isComplete() == true`.

## 7) Errores típicos
- `glad/glad.h` no encontrado: falta instalar/incluir GLAD.
- `glm/glm.hpp` no encontrado: falta `libglm-dev` (o equivalente).
- ventana negra: revisar logs de shader y completitud de FBO.
