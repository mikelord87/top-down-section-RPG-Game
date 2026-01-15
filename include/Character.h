/**
 * @file Character.h
 * @brief Declares the player-controlled Character.
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

/** @def KNIGHT_WEAPON_SWORD_PATH
 *  @brief Texture path for the knight sword sprite.
 */
#define KNIGHT_WEAPON_SWORD_PATH "assets/characters/weapon_sword.png"

/** @def CHARACTER_PLAYER_HEALTH
 *  @brief Default player starting/max health (HP).
 *
 * Used to initialize the player's health when the Character is constructed.
 * This value also represents the default maximum health cap unless a gameplay
 * system overrides it.
 */
#define CHARACTER_PLAYER_HEALTH 100.0f

/**
 * @class Character
 * @brief Player-controlled character (knight).
 *
 * Reads keyboard input (WASD) to set movement velocity, draws an equipped sword,
 * and tracks health/alive state.
 */
class Character : public BaseCharacter
{
    public:
        /**
         * @brief Construct a Character centered in the window.
         * @param winWidth Window width in pixels.
         * @param winHeight Window height in pixels.
         */
        Character(int winWidth, int winHeight);
        
        /**
         * @brief Per-frame update for the player character.
         * @param deltaTime Frame delta time in seconds.
         */
        virtual void tick(float deltaTime) override;

        /**
         * @brief Get the knight screen position (keeps player centered).
         * @return Screen position of the knight.
         */
        virtual Vector2 getScreenPos(void) override;

        /**
         * @brief Get the sword collision rectangle in screen space.
         * @return Screen-space collision rectangle for melee hit detection.
         */
        Rectangle getWeaponCollisionRec(){return weaponCollisionRec;}

        /** @brief Get current health (0..CHARACTER_PLAYER_HEALTH). */
        float getHealth() const {return health;}

        /**
         * @brief Apply damage to the character health.
         * @param damage Damage amount to subtract from health.
         */
        void takeDamage(float damage);

    private:
        int windowWidth{};                                          ///< Window width in pixels.
        int windowHeight{};                                         ///< Window height in pixels.
        Texture2D weapon{LoadTexture(KNIGHT_WEAPON_SWORD_PATH)};    ///< Sword sprite.
        Rectangle weaponCollisionRec{};                             ///< Sword collision AABB in screen space.
        float health{CHARACTER_PLAYER_HEALTH};                      ///< Player health; <= 0 implies not alive.
};

#endif