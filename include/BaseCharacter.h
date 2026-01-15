/**
 * @file BaseCharacter.h
 * @brief Declares the BaseCharacter abstract class used by all animated game actors.
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

/** @def KNIGHT_CHARACTER_PATH
 *  @brief Default texture path for the knight character (idle spritesheet).
 */
#define KNIGHT_CHARACTER_PATH "assets/characters/knight_idle_spritesheet.png"

/** @def KNIGHT_CHARACTER_IDLE_PATH
 *  @brief Texture path for the knight idle animation spritesheet.
 */
#define KNIGHT_CHARACTER_IDLE_PATH "assets/characters/knight_idle_spritesheet.png"

/** @def KNIGHT_CHARACTER_RUN_PATH
 *  @brief Texture path for the knight run animation spritesheet.
 */
#define KNIGHT_CHARACTER_RUN_PATH "assets/characters/knight_run_spritesheet.png"

/**
 * @class BaseCharacter
 * @brief Common functionality for animated characters.
 *
 * Handles animation timing, movement integration, simple collision rectangle creation,
 * and drawing to the screen. Derived classes must implement getScreenPos() to map
 * world coordinates to screen coordinates.
 *
 * @note Textures are loaded via LoadTexture() in the member initializers. Ensure you
 *       manage lifetime appropriately (e.g., unload textures at shutdown or add RAII).
 */
class BaseCharacter
{
    public:
        /** @brief Construct a BaseCharacter (loads default textures). */
        BaseCharacter();

        /** @brief Get the character world position (top-left reference). */
        Vector2 getWorldPos(void) { return worldPos; }

        /** @brief Revert movement by restoring the previous frame's world position. */
        void undoMovement(void);

        /**
         * @brief Get the character collision rectangle in screen space.
         * @return Rectangle in screen coordinates for simple AABB collision checks.
         */
        Rectangle getCollisionRec(void);

        /**
         * @brief Per-frame update: advances animation, integrates movement, and draws the sprite.
         * @param deltaTime Frame delta time in seconds.
         */
        virtual void tick(float deltaTime);

        /**
         * @brief Convert world position to screen position for drawing.
         * @return Screen position of the character.
         */
        virtual Vector2 getScreenPos() = 0;

        /** @brief Get the alive state for this character. */
        bool getAlive(){return alive;}

        /** @brief Set the alive state for this character. */
        void setAlive(bool isAlive){alive = isAlive;}

    protected:
        Texture2D texture{LoadTexture(KNIGHT_CHARACTER_PATH)};          ///< Current texture used for drawing.
        Texture2D idle{LoadTexture(KNIGHT_CHARACTER_PATH)};             ///< Idle animation spritesheet.
        Texture2D run{LoadTexture(KNIGHT_CHARACTER_RUN_PATH)};          ///< Run animation spritesheet.
        Vector2 worldPos{};                                             ///< Position in world coordinates.
        Vector2 worldPosLastFrame{};                                    ///< World position in previous frame.
        float rightLeft{1.0f};                                          ///< Facing direction: 1 = right, -1 = left.
        // Animation variables
        float runningTime{};                                            ///< Accumulated time for frame switching.
        int frame{};                                                    ///< Current animation frame index.
        int maxFrames{6};                                               ///< Maximum frame index (inclusive) used by spritesheets.
        float updateTime{1.0f / 12.0f};                                 ///< Seconds per frame.
        float speed{4.0f};                                              ///< Movement speed scalar
        float width{};                                                  ///< Width of one animation frame.
        float height{};                                                 ///< Height of one animation frame.
        float scale{4.0f};                                              ///< Draw scale factor.
        Vector2 velocity{};                                             ///< Desired movement direction this frame.

    private:
        bool alive{true};                                               ///< Alive flag used for game state.
};

#endif