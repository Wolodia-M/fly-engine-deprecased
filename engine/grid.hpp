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

#ifndef ENGINECLASSGRID_HPP
#define ENGINECLASSGRID_HPP
#include "texture_atlas.hpp"
typedef struct{
    int start_x, start_y;
    int end_x, end_y;
    int pos_x, pos_y;
    int gx, gy;
    vector<int> x;
    vector<int> y;
    int counter;
    int max;
    bool dir;
}enemy;
#include "lines.hpp"
class EngineClassGrid
{
public:
    /**
     * @brief Init grid rendere
     *
     * @param render SDL renderer
     */
    void init(SDL_Renderer *_render);
    /**
     * @brief Init level grid with starting point
     *
     * @param path Path to level file
     * @param x Starting x pos of player
     * @param y Starting y pos of player
     */
    void initGrid(string _level, int _rows, int _columns);
    /**
     * @brief Init texture atlass
     *
     * @param path Path to file
     */
    void initAtlas(string path);
    /**
     * @brief Draw on screan
     *
     */
    void draw(int _x, int _y);
    /**
     * @brief Get collision of object on _x _y 
     * 
     * @param _x x position of object
     * @param _y y position on object
     * @param _dx shift on x axis
     * @param _dy shift on y axis
     * @param _posx x position of player
     * @param _ypos y position of player
     * @param _dir direction of player
     * 
     * @return true Collision passed
     * @return false Wall
     */
    bool getCollision(int _x, int _y, int _dx, int _dy, int _posx, int _posy, int _dir);
    /**
     * @brief Draw player at _x _y with _dx and _dy
     * 
     * @param _x x position of player
     * @param _y y position of player
     * @param _dx shift on x axis
     * @param _dy shift on y axis
     */
    void drawPlayer(int _x, int _y, int _dx, int _dy);
    /**
     * @brief Draw all enemies
     * 
     */
    void drawEnemies();
    /**
     * @brief Calculate new position of enemy
     * 
     */
    void getNewEnemyPos();
    /**
     * @brief Check player collision with enemy
     * 
     * @param _x x position of player
     * @param _y y position of player
     * 
     * @return true player dead
     * @return false player alive
     */
    bool getPlayerEnemyCollision(int _x, int _y);
    void cheater();
    int rows, columns;
private:
    int tile_0_x, tile_0_y;
    string textureAtlas;
    string level;
    TextureAtlas atlas;
    SDL_Renderer *render;
    TextureId textureIdxGrid[100][100];
    SDL_Texture *atlasTexture;
    // start_x1 start_y1 end_x1 end_y1 start_x2 start_y2 end_x2 end_y2 ... 
    vector<enemy> enemies;
    int enemyCnt;
    lines calc;
    bool cheat = false;
};
#endif