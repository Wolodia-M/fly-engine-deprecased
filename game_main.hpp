//  Simple game engine that use SDL2
//  Copyright (C) 2022 WolodiaM
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

// Main header of a game
namespace game
{
    /**
     * @brief Init game
     *
     */
    void init();
    /**
     * @brief Game logic update
     *
     */
    void tick();
    /**
     * @brief Game graphick update
     *
     */
    void frame();
    /**
     * @brief Clean all after game
     *
     */
    void destroy();
}
// Body of a functions
void game::init()
{
    // Init atexit()
    atexit(destroy);
    // Init SDL graphick and mixer
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
    // Start audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    // Setup SDL window
    window = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREAN_WIGHT, SCREAN_HEIGHT, SDL_WINDOW_SHOWN);
#if !defined(DEBUG_WINDOVED) || !defined(DEBUG)
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
#endif
    // Init SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Init image loading
    IMG_Init(IMG_INIT_PNG);
    // Init SDL2 for engine class
    engine.getSDL2data(renderer);
    // Init engine
    engine.loadTextureAtlas("media/art/texture_atlas.png");
    engine.loadSounds("path to death sound", "not used now, please wait for next version of engine", "path to end sound");
    // Your init
}
void game::tick()
{
    // Get non-state events
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            is_run = 0;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            SDL_KeyboardEvent *key = &event.key;
            if (key->keysym.scancode == 0x29)
            {
                is_run = 0;
            }
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                engine.move(2);
                break;
            case SDLK_DOWN:
                engine.move(1);
                break;
            case SDLK_LEFT:
                engine.move(4);
                break;
            case SDLK_RIGHT:
                engine.move(3);
                break;
            case SDLK_w:
                engine.move(2);
                break;
            case SDLK_s:
                engine.move(1);
                break;
            case SDLK_a:
                engine.move(4);
                break;
            case SDLK_d:
                engine.move(3);
                break;
            }
            // You control
#if defined(DEBUG) && defined(DEBUG_KEY)
            printf("Key: %x", key->keysym.sym);
#endif // DEBUG && DEBUG_KEY
        }
    }
    static clock_t tmr = 0;
    static bool tmrRun = false;
    static int lastLevel = -1;
    // State of a game
    // 0 -> main menu, 0xFFFF -> end menu, 1 - 0xFFFE -> levels
    if (engine.getState() == 0)
    {
        // Start screan of game
    }
    else if (engine.getState() != 0 && engine.getState() != engine.ENDSTATE)
    {
        string temp = "data/levels/level";
        temp += to_string((engine.getState() - 1));
        temp += ".level";
        engine.loadLevel(temp);
    }
    else if (engine.getState() == engine.ENDSTATE)
    {
        // End screan of game
    }
    if (tmrRun == false)
    {
        tmr = clock();
        tmrRun = true;
    }
    if (engine.getState() != 0 && engine.getState() != engine.ENDSTATE && tmrRun && clock() - tmr > (CLOCKS_PER_SEC / 50))
    {
        engine.tick();
        tmrRun = false;
    }
}
void game::frame()
{
    // Update graphick
    SDL_RenderPresent(renderer);
    if (engine.getState() != 0 & engine.getState() != engine.ENDSTATE)
    {
        engine.draw();
    }
}
void game::destroy()
{
    // Clear renderer
    SDL_DestroyRenderer(renderer);
    // Clear window
    SDL_DestroyWindow(window);
    // Stop SDL2 subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
#ifdef DEBUG
    // For better console output
    printf("\n");
#endif
}