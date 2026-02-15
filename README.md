# IUSTZ Ranking Core

IUSTZ Ranking Core is a C++ text-based RPG focused on turn-based combat, inventory strategy, and character progression.

## Repository layout

```text
.
├── src/                  # Active playable codebase
│   ├── Headers/          # Gameplay classes and UI helpers
│   ├── GameEngine.*      # Engine wrapper API used by GUI frontend
│   ├── SaveSystem.*      # JSON save/load implementation
│   ├── data/             # Legacy text data still used by older flows
│   └── The_main.cpp      # Console entrypoint
├── src_gui/              # Dear ImGui (GLFW + OpenGL3) frontend
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
- New Dear ImGui GUI executable (`iustz_gui`) that calls the engine API and keeps gameplay rules in core code.

## Build and run

> The console game still depends on `windows.h`, so native builds are intended for Windows environments (Visual Studio or MinGW).

### CMake (recommended)

```bash
cmake -S . -B build
cmake --build build --config Release
```

Run either executable:

```bash
# Multi-config generators (MSVC)
build/Release/iustz_game.exe
build/Release/iustz_gui.exe

# Single-config generators (Ninja/Unix Makefiles)
build/iustz_game
build/iustz_gui
```

### g++ (console only, single command, MinGW)

```bash
g++ -std=c++17 -O2 -Iexternal -Isrc -Isrc/Headers src/*.cpp -o iustz_game.exe
./iustz_game.exe
```

## Save and load system (updated)

The game now stores saves in **JSON slot files** instead of the old `src/data/<name>.txt` character files.

### Save location

- Directory: `saves/`
- One file per slot: `saves/<slotId>.json`

The save directory is created automatically when saving for the first time.

### Save format

Each save contains:

- `version` (currently `3`)
- `slotId` (unique file key)
- `slotLabel` (user-facing name)
- `createdAt`, `updatedAt` (ISO local timestamps)
- `mode` (`singleplayer` or `multiplayer`)
- `partyPreview` (array of player names used by the load menu)
- `party` and `session` runtime payload (stats, inventory, battle progress)

### Load behavior

- The load menu lists all `*.json` files in `saves/`, sorted by `updatedAt` descending.
- Entries are shown as `slotLabel + updated time + party preview`.
- Legacy saves (`version < 3` or missing `slotId`) are shown in a separate legacy section and can be migrated.
- Files are validated before loading.
- Corrupt files are skipped from load actions and shown as `(corrupt save)`.
- Unknown inventory entries are skipped when reconstructing runtime objects.

### Important compatibility note

- Legacy JSON save files are supported through one-time migration to schema `version: 3`.

## Development notes

- Make gameplay changes in `src/`.
- Keep `archive/` unchanged unless intentionally curating historical snapshots.
- See `CONTRIBUTING.md` for contribution guidelines.

## License

MIT License. See [LICENSE](LICENSE).
