// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "height_map.h"

uint32_t get_pixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    uint8_t* p = (uint8_t*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
        case 1: return *p;
        case 2: return *(uint16_t*)p;
        case 3:
        {
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        case 4: return *(uint32_t*)p;

        default: return 0;
    }
}

std::vector<std::vector<int>> load_height_map(const char* path, float ratio)
{
    SDL_Surface* image = IMG_Load(path);

    if(!image)
        log::report(log_type::error, "unable to load image for a height map");

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    SDL_LockSurface(image);
    
    std::vector<int> temp;
    std::vector<std::vector<int>> result;

    log::report(log_type::message, "Loading height map...");
    int value = 0;

    for(int i = 0; i < image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
        {
            SDL_GetRGB(get_pixel(image, i, j), image->format, &r, &g, &b);
            if(r != g || r != b || g != b)
                value = 0.212671f * (float)r + 0.715160f * (float)g + 0.072169f * (float)b; // what the fuck is that
            else
                value = r;
            temp.push_back((int)(value * ratio));
        }
        result.push_back(temp);
        temp.clear();
    }

    log::report(log_type::message, "Height map loaded");

    SDL_UnlockSurface(image);

    SDL_FreeSurface(image);

    return std::move(result);
}
