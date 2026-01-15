/**
 * @file Enemy.h
 * @brief Declares the Enemy character type (AI-controlled).
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

/** @def ENEMY_CHARACTER_IDLE_PATH
 *  @brief Texture path for goblin idle animation spritesheet.
 */
#define ENEMY_CHARACTER_IDLE_PATH "assets/characters/goblin_idle_spritesheet.png"

/** @def ENEMY_CHARACTER_RUN_PATH
 *  @brief Texture path for goblin run animation spritesheet.
 */
#define ENEMY_CHARACTER_RUN_PATH "assets/characters/goblin_run_spritesheet.png"

/** @def ENEMY_SLIME_RUN_PATH
 *  @brief Texture path for slime run animation spritesheet.
 */
#define ENEMY_SLIME_RUN_PATH "assets/characters/slime_run_spritesheet.png"

/** @def ENEMY_SLIME_IDLE_PATH
 *  @brief Texture path for slime idle animation spritesheet.
 */
#define ENEMY_SLIME_IDLE_PATH "assets/characters/slime_idle_spritesheet.png"

/**
 * @class Enemy
 * @brief AI-controlled enemy that chases and damages the player.
 *
 * Enemy uses a target Character to:
 * - Compute screen position relative to the player world position.
 * - Move towards the player until within a stop radius.
 * - Apply continuous damage while colliding with the player.
 */
class Enemy : public BaseCharacter
{
    public:

        /**
         * @brief Construct an enemy at a world position using supplied textures.
         * @param pos World position to spawn the enemy.
         * @param idle_texture Texture for idle animation spritesheet.
         * @param run_texture Texture for run animation spritesheet.
         */
        Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);

        /**
         * @brief Per-frame update: chase the target and apply damage on collision.
         * @param deltaTime Frame delta time in seconds.
         */
        virtual void tick(float deltaTime) override;

        /**
         * @brief Set the player target for this enemy.
         * @param character Pointer to the target Character (must outlive this Enemy).
         */
        void setTarget(Character* character);

        /**
         * @brief Convert enemy world position to screen position relative to target.
         * @return Screen position where the enemy should be drawn.
         */
        virtual Vector2 getScreenPos(void) override; 

    private:
        Character* target;          ///< Target character to chase (non-owning pointer).
        float damagePerSec{10.f};   ///< Continuous damage applied per second on collision.
        float radius{25.0f};        ///< Stop distance to prevent jittering close to the target.
};

#endif // ENEMY_H