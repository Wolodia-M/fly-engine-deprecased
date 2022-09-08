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

#pragma once
#include <SDL2/SDL.h>
#include "atlas_mapping.hpp"
const SDL_Rect TEXTURE_REGIONS[] =
{
    SDL_Rect{0, 0, 0, 0},    // NONE
    SDL_Rect{0, 0, 0, 0},    // DUMMY_TILE
    SDL_Rect{0, 0, 0 ,0},    // DUMMY_ENEMY
    SDL_Rect{0, 0, 0, 0},    // DUMMY_PLAYER_1
    SDL_Rect{0, 0, 0, 0},    // DUMMY_PLAYER_2
    SDL_Rect{0, 0, 0, 0},    // DUMMY_TILE_DOOR_VERTICAL
    SDL_Rect{0, 0, 0, 0}     // DUMMY_TILE_DOOR_HORIZONTAL
    // Here ypu need to map TextureId enum to SDL_Rects with correct sectors of texture atlass
};
class TextureAtlas
{
public:
    /**
     * @brief Construct a new Texture Atlas object
     *
     * @param atlas Texture fo atlas
     */
    void init(SDL_Texture *atlas)
    {
        atlasImg = atlas;
    }
    int getHight(TextureId id)
    {
        return TEXTURE_REGIONS[static_cast<int>(id)].h;
    }
    int getWight(TextureId id)
    {
        return TEXTURE_REGIONS[static_cast<int>(id)].w;
    }
    /**
     * @brief Draw texture
     *
     * @param renderer SDL2 object
     * @param id Id of texture
     * @param x X render pos of image
     * @param y Y render pos of image
     */
    void drawImg(SDL_Renderer *renderer, TextureId id, int x, int y)
    {
        // Get id
        int tidx = static_cast<int>(id);
        // Get texture from ID
        dest.x = x;
        dest.y = y;
        dest.w = TEXTURE_REGIONS[tidx].w;
        dest.h = TEXTURE_REGIONS[tidx].h;
        // Draw texture
        SDL_RenderCopy(renderer, atlasImg, &TEXTURE_REGIONS[tidx], &dest);
    }

private:
    SDL_Texture *atlasImg;
    SDL_Rect src, dest;
};