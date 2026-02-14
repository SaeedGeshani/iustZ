# IUSTZ Ranking Core

IUSTZ Ranking Core is a C++ text-based RPG focused on turn-based combat, inventory strategy, and character progression.

## Why this repository is structured this way

This repo was cleaned to separate the **active game source** from **legacy snapshots** and **documentation assets**.

## Repository layout

```text
.
├── src/                  # Active playable codebase
│   ├── Headers/
│   ├── data/
│   └── The_main.cpp
├── archive/              # Legacy/experimental snapshots kept for reference
│   ├── APfirstproject/
│   ├── Improved/
│   └── experiments/
├── docs/
│   └── reports/          # PDF reports and project docs
├── .gitignore
├── CONTRIBUTING.md
├── LICENSE
└── README.md
```

## Features

- Single-player and local multiplayer mode.
- Character create/load flow with persisted save data.
- Enemy encounters, shop events, and progression loop.
- Weapon/item classes with stamina and HP mechanics.

## Build and run

> Current game code uses `windows.h`, so native compilation is intended for Windows (MSYS2/MinGW or Visual Studio environments).

### g++ (MinGW)

```bash
g++ -std=c++17 -O2 -o The_main.exe src/The_main.cpp
./The_main.exe
```

## Save files

Runtime save data is stored in:

- `src/data/users.txt`
- `src/data/*.txt`

## Development notes

- Work on `src/` for current gameplay changes.
- Keep `archive/` untouched unless you are intentionally curating historical versions.
- See `CONTRIBUTING.md` for contribution standards.

## License

MIT License. See [LICENSE](LICENSE).
