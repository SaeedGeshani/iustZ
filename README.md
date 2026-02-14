# IUSTZ Ranking Core

IUSTZ Ranking Core is a C++ text-based RPG focused on turn-based combat, inventory strategy, and character progression.

## Repository layout

```text
.
├── src/                  # Active playable codebase
│   ├── Headers/          # Gameplay classes and UI helpers
│   ├── SaveSystem.*      # JSON save/load implementation
│   ├── data/             # Legacy text data still used by older flows
│   └── The_main.cpp      # Game entrypoint
├── external/             # Third-party headers (nlohmann/json)
├── archive/              # Legacy/experimental snapshots
├── docs/                 # Reports and project docs
├── CMakeLists.txt
└── README.md
```

## Features

- Single-player and local multiplayer game loop.
- Turn-based combat with stamina, damage, XP, and level progression.
- Shop and inventory systems (weapons + usable items).
- Slot-based save/load using validated JSON save files.

## Build and run

> The game depends on `windows.h`, so native builds are intended for Windows environments (Visual Studio or MinGW).

### CMake (recommended)

```bash
cmake -S . -B build
cmake --build build
./build/iustz_game
```

### g++ (single command, MinGW)

```bash
g++ -std=c++17 -O2 -Iexternal -Isrc -Isrc/Headers src/*.cpp -o iustz_game.exe
./iustz_game.exe
```

## Save and load system (updated)

The game now stores saves in **JSON slot files** instead of the old `src/data/<name>.txt` character files.

### Save location

- Directory: `saves/`
- One file per slot: `saves/<slotName>.json`

The save directory is created automatically when saving for the first time.

### Save format

Each save contains:

- `version` (currently `1`)
- `player` object: `name`, `gender`, `hp`, `xp`, `lvl`, `coins`, `dm`, `stamina`, `kills`
- `inventory` object:
  - `weapons`: array of weapon names
  - `items`: array of usable-item names
- `equippedWeapon`: equipped weapon name

### Load behavior

- The load menu lists all `*.json` files in `saves/`.
- Files are validated before loading.
- Corrupt files, unsupported versions, or missing required fields are rejected with an error message.
- Unknown inventory entries are skipped when reconstructing runtime objects.

### Important compatibility note

- Old text save files in `src/data/` are **not** used by the new slot-based JSON loader.
- Existing JSON save files must match `version: 1`.

## Development notes

- Make gameplay changes in `src/`.
- Keep `archive/` unchanged unless intentionally curating historical snapshots.
- See `CONTRIBUTING.md` for contribution guidelines.

## License

MIT License. See [LICENSE](LICENSE).
