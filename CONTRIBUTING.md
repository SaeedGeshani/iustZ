# Contributing Guide

Thanks for helping improve IUSTZ Ranking Core.

## What to edit

- **Primary codebase:** `src/`
- **Historical snapshots:** `archive/` (reference only)
- **Documentation assets:** `docs/`

## Development workflow

1. Make focused changes in `src/`.
2. Keep commits scoped and readable.
3. Update README/docs when behavior or structure changes.
4. Do not commit generated binaries or temporary IDE files.

## Build expectation

The project currently targets Windows-oriented toolchains due to `windows.h` usage.

## Pull request checklist

- [ ] Code changes are scoped and intentional.
- [ ] No generated artifacts (`.exe`, object files, logs) are included.
- [ ] Documentation is updated for structural or behavior changes.
- [ ] Build/validation steps are included in the PR description.
