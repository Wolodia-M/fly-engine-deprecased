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

#ifndef ENGINECLASSMAIN_HPP
#define ENGINECLASSMAIN_HPP
// Libs
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;
// Files
#include "engine/grid.hpp"
class EngineClassMain
{
    public:
        /**
         * @brief Load texture atlass 
         * 
         * @param path Path to texture
         */
        void loadTextureAtlas(string path);
        /**
         * @brief Load music for level
         * 
         * @param path Path to file
         */
        void loadLevelMusic(string path);
        /**
         * @brief Load sounds
         * 
         * @param death Path to death sound 
         * @param walk Path to walk sound
         * @param end Path to end-level sound
         */
        void loadSounds(string death, string walk, string end);
        /**
         * @brief Load level data
         * 
         * @param path Path to level
         */
        void loadLevel(string path);
        /**
         * @brief Move character
         * 
         * @param dir Direction to move. 1 - down, 2 - up, 3 - right, 4 - left
         */
        void move(int dir);
        /**
         * @brief Engine tick
         * 
         */
        void tick();
        /**
         * @brief Get SDL2 main surface
         * 
         * @param _rend main SDL_Renderer
         */
        void getSDL2data(SDL_Renderer* _rend);
        /**
         * @brief Graphick update
         * 
         */
        void draw();
        /**
         * @brief Get the State object
         * 
         * @return int state of engine
         */
        int getState();
        /**
         * @brief Set the State object
         * 
         * @param val new engine state
         */
        void setState(int val);
        /**
         * @brief Go to next level
         * 
         */
        void nextlevel();
        void cheat();
        bool cheated = 0;
        static const int ENDSTATE = 0xFFFF;
    private:
        void convertPlayerPos();
        EngineClassGrid grid;
        ifstream levelFile;
        string texture;
        string mus;
        string sound[3];
        Mix_Chunk *death = NULL;
        Mix_Chunk *end = NULL;
        Mix_Chunk *step = NULL;
        string levelPath = "";
        SDL_Renderer* rend;
        int state = 0;
        bool end_flag = false;
        bool dead_flag = false;
        struct {
            int grid_m_x, grid_m_y; 
            int grid_x, grid_y;
        }player;
        struct {
            int start_x, start_y;
            int end_x, end_y;
        }levelData;
};
#endif // ENGINECLASSMAIN_HPP