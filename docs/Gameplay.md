# Gameplay Notes

This page documents current gameplay behavior and intended design direction.

---

## Current Gameplay (Prototype)

- You control a knight character (`Character`)
- You can move in a top-down world using keyboard input
- A sword is equipped and can be drawn / used for melee hit detection
- Enemies (`Enemy`) exist as hostile entities
- Props (`Prop`) exist as world objects

---

## Controls

- **W / A / S / D** — Move

> If/when you add attacks or interactions, list them here:
> - **Space / Mouse Left** — Attack (example)
> - **E** — Interact (example)

---

## Combat

### Weapon / Hit Detection
The player character exposes a weapon collision rectangle:

- `Rectangle Character::getWeaponCollisionRec()`

Typical usage:
- When the player attacks (or while attacking), test this rectangle against enemy collision rectangles
- If collision occurs, apply damage to the enemy

### Health
The player starts with:

- `CHARACTER_PLAYER_HEALTH` in `Character.h`

The player loses health via:

- `Character::takeDamage(float damage)`

---

## Enemies

Enemies should typically have:

- Movement/behavior updates per frame (`tick`)
- A way to take damage (health decreases)
- A state that determines whether they’re active/alive

Possible next behaviors:
- Patrol in an area
- Chase player within a detection radius
- Stop/idle when far away
- Attack player when close

---

## Props

Props can be used for:

- Decoration
- Obstacles (collision)
- Interactables (chests, doors)
- Triggers (zone-based events)

Suggested additions:
- `PropType` enum (Decoration, Solid, Interactable)
- Optional interaction callback or ID

---

## UI Ideas

- Player health bar
- Damage flash / knockback feedback
- Enemy health (optional)
- Debug overlay (FPS, coordinates, hitboxes)

---

## Milestone Ideas

- **M1:** player attack input + enemy damage
- **M2:** collisions with world and props
- **M3:** enemy AI (patrol/chase/attack)
- **M4:** UI and game state (menu, game over)
- **M5:** content (more levels, enemies, items)
