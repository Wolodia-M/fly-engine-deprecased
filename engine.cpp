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

#include <string>
#include <SDL2/SDL.h>
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <vector>
#include "filesystem"
using namespace std;
#include "engine.hpp"
void EngineClassMain::loadLevel(string path)
{
    if (!filesystem::exists(path.c_str()))
    {
        EngineClassMain::setState(EngineClassMain::ENDSTATE);
        return;
    }
    if (path != levelPath)
    {
        end_flag = false;
        levelFile.open(path);
        string buff;
        getline(levelFile, buff);
        int rows = stoi(buff);
        getline(levelFile, buff);
        int columns = stoi(buff);
        getline(levelFile, buff);
        player.grid_x = stoi(buff);
        levelData.start_x = player.grid_x;
        getline(levelFile, buff);
        player.grid_y = stoi(buff);
        levelData.start_y = player.grid_y;
        getline(levelFile, buff);
        levelData.end_x = stoi(buff);
        getline(levelFile, buff);
        levelData.end_y = stoi(buff);
        levelPath = path;
        #if defined(DEBUG) && defined(DEBUG_GET_LEVEL_HELPER_DATA)
        printf(levelPath.c_str());
        printf("\nx pos: %d\n", levelData.player_x);
        printf("y pos: %d\n", levelData.player_y);
        printf("level end x pos: %d\n", levelData.end_x);
        printf("level end y pos: %d\n", levelData.end_y);
        #endif // defined(DEBUG) && defined(DEBUG_GET_LEVEL_HELPER_DATA)
        levelFile.close();
        grid.initGrid(levelPath, rows, columns);
    }
}
void EngineClassMain::move(int dir)
{
    switch(dir)
    {
    case 1:
        if(player.grid_y < (grid.rows - 1) && grid.getCollision(player.grid_x, (player.grid_y + 1), player.grid_m_x, player.grid_m_y, player.grid_x, player.grid_y, dir))
        {
            player.grid_m_y += 2;
        }
        break;
    case 2:
        if(player.grid_y > 0 && (((player.grid_m_y - 2) >= 0) || grid.getCollision(player.grid_x, (player.grid_y - 1), player.grid_m_x, player.grid_m_y, player.grid_x, player.grid_y, dir)))
        {
            player.grid_m_y -= 2;
        }
        break;
    case 3:
        if(player.grid_x < (grid.columns - 1) && grid.getCollision((player.grid_x + 1), player.grid_y, player.grid_m_x, player.grid_m_y, player.grid_x, player.grid_y, dir))
        {
            player.grid_m_x += 2;
        }
        break;
    case 4:
        if(player.grid_x > 0 && (((player.grid_m_x - 2) >= 0) || grid.getCollision((player.grid_x - 1), player.grid_y, player.grid_m_x, player.grid_m_y, player.grid_x, player.grid_y, dir)))
        {
            player.grid_m_x -= 2;
        }
        break;
    }
    EngineClassMain::convertPlayerPos();
}
void EngineClassMain::tick()
{
    if (dead_flag == true)
    {
        player.grid_m_x = 0;
        player.grid_m_y = 0;
        player.grid_x = levelData.start_x;
        player.grid_y = levelData.start_y;
        Mix_PlayChannel(-1, EngineClassMain::death, 0);
    }
    //printf("\nx: %d y: %d", player.grid_x, player.grid_y);
    if (player.grid_x == levelData.end_x && player.grid_y == levelData.end_y)
    {
        EngineClassMain::nextlevel();
    }
    grid.getNewEnemyPos();
    dead_flag = grid.getPlayerEnemyCollision(player.grid_x, player.grid_y);
}
void EngineClassMain::draw()
{
    if (player.grid_x > 0 && player.grid_y > 0)
    {
        grid.draw(player.grid_x - 1, player.grid_y - 1);
    }
    else if (player.grid_x > 0)
    {
        grid.draw(player.grid_x - 1, player.grid_y);
    }
    else if (player.grid_y > 0)
    {
        grid.draw(player.grid_x, player.grid_y - 1);
    }
    else
    {
        grid.draw(player.grid_x, player.grid_y);
    }
    grid.drawPlayer(player.grid_x, player.grid_y, player.grid_m_x, player.grid_m_y);
    grid.drawEnemies();
}
void EngineClassMain::getSDL2data(SDL_Renderer* _rend)
{
    rend = _rend;
    grid.init(rend);
}
void EngineClassMain::loadTextureAtlas(string path)
{
    texture = path;
    grid.initAtlas(texture);
}
void EngineClassMain::convertPlayerPos()
{
    if(player.grid_m_x > 15) {player.grid_x++; player.grid_m_x -= 15;}
    if(player.grid_m_y > 15) {player.grid_y++; player.grid_m_y -= 15;}
    if(player.grid_m_x < 0) {player.grid_x--; player.grid_m_x += 15;}
    if(player.grid_m_y < 0) {player.grid_y--; player.grid_m_y += 15;}
}
void EngineClassMain::nextlevel()
{
    if (end_flag == false && player.grid_x != 0 && player.grid_y != 0)
    {
        Mix_PlayChannel(-1, EngineClassMain::end, 0);
        EngineClassMain::setState(EngineClassMain::getState() + 1);
        end_flag = true;
    }
}
void EngineClassMain::loadSounds(string _death, string _walk, string _end)
{
    EngineClassMain::sound[0] = _death;
    EngineClassMain::sound[1] = _walk;
    EngineClassMain::sound[2] = _end;
    EngineClassMain::death = Mix_LoadWAV(_death.c_str());
    EngineClassMain::end = Mix_LoadWAV(_end.c_str());
}
void EngineClassMain::cheat()
{
    EngineClassMain::cheated = 1;
    grid.cheater();
}
void EngineClassMain::setState(int val){state = val;}
int EngineClassMain::getState(){return state;}