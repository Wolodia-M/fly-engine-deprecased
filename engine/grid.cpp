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

// Libs
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <vector>
using namespace std;
// Files
#include "texture_atlas.hpp"
#include "atlas_mapping.hpp"
// Header
#include "grid.hpp"
// Realization
void EngineClassGrid::initGrid(string _level, int _rows, int _columns)
{
    for(int x = 0; x < 100; x++)
    {
        for(int y = 0; y < 100; y++)
        {
            textureIdxGrid[y][x] = TextureId::NONE;
        }
    }
    level = _level;
    rows = _rows;
    columns = _columns;
    char buff;
    string temp;
    ifstream levelFile;
    levelFile.open(level);
    getline(levelFile, temp);
    getline(levelFile, temp);
    getline(levelFile, temp);
    getline(levelFile, temp);
    getline(levelFile, temp);
    getline(levelFile, temp);
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            levelFile >> buff;
#if defined(DEBUG) && defined(DEBUG_DECODE_LEVEL)
            cout << buff;
#endif // defined(DEBUG) && defined(DEBUG_DECODE_LEVEL)
            switch (buff)
            {
            case '0':
                textureIdxGrid[y][x] = TextureId::NONE;
                break;
            case '1':
                textureIdxGrid[y][x] = TextureId::DUMMY_TILE;
                break;
            // Next cases for level parsing
            }
        }
    }
    enemyCnt = 0;
    enemies.clear();
    string tempE[4] = {"", "", "", ""};
    while(1)
    {
        levelFile >> tempE[0];
        levelFile >> tempE[1];
        levelFile >> tempE[2];
        levelFile >> tempE[3];
        if(tempE[0] == "endlvl") goto end;
        //printf("%s, %s, %s, %s", tempE[0], tempE[1], tempE[2], tempE[3]);
        if(tempE[0] != "endlvl")
        {
            enemyCnt++;
            enemy tmp;
            tmp.start_x = stoi(tempE[0]);
            tmp.start_y = stoi(tempE[1]);
            tmp.end_x   = stoi(tempE[2]);
            tmp.end_y   = stoi(tempE[3]);
            tmp.pos_x   = tmp.start_x;
            tmp.pos_y   = tmp.start_y;
            calc.DDALine(tmp.start_x, tmp.start_y, tmp.end_x, tmp.end_y, &tmp);
            tmp.max     = (tmp.x.size() - 1);
            tmp.counter = 0;
            tmp.dir = 1;
            enemies.push_back(tmp);
        }
    }
    end:
    levelFile.close();
}
void EngineClassGrid::initAtlas(string path)
{
    textureAtlas = path;
    SDL_Surface *temps = NULL;
    temps = IMG_Load(path.c_str());
#if defined(DEBUG) && defined(DEBUG_LOAD_TEXTURES)
    if (temps == NULL)
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
#endif // defined(DEBUG) && defined(DEBUG_LOAD_TEXTURES)
    atlasTexture = SDL_CreateTextureFromSurface(render, temps);
#if defined(DEBUG) && defined(DEBUG_LOAD_TEXTURES)
    if (atlasTexture == NULL)
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
#endif // defined(DEBUG) && defined(DEBUG_LOAD_TEXTURES)
    SDL_FreeSurface(temps);
    atlas.init(atlasTexture);
}
void EngineClassGrid::init(SDL_Renderer *_render)
{
    render = _render;
}
void EngineClassGrid::drawEnemies()
{
    int x = tile_0_x * 16;
    int y = tile_0_y * 16;
    for(int i = enemyCnt; i > 0; i--)
    {
        enemy *e = &enemies.at(i - 1);
        int _x = e->pos_x;
        int _y = e->pos_y;
        atlas.drawImg(render, TextureId::DUMMY_ENEMY, (_x - x), (_y - y));
    }
}
void EngineClassGrid::draw(int _x, int _y)
{
    int ypos, xpos;
    if (_y >= rows - 15)
    {
        ypos = rows - 15;
    }
    else
    {
        ypos = _y;
    }
    if (_x >= columns - 20)
    {
        xpos = columns - 20;
    }
    else
    {
        xpos = _x;
    }
    for (int y = ypos; y < ypos + 15; y++)
    {
        for (int x = xpos; x < xpos + 20; x++)
        {
            if (x < rows || y < columns)
            {
                atlas.drawImg(render, textureIdxGrid[y][x], (x - xpos) * 16, (y - ypos) * 16);
            }
        }
    }
    tile_0_x = xpos;
    tile_0_y = ypos;
}
bool EngineClassGrid::getCollision(int _x, int _y, int _dx, int _dy, int _posx, int _posy, int _dir)
{
    int x, y;
    // Start of custom collision section, for example - for doors
    if (textureIdxGrid[_posy + 1][_posx] == TextureId::DUMMY_TILE_DOOR_HORIZONTAL && _dy > 6)
    {
        if (_dir == 1 || _dir == 2) return true;
        if (_dir == 3 || _dir == 4) return false;
    }
    if (textureIdxGrid[_posy][_posx + 1] == TextureId::DUMMY_TILE_DOOR_VERTICAL && _dx > 6)
    {
        if (_dir == 1 || _dir == 2) return false;
        if (_dir == 3 || _dir == 4) return true;
    }
    if (textureIdxGrid[_posy][_posx] == TextureId::DUMMY_TILE_DOOR_HORIZONTAL)
    {
        if (_dir == 1 || _dir == 2) return true;
        if (_dir == 3 || _dir == 4) return false;
    }
    if (textureIdxGrid[_posy][_posx] == TextureId::DUMMY_TILE_DOOR_VERTICAL)
    {
        if (_dir == 1 || _dir == 2) return false;
        if (_dir == 3 || _dir == 4) return true;
    }
    // End of custom collision section
    switch (textureIdxGrid[_y][_x])
    {
    case TextureId::NONE:
        return true;
        break;
    case TextureId::DUMMY_TILE:
        return false;
        break;
    // Collision for your tiles, true - player can walk, false - cannot
    }
}
void EngineClassGrid::drawPlayer(int _x, int _y, int _dx, int _dy)
{
    int x = tile_0_x;
    int y = tile_0_y;
    static bool state = 0;
    static int cnt = 0;
    if (state)
    {
        atlas.drawImg(render, TextureId::DUMMY_PLAYER_1, (((_x - x) * 16) + _dx), (((_y - y) * 16) + _dy)); 
    }
    else
    {
        atlas.drawImg(render, TextureId::DUMMY_PLAYER_2, (((_x - x) * 16) + _dx), (((_y - y) * 16) + _dy));
    }
    cnt++;
    if (cnt == 256)
    {
        cnt = 0;
        state = !state;
    }
}
void EngineClassGrid::getNewEnemyPos()
{
    for(int i = enemyCnt; i > 0; i--)
    {
        enemy *e = &enemies.at(i - 1);
        if(e->dir == 1)
        {
            if(e->counter == e->max - 1) e->dir = 0;
            e->gx = (e->x.at(e->counter) / 16);
            e->gy = (e->y.at(e->counter) / 16);
            e->pos_x = e->x.at(e->counter);
            e->pos_y = e->y.at(e->counter);
            e->counter++;
        }
        else if (e->dir == 0)
        {
            if(e->counter == 1) e->dir = 1;
            e->gx = (e->x.at(e->counter) / 16);
            e->gy = (e->y.at(e->counter) / 16);
            e->pos_x = e->x.at(e->counter);
            e->pos_y = e->y.at(e->counter);
            e->counter--;
        }
    }
}
bool EngineClassGrid::getPlayerEnemyCollision(int _x, int _y)
{
    bool ret;
    for(int i = enemyCnt; i > 0; i--)
    {
        enemy *e = &enemies.at(i - 1);
        if(((e->gx == _x) || (e->gx == (_x + 1)) || (e->gx == (_x - 1))) && \
        ((e->gy == _y) || (e->gy == (_y + 1)) || (e->gy == (_y - 1))))
        {
            ret = true;
        }
    }
    return ret;
}
void EngineClassGrid::cheater()
{
    cheat = !cheat;
}
