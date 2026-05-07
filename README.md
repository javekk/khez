# Khez - Chess Engine

C++ chess engine based on bitboards.

## Requirements

- CMake 3.16+
- C++17 compatible compiler (GCC/Clang)
- Build tools (make)

## Building

Debug build (default):

```bash
cmake -S . -B build
cmake --build build -j
```

Release build (optimized, use this for matches/benchmarks):

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

Build the previous commit alongside the current code (for self-play):

```bash
./scripts/build-head.sh   # produces build/khez-head
```

## Running

```bash
./build/khez            # main executable
./build/khez_tests      # tests
ctest --test-dir build  # tests via CTest
```

### References and Credits

Implementation ispirared and based on this really nice and didactic playlist [Bitboard CHESS ENGINE in C](https://www.chessprogramming.org/) by [Code Monkey King aka Maksim Korzh](https://github.com/maksimKorzh) and also based on what can be found on the [Chess programming wiki](https://www.chessprogramming.org/).
