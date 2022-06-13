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
        enum class type { grass, wood, plank };

        Cube() = default;
        Cube(type t) : _type(t) {}
        Cube(type t, Vec3<float> pos, Vec3<float> size);
        Cube(type t, float x, float y, float z, float w = 0, float h = 0, float d = 0);
        
        void create(class World& world);

        void set_pos(class World& world, Vec3<float> pos) noexcept;
        void set_pos(class World& world, float x, float y, float z) noexcept;

        void set_size(class World& world, Vec3<float> size) noexcept;
        void set_size(class World& world, float x, float y, float z) noexcept;

        void render();

        ~Cube();

    private:
        Vec3<float> _vPos;
        Vec3<float> _vSize;

        type _type = type::grass;

        GLuint _vbo = 0;
        GLuint _vao = 0;
        size_t _vertex_count = 0;
};

#endif // __CUBE__
