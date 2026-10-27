# 2048 — EGE Graphics Version

A classic 2048 game built with EGE (Easy Graphics Engine).

## Features

- Graphical interface with colored tiles
- Arrow-key controls
- Live score display
- Win/lose detection: reach 2048 to win; the game ends when no moves remain
- Press R to restart at any time

## Build and Run

### Requirements

[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://isocpp.org/)
[![MinGW](https://img.shields.io/badge/MinGW-64%20bit-green.svg)](http://www.mingw-w64.org/)
[![EGE](https://img.shields.io/badge/EGE-20.08%2B-orange.svg)](https://xege.org/)

### Build

```bash
g++ 2048.cpp -o 2048.exe -ID:\mingw64\include -LD:\mingw64\lib -lgraphics -lgdi32 -lgdiplus -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid
```

Adjust the `-I` and `-L` paths to match your MinGW/EGE installation.

### Run

```bash
./2048.exe
```

## Controls

| Key | Action |
| ---- | -------- |
| ↑ | Move up |
| ↓ | Move down |
| ← | Move left |
| → | Move right |
| R | Restart |

## Rules

1. The game is played on a 4×4 grid.
2. Use the arrow keys to slide tiles.
3. Tiles with the same number merge into one tile with their sum.
4. After each move, a new 2 or 4 appears in a random empty cell.
5. Reach 2048 to win.
6. If no moves are possible and no cells are empty, the game is over.

## Tech

- Language: C++11
- Graphics: EGE (Easy Graphics Engine)
- Compiler: MinGW-w64
- Platform: Windows

## Author

**Dr. Ailan Anjuxi (谙弆悕)**

- Email: anjuxi.ME@outlook.com
- SIP: sip:anjuxi@sip.linphone.org
