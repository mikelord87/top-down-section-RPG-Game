# Architecture

This document describes the current (high-level) structure of the project and how the main game objects interact.

---

## Core Classes

### `BaseCharacter`
A common base class for any character-like entity in the game (player and enemies). Typical responsibilities include:

- Shared character data (position, movement, animation state, alive state, etc.)
- Core per-frame update hooks (e.g., `tick(float deltaTime)`)
- Common drawing helpers / helpers related to world-vs-screen positioning

> **Note:** The exact responsibilities depend on your implementation, but the goal is to avoid duplicating logic between `Character` and `Enemy`.

### `Character`
The **player-controlled** character (knight).

Main responsibilities (as implemented/expected):

- Reads keyboard input (**W/A/S/D**) to control movement
- Tracks player health and alive state
- Loads and draws an equipped sword texture
- Exposes a weapon collision rectangle (used for melee hit detection)

Key items in the header:
- `CHARACTER_PLAYER_HEALTH` — default player starting/max health
- `KNIGHT_WEAPON_SWORD_PATH` — sword sprite path
- `Rectangle getWeaponCollisionRec()` — provides weapon hitbox for collisions

### `Enemy`
An AI-controlled entity.

Typical responsibilities:

- Moves/updates each frame (`tick`)
- Has its own alive/health state
- Interacts with the player (taking/causing damage)

### `Prop`
Non-character world objects:

- Decorations (trees, rocks)
- Interactable objects (chests, doors)
- Obstacles / collision objects (depending on your implementation)

---

## Update Loop (Typical Frame)

A common pattern in a raylib game loop:

1. **Read input** (player only)
2. **Update entities**
   - `Character::tick(deltaTime)`
   - `Enemy::tick(deltaTime)` (for each enemy)
   - `Prop` update (if props are animated/interactable)
3. **Resolve interactions**
   - Weapon hitbox vs enemy hitboxes
   - Player vs enemy collisions
   - Player vs prop collisions (if applicable)
4. **Draw**
   - World (tiles / map)
   - Props
   - Enemies
   - Player
   - UI (health bar, debug, etc.)

---

## Coordinate Spaces

It’s useful to keep a clear separation of:

- **World space**: where entities truly are (e.g., map coordinates)
- **Screen space**: where things draw relative to the camera

In this project, the `Character` commonly stays **centered on-screen**, and the world scrolls around the player.
That’s why `Character::getScreenPos()` returns a screen position (often the center of the window), while enemies/props may need conversions based on player/world offsets.

---

## Damage and Health (Typical Flow)

Example flow for player damage:

- Some collision / combat logic determines a hit
- `Character::takeDamage(float damage)` is called
- `health` decreases, and when `health <= 0`, the player is considered not alive

Similarly for enemies, you’ll typically have:
- `Enemy::takeDamage(...)` or equivalent
- Alive/dead logic, remove or stop updating on death

---

## Suggested Next Steps

- Create a small **Collision** helper/module for rectangle/hit logic
- Add a lightweight **GameWorld** (or similar) to manage:
  - entity lists
  - collisions
  - spawning/despawning
- Move hard-coded constants into a single `Constants.h` (optional)
