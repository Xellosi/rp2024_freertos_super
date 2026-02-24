# blink (Super Project demo)

This example is tracked by the top-level `rp2024_freertos_super` repository and demonstrates Super Project integration:

- Dependencies come from top-level git submodules:
  - `pico-sdk`
  - `FreeRTOS`
- The build uses `SUPER_PROJECT_ROOT` and resolves SDK/kernel from the root project.

## Build

```bash
cd workplace/blink
make
```

or:

```bash
cmake -S . -B build -DSUPER_PROJECT_ROOT=$(pwd)/../..
cmake --build build -j
```
