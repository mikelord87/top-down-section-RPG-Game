#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(/* args */)
{
}

void BaseCharacter::undoMovement(void)
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec(void)
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

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