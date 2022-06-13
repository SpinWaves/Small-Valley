// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "textures.h"

Texture::Texture(const char* path)
{
    load_texture(path);
}

void Texture::load_texture(const char* filename, texture_type type)
{
    glEnable(GL_TEXTURE_2D);

    SDL_Surface* image = IMG_Load(filename);

    if(!image)
        log::report(log_type::error, "unable to load image for a texture");

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    SDL_FreeSurface(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    if(!_texture)
        log::report(log_type::error, "unable to generate a texture");
    
    _type = type;
}

Texture::~Texture()
{
    if(_texture != 0)
        free_texture();
}
