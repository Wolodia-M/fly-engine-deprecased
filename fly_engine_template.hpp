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

// Libraries
// Input / output
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
// Console
#include "stdio.h"
// Work with text
#include "string"
// Randomiser
#include "random"
// For timers
#include "ctime"
// Wor with file
#include "filesystem"
// Namespaces
using namespace std;
// Defines
const int SCREAN_WIGHT = 320;
const int SCREAN_HEIGHT = 240;
const string GAME_NAME = "Name of game";
// Variables
bool is_run = 1;// Objects
bool help_loaded = false;
int temp_level_number;
SDL_Window* window = NULL;              // App window 
SDL_Event event;                        // App event handler
SDL_Renderer* renderer = NULL;          // Renderer
// Files
#include "engine.hpp"
EngineClassMain engine;
#include "game_main.hpp"        // Game header
// My namespaces
using namespace game;           // Game main namespace
