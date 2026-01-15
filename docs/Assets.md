# Assets Guide

This page explains how assets are stored and referenced in the game.

---

## Assets Folder

Recommended structure:

```text
assets/
  characters/
  nature_tileset/
  ui/
  audio/
```

In the current code, the player weapon sprite is referenced as:

- `KNIGHT_WEAPON_SWORD_PATH` (in `Character.h`)

Example:
- `assets/characters/weapon_sword.png`

---

## Naming Conventions (Recommended)

- Use lowercase with underscores:
  - `knight_idle.png`
  - `weapon_sword.png`
  - `enemy_slime_walk.png`
- Keep folders descriptive:
  - `characters/`
  - `tiles/` or `nature_tileset/`
  - `ui/`

---

## Adding a New Asset

1. Place the file under `assets/` in an appropriate folder
2. Reference it from code via a constant/path define (or `constexpr`)
3. Load it using raylib:
   - `LoadTexture("assets/...")`

**Tip:** Prefer storing paths in one place so you don’t duplicate strings.

---

## Credits / Licensing

If you use third-party art/audio, keep a record of:

- Author/creator
- License type (CC0, CC-BY, etc.)
- Source location

Recommended: add a `CREDITS.md` file or a “Credits” section in `README.md`.

---

## Performance Tips

- Load textures once and reuse them
- Avoid loading textures inside `tick()`; load at initialization or in a resource manager
- Consider unloading textures on shutdown (or when changing levels)
