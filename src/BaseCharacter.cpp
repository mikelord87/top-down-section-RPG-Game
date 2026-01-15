/**
 * @file BaseCharacter.cpp
 * @brief Implements BaseCharacter behavior such as animation, movement, and drawing.
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(/* args */)
{
}

/**
 * @brief Restore world position to the last frame (used to undo invalid movement).
 */
void BaseCharacter::undoMovement(void)
{
    worldPos = worldPosLastFrame;
}

/**
 * @brief Build an AABB collision rectangle in screen space.
 *
 * Uses the current screen position returned by getScreenPos() and the scaled
 * animation frame size.
 *
 * @return Screen-space collision rectangle.
 */
Rectangle BaseCharacter::getCollisionRec(void)
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

/**
 * @brief Update animation, integrate movement, and draw.
 *
 * - Advances animation frame based on deltaTime and updateTime.
 * - Integrates velocity into worldPos (normalized) with the configured speed.
 * - Selects idle or run texture depending on motion.
 * - Resets velocity to zero after applying movement (caller should set velocity every frame).
 *
 * @param deltaTime Frame delta time in seconds.
 */
void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0f)
    {
        // set worldPos = worldPos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    // Draw the character
    Rectangle sourceKnight{frame * width, 0.0f, rightLeft * width, height};
    Rectangle destKnight{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, sourceKnight, destKnight, Vector2{}, 0.0f, WHITE);
}