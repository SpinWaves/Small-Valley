// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __CUBE__
#define __CUBE__

#include <pch.h>
#include <maths/vec3.h>
#include <graphics/textures.h>
#include <graphics/shaders.h>

class Cube
{
    public:
        Cube() = default;
        Cube(Vec3<float> pos, Vec3<float> size);
        Cube(float x, float y, float z, float w = 0, float h = 0, float d = 0);
        
        void create(class World& world);

        void set_pos(Vec3<float> pos) noexcept;
        void set_pos(float x, float y, float z) noexcept;

        void set_size(Vec3<float> size) noexcept;
        void set_size(float x, float y, float z) noexcept;

        void render();

        ~Cube();

    private:
        GLuint _vbo = 0;
        GLuint _vao = 0;
        size_t _vertex_count = 0;

        Vec3<float> _vPos;
        Vec3<float> _vSize;
};

#endif // __CUBE__
