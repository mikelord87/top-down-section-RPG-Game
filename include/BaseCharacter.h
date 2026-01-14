#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

#define KNIGHT_CHARACTER_PATH "assets/characters/knight_idle_spritesheet.png"
#define KNIGHT_CHARACTER_IDLE_PATH "assets/characters/knight_idle_spritesheet.png"
#define KNIGHT_CHARACTER_RUN_PATH "assets/characters/knight_run_spritesheet.png"

class BaseCharacter
{
    public:
        BaseCharacter();
        Vector2 getWorldPos(void) { return worldPos; }
        void undoMovement(void);
        Rectangle getCollisionRec(void);
        virtual void tick(float deltaTime);
        virtual Vector2 getScreenPos() = 0;
        bool getAlive(){return alive;}
        void setAlive(bool isAlive){alive = isAlive;}

    protected:
        Texture2D texture{LoadTexture(KNIGHT_CHARACTER_PATH)};
        Texture2D idle{LoadTexture(KNIGHT_CHARACTER_PATH)};
        Texture2D run{LoadTexture(KNIGHT_CHARACTER_RUN_PATH)};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        // 1 : facing right, -1 : facing left
        float rightLeft{1.0f};
        // Animation variables
        float runningTime{};
        int frame{};
        int maxFrames{6};
        float updateTime{1.0f / 12.0f};
        float speed{4.0f};
        float width{};
        float height{};
        float scale{4.0f};
        Vector2 velocity{};

    private:
        bool alive{true};
};

#endif