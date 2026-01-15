# Contributing Guide

Thanks for your interest in contributing!

---

## Development Setup

1. Install prerequisites:
   - C++ compiler (GCC/Clang/MSVC)
   - raylib
   - `make` (if using Makefile)

2. Build the project:
```bash
make
```

3. Generate documentation:
```bash
make docs
```

---

## Coding Guidelines

- Prefer clear names and small functions
- Keep classes focused:
  - shared behavior in `BaseCharacter`
  - player-specific in `Character`
  - enemy-specific in `Enemy`
  - world objects in `Prop`
- Document public APIs with Doxygen comments

---

## Documentation Guidelines

- Add/maintain Doxygen blocks for new classes and public methods
- Update `README.md` and `docs/*.md` when behavior changes
- Keep `docs/Changelog.md` updated for releases

---

## Pull Requests

- Keep PRs small and focused
- Include:
  - what changed
  - why it changed
  - how to test it
- Ensure the project builds cleanly and docs generate without errors

---

## Reporting Issues

When reporting a bug, include:
- steps to reproduce
- expected behavior
- actual behavior
- screenshots/logs if relevant
- platform info (Windows/Linux/macOS)
