/**
 * @file Prop.h
 * @brief Declares a static world prop (e.g., rocks/logs) with basic collision.
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#ifndef PROP_H
#define PROP_H

#include "raylib.h"

/**
 * @class Prop
 * @brief A static world object that can be rendered and collided with.
 *
 * Props are positioned in world space and rendered relative to the player's world position.
 */
class Prop
{
    public:
        /**
         * @brief Construct a prop at a world position with a texture.
         * @param pos World position (top-left reference).
         * @param tex Texture to render for the prop.
         */
        Prop(Vector2 pos, Texture2D tex);

        /**
         * @brief Render the prop relative to the given player world position.
         * @param knightPos Player world position used to compute on-screen position.
         */
        void Render(Vector2 knightPos);

        /**
         * @brief Get prop collision rectangle in screen space.
         * @param knightPos Player world position used to compute on-screen position.
         * @return Screen-space collision rectangle.
         */
        Rectangle getCollisionRec(Vector2 knightPos);

    private:
        Vector2 worldPos{};     ///< Prop position in world coordinates.
        Texture2D texture{};    ///< Prop texture (copied handle).
        float scale{4.0f};      ///< Draw scale factor.
};

#endif // PROP_H