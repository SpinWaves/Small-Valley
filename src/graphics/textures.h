// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __TEXTURES__
#define __TEXTURES__

#include <pch.h>

enum class texture_type { diffuse, specular, normal };

class Texture
{
    public:
        Texture() = default;

        void load_texture(const char* filename, texture_type type = texture_type::diffuse);
        inline void bind_texture()   noexcept { glBindTexture(GL_TEXTURE_2D, _texture); }
        inline static void unbind_texture() noexcept { glBindTexture(GL_TEXTURE_2D, 0); }
        inline void free_texture()   noexcept { glDeleteTextures(1, &_texture); _texture = 0; }
        inline texture_type get_type() const noexcept { return _type; }

        ~Texture();

    private:
        GLuint _texture = 0;
        texture_type _type;
};

#endif // __TEXTURES__
