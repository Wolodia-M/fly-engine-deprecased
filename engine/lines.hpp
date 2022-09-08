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

#ifndef LINES_HPP
#define LINES_HPP
class lines
{
public:
    void DDALine(int x0, int y0, int x1, int y1, enemy *e)
    {
        x0 *= 16;
        y0 *= 16;
        x1 *= 16;
        y1 *= 16;
        int dx = x1 - x0;
        int dy = y1 - y0;
        int step;
        if (abs(dx) > abs(dy))
            step = abs(dx);
        else
            step = abs(dy);
        float x_incr = (float)dx / step;
        float y_incr = (float)dy / step;
        float x = x0;
        float y = y0;

        for (int i = 0; i < step; i++)
        {
            e->x.push_back(lines::round(x));
            e->y.push_back(lines::round(y));
            x += x_incr;
            y += y_incr;
        }
    }
private:
    int round(float n) {
    if (n - (int)n < 0.5)
        return (int)n;
    return (int)(n + 1);
}
};
#endif