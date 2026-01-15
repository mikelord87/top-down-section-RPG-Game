/**
 * @file Prop.cpp
 * @brief Implements Prop rendering and collision helpers.
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
        worldPos(pos),
        texture(tex)
{

}

/**
 * @brief Draw the prop in screen space based on the player's world position.
 * @param knightPos Player world position.
 */
void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0.0f, scale, WHITE);
}

/**
 * @brief Build the prop's collision rectangle in screen space.
 * @param knightPos Player world position.
 * @return Screen-space collision rectangle.
 */
Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale};
}