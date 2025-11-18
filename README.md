# Khez - Chess Engine

C++ chess engine based on bitboards.

## Requirements

- CMake 3.16+
- C++17 compatible compiler (GCC/Clang)
- Build tools (make)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Running

### Main executable

```bash
./khez
```

### Tests

```bash
./khez_tests
```

Or using CTest:

```bash
ctest
```

### References

Overall implementation mostly based on what can be found on the [Chess programming wiki](https://www.chessprogramming.org/) and the initial implementation was guided by this really cool playlist [Bitboard CHESS ENGINE in C](https://www.chessprogramming.org/) by [Code Monkey King aka Maksim Korzh](https://github.com/maksimKorzh)

Find magic numbers algorithm is the one Proposed by [Tord Romstad](https://www.chessprogramming.org/Looking_for_Magics) [here on chessproggeming wiki](https://www.chessprogramming.org/Looking_for_Magics)
