# Firmware Development Guide

### Description of Reserved memory in HBM for RISCV

| region | size | rv access | host access |
| - | - | - | - |
| fw.bin & rodata | 5 * 2MB | ro | ro, no_cache |
| bss & stack & heap | 5 * 2MB | rw | ro, no_cache |
| command queue | 5 * 2MB | ro | rw |
| malloc | 5 * 20MB | rw | ro |

