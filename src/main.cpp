/**
 * @file main.cpp
 * @brief Entry point for the top-down RPG demo.
 *
 * Sets up the raylib window, loads assets, creates game objects, and runs the main loop.
 * 
 * @author Miguel Rios
 * @date 01/14/2026
 */

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

/** 
 * @def WINDOW_DIM_SIZE
 * @brief Number of window dimension entries (width, height). 
 */
#define WINDOW_DIM_SIZE 2

/** 
 * @def WINDOW_DIM_WIDTH
 * @brief Window width in pixels.
 */
#define WINDOW_DIM_WIDTH 384

/** 
 * @def WINDOW_DIM_HEIGHT
 * @brief Window height in pixels.
 */
#define WINDOW_DIM_HEIGHT 384

/** 
 * @def GAME_FPS
 * @brief Target frame rate.
 */
#define GAME_FPS 60   

/** 
 * @def WINDOW_TITLE
 * @brief Window title.
 */
#define WINDOW_TITLE "RPG Game"

/** 
 * @def GAME_WORLD_MAP_PATH
 * @brief World map texture path.
 */
#define GAME_WORLD_MAP_PATH "assets/nature_tileset/WorldMap.png"

/** 
 * @def GAME_PROPS_ROCK_PATH
 * @brief Rock prop texture path.
 */
#define GAME_PROPS_ROCK_PATH "assets/nature_tileset/Rock.png"

/** 
 * @def GAME_PROPS_LOG_PATH
 * @brief Log prop texture path.
 */      
#define GAME_PROPS_LOG_PATH "assets/nature_tileset/Log.png"

/** 
 * @def GAME_WORLD_MAP_SCALE
 * @brief World map draw scale.
 */
#define GAME_WORLD_MAP_SCALE 4.0f

/**
 * @brief Program entry point.
 *
 * Creates the window and game entities (player, props, enemies), then runs an update/render loop
 * until the window is closed.
 *
 * @return Exit code (0 on normal completion).
 */
int main()
{
    // Window dimension
    const int windowDimensions[WINDOW_DIM_SIZE] = {WINDOW_DIM_WIDTH, WINDOW_DIM_HEIGHT};

    // Initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], WINDOW_TITLE);

    // Load World Map texture
    Texture2D worldMap = LoadTexture(GAME_WORLD_MAP_PATH);
    Vector2 wmPos{0.0f, 0.0f};
    const float mapScale(4.0f);

    Character knight(windowDimensions[0], windowDimensions[1]);

    Prop props[2]{
        Prop{Vector2{600.0f, 300.0f}, LoadTexture(GAME_PROPS_ROCK_PATH)},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture(GAME_PROPS_LOG_PATH)}
    };

    Enemy goblin{
        Vector2{800.0f, 300.0f},
        LoadTexture(ENEMY_CHARACTER_IDLE_PATH),
        LoadTexture(ENEMY_CHARACTER_RUN_PATH)
    };
    
    Enemy slime{
        Vector2{500.0f, 700.0f},
        LoadTexture(ENEMY_SLIME_IDLE_PATH),
        LoadTexture(ENEMY_SLIME_RUN_PATH)
    };

    Enemy* enemies[]
    {
        &goblin,
        &slime
    };

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(GAME_FPS);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        wmPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        // Draw the World Map
        DrawTextureEx(worldMap, wmPos, 0.0, GAME_WORLD_MAP_SCALE, WHITE);

        // Draw the props
        for(auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if(!knight.getAlive()) // Character is not alive
        {
            DrawText("Game Over!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.0f, 45.0f, 40, RED);
        }

        // Game logic
        knight.tick(GetFrameTime());

        // Check map bounds
        if(knight.getWorldPos().x < 0.0f ||
           knight.getWorldPos().y < 0.0f ||
           knight.getWorldPos().x + WINDOW_DIM_WIDTH > worldMap.width * mapScale ||
           knight.getWorldPos().y + WINDOW_DIM_HEIGHT > worldMap.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check prop collisions
        for(auto prop : props)
        {
            if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // Update enemies
        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // Player attack (mouse click)
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(worldMap);
    /*UnloadTexture(knight);
    UnloadTexture(knight_idle);
    UnloadTexture(knight_run);*/
    CloseWindow();
}