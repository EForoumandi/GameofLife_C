# Game of Life — C (1-D array implementation)

A compact C implementation of Conway’s **Game of Life** that represents the 2-D grid in a **single 1-D array**. This approach keeps the code simple and cache-friendly and serves as a clear baseline for experimenting with neighbor lookups and iteration strategies.

---

## Features

- **Single-file C program** (`GameofLife.c`)
- **1-D array backing** for a 2-D grid (flat indexing: `i * width + j`)
- **Compile-time debug levels** (`-DDEBUG0`, `-DDEBUG1`, `-DDEBUG2`) for partitioning and progress prints
- Easy to build and run with any POSIX-like toolchain

---

## Quick start

### Build

```bash
# Optimize + warnings; outputs a 'gameoflife' binary
gcc -O2 -Wall -o gameoflife GameofLife.c
