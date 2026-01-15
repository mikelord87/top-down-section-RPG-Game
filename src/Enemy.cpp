/**
 * @file Enemy.cpp
 * @brief Implements Enemy AI behavior (chase and collision damage).
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#include "Enemy.h"
#include "raymath.h"

/**
 * @brief Initialize enemy animation parameters and spawn location.
 */
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

/**
 * @brief Chase the target and apply damage when colliding.
 *
 * The enemy moves towards the target screen position (relative movement) and stops
 * when within a small radius. Damage is applied continuously while AABBs overlap.
 *
 * @param deltaTime Frame delta time in seconds.
 */
void Enemy::tick(float deltaTime)
{
    if(!getAlive()) return;
    // Get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius)
    {
        velocity = {};
    }
    BaseCharacter::tick(deltaTime);

    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

/**
 * @brief Compute screen position relative to the target's world position.
 *
 * @return Screen position for drawing/collision.
 */
Vector2 Enemy::getScreenPos(void)
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

/**
 * @brief Assign the target character pointer.
 *
 * @param character Non-null pointer to a Character.
 */
void Enemy::setTarget(Character* character)
{
    if(nullptr != character)
    {
        target = character;
    }
}