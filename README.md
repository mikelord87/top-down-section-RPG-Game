# Top-down section RPG Game

**Author:** Miguel Rios  
**Version:** 0.1.0  
**Language:** C++  
**Library:** raylib  

A small top-down action RPG prototype. The player controls a knight character, explores a 2D world, and interacts with enemies and props.

---

## Features

- Top-down player movement (WASD)
- Player melee weapon (sword) with a weapon collision rectangle
- Basic health / alive state handling
- Enemies with damage interactions
- Props / world objects
- Doxygen API documentation from source comments

---

## Project Architecture

This project is organized around a few core classes:

- `BaseCharacter`  
  Shared functionality for characters (common data/state and behavior used by both player and enemies).

- `Character`  
  The **player-controlled** knight. Handles input, movement updates, weapon drawing/collision, and player health.

- `Enemy`  
  AI-controlled character logic (movement/behavior and interactions with the player).

- `Prop`  
  Non-character world objects (environment props, interactables, decorations, etc.).

### Key gameplay data (examples)
- Player health is initialized from `CHARACTER_PLAYER_HEALTH` (see `Character.h`).
- Weapon sprite path is defined in `Character.h` (e.g., `KNIGHT_WEAPON_SWORD_PATH`).

---

## Controls

- **W / A / S / D** — Move

> Add additional controls here if you implement attack, interact, sprint, inventory, etc.

---

## Folder Structure

A clean structure (recommended):

```text
include/        # Header files (.h)
src/            # Source files (.cpp)
assets/         # Textures, tilesets, sprites, audio, etc.
docs/           # Extra markdown pages (optional)
```

If you keep everything in the repo root right now, that’s fine—this structure is just a recommended next step.

---

## Build & Run

### Prerequisites
- C++ compiler (GCC / Clang / MSVC)
- raylib installed and linkable
- `make` (if you’re building via Makefile)

### Build
From the project root:

```bash
make
```

### Run
```bash
./game
```

> If your output executable has a different name, update the command accordingly.

---

## Generate Documentation (Doxygen)

### Install (Windows)
- Install **Doxygen**
- (Recommended) Install **Graphviz** for diagrams

### Generate docs
```bash
make docs
```

Then open:
- `docs/doxygen/html/index.html`

### Recommended Doxyfile settings
To use this README as the Doxygen landing page, set:

```ini
MARKDOWN_SUPPORT       = YES
USE_MDFILE_AS_MAINPAGE = README.md
INPUT                  = src include README.md docs
FILE_PATTERNS          = *.h *.hpp *.cpp *.md
RECURSIVE              = YES
```

---

## Roadmap (Ideas)

- [ ] Player attack input + attack cooldown
- [ ] Health bar / UI feedback
- [ ] Enemy behaviors (patrol, chase, avoid, etc.)
- [ ] Tilemap collision + navigation
- [ ] Items, pickups, and inventory
- [ ] Sound effects and background music
- [ ] Save/load

---

## Contributing

Issues and pull requests are welcome:
- Keep changes small and focused
- Run `make` and `make docs` before submitting
- Prefer documenting new classes and public methods with Doxygen comments

---

## Credits

- Built with **raylib**
- Art assets: _(list sources/creators here, or “Original / TBD”)_

---

## License

Choose one:
- MIT / Apache-2.0 / GPL-3.0 / Proprietary / TBD

(Add the license text or a `LICENSE` file when you decide.)
