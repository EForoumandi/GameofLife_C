# MatMul — CPU & CUDA Matrix Multiplication

Implementations and benchmarks for matrix–matrix multiplication across **CPU** and **GPU** paths:

- Naïve C/C++ CPU baseline
- Optimized CPU via **BLAS** (`cblas_dgemm`, e.g., Intel MKL / OpenBLAS)
- CUDA GPU kernels (naïve global-memory & shared-memory tiled)
- **cuBLAS** (`cublasDgemm`) reference

The goal is to compare correctness and performance across these variants on the same problem sizes.

---

## Features

- **Multiple backends**: CPU naive, CPU BLAS, CUDA naive, CUDA shared, cuBLAS
- **Comparable interfaces** so you can sweep matrix sizes and collect timings
- **Single precision / double precision** ready (toggle typedef or template)
- **Deterministic seeding** for reproducible inputs
- **Simple CSV logging** for plots

> Note: The repository currently includes starter CUDA code and a README; you can add BLAS/CPU files as shown below if they’re not already present.

---

## Requirements

- **C/C++ toolchain** (GCC/Clang or MSVC)
- **CUDA Toolkit** (for GPU builds; includes cuBLAS)
- **A BLAS library** for CPU (choose one)
  - Intel **MKL** (Linux/Windows/macOS)
  - **OpenBLAS** (portable open-source)
- Python (optional) for plotting CSV results

---

## Build

### 1) CPU (naïve)

```bash
g++ -O3 -march=native -DNDEBUG -o matmul_cpu src/matmul_cpu_naive.cpp
