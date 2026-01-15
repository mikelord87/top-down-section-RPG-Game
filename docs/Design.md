# Design Notes

This document captures the game design intent and provides a lightweight reference for future development.

---

## Game Concept

A top-down action RPG prototype where the player controls a knight (`Character`) exploring a 2D world. The player encounters enemies (`Enemy`) and interacts with world objects (`Prop`).

---

## Core Pillars

- **Readable movement and combat**: simple controls, clear hit feedback
- **Fast iteration**: add small features frequently
- **Data-driven growth**: move constants and tuning values to one place as the game scales
- **Maintainable architecture**: shared behavior in `BaseCharacter`, specialized behavior in derived classes

---

## Player (`Character`)

### Goals
- Responsive movement
- Clear weapon usage / melee reach
- Health-based survival loop

### Mechanics (current / intended)
- **Movement**: WASD sets velocity each frame
- **Weapon**: sword sprite + weapon collision rectangle
- **Health**: initialized from `CHARACTER_PLAYER_HEALTH`

### Future improvements
- Attack input + cooldown window
- Attack animation timing (active frames vs recovery)
- Knockback + invincibility frames (brief)
- Stamina (optional)

---

## Enemies (`Enemy`)

### Goals
- Minimal but believable behavior
- Easy to add new enemy types

### Behavior ideas
- **Idle / roam**: random or waypoint movement
- **Detect / chase**: pursue player within a radius
- **Attack**: contact damage or timed melee
- **Retreat** (optional): move away when low HP

### Scaling path
- Start with one enemy archetype → expand into:
  - fast/low HP
  - slow/high HP
  - ranged (projectile)
  - boss (patterned behavior)

---

## Props (`Prop`)

Props can be:
- **Decorations**: trees, rocks, scenery
- **Solid obstacles**: block movement / collision
- **Interactables**: doors, chests, pickups
- **Triggers**: zones that start events or spawn enemies

### Suggested data model
- `PropType`: Decoration / Solid / Interactable / Trigger
- Optional `id` or `tag` for scripting / event logic

---

## Combat & Collision

### Combat loop (intended)
1. Player attacks → weapon hitbox becomes active
2. Hitbox intersects enemy collision rectangle → apply damage
3. Enemy reacts (HP-, knockback, death)

### Collision suggestions
- Centralize collision checks in a helper module or game-world manager
- Add debug toggle to draw hitboxes (very helpful)

---

## World / Camera

Typical approach:
- Keep player on screen center
- Draw enemies/props relative to player world position offset

Notes:
- Distinguish **world space** (true positions) vs **screen space** (draw positions)
- Keep conversions consistent (one function or module)

---

## UI

Minimal UI milestones:
- HP bar for player
- Damage feedback (flash, sound, shake)
- Game over screen (HP <= 0)

---

## Tuning / Constants

As the project grows, consider moving constants to a single header:
- `Constants.h` or `Config.h`

Example:
- movement speed
- weapon reach
- starting/max HP
- enemy detection radius

---

## Milestones

- **M1**: Attack input + enemy damage
- **M2**: World collision with props/tiles
- **M3**: Enemy AI (patrol/chase/attack)
- **M4**: UI + game states
- **M5**: Content (levels, enemies, items)
