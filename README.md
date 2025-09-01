# Miner Game

Console-based Minesweeper implemented in C++23.

## Features
- Generate mines randomly
- Reveal cells with BFS for safe area expansion
- Display game grid in console

## Requirements
- C++23 compatible compiler
- CMake 3.20+

## Build
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

<img width="1116" height="629" alt="Screenshot 2025-09-01 030551" src="https://github.com/user-attachments/assets/e3791473-d16f-4dd9-b40c-3fe161f50d54" />
