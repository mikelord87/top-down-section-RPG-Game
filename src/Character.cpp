/**
 * @file Character.cpp
 * @brief Implements the player-controlled Character logic.
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
        windowWidth(winWidth),
        windowHeight(winHeight)
{
    // Frame size is derived from the spritesheet width.
    width = texture.width / maxFrames;
    height = texture.height;
}

/**
 * @brief Keep the player centered in the window.
 *
 * This returns a screen position such that the character's sprite is drawn around
 * the center of the window (accounting for scaling).
 */
Vector2 Character::getScreenPos(void)
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };
}

/**
 * @brief Handle input, update movement/animation, and draw the player and weapon.
 *
 * - Uses WASD keys to set velocity.
 * - Calls BaseCharacter::tick() to animate/move/draw the character.
 * - Draws the sword on the appropriate side based on facing direction.
 * - Builds weaponCollisionRec for hit detection.
 *
 * @param deltaTime Frame delta time in seconds.
 */
void Character::tick(float deltaTime)
{
    if(!getAlive()) return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0f;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0f;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

    if(rightLeft > 0.0f)
    {
        origin = {0.0f, weapon.height * scale};
        offset = {35.0f, 55.0f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.0f : 0.0f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.0f, 55.0f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.0f : 0.0f;
    }

    // Draw the sword
    Rectangle source{0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    // Debug draw:
    // DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}

/**
 * @brief Reduce health and update alive state.
 * @param damage Damage amount to subtract from health.
 */
void Character::takeDamage(float damage)
{
    health -= damage;

    if(health <= 0.0f)
    {
        setAlive(false);
    }
}