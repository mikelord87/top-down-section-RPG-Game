#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

#define ENEMY_CHARACTER_PATH "characters/goblin_idle_spritesheet.png"
#define ENEMY_CHARACTER_IDLE_PATH "characters/goblin_idle_spritesheet.png"
#define ENEMY_CHARACTER_RUN_PATH "characters/goblin_run_spritesheet.png"

class Enemy : public BaseCharacter
{
    public:
        Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
        virtual void tick(float deltaTime) override;
        void setTarget(Character* character);
        virtual Vector2 getScreenPos(void) override; 

    private:
        Character* target;
        float damagePerSec{10.f};
        float radius{25.0f};
};