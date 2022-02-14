// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __CUBE_MESH__
#define __CUBE_MESH__

#include "vertex.h"
#include <pch.h>

const std::vector<Vertex> cube_mesh = {
    // top
    Vertex(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<float>(0, 0, 1),  Vec2<float>(0, 0)),
    Vertex(Vec3<float>(0.5f, -0.5f, -0.5f), Vec3<float>(0, 0, 1),  Vec2<float>(1, 0)),
    Vertex(Vec3<float>(0.5f, 0.5f, -0.5f), Vec3<float>(0, 0, 1),  Vec2<float>(1, 1)),

    Vertex(Vec3<float>(0.5f, 0.5f, -0.5f), Vec3<float>(0, 0, 1),  Vec2<float>(1, 1)),
    Vertex(Vec3<float>(-0.5f, 0.5f, -0.5f), Vec3<float>(0, 0, 1),  Vec2<float>(0, 1)),
    Vertex(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<float>(0, 0, 1),  Vec2<float>(0, 0)),

    // bottom
    Vertex(Vec3<float>(-0.5f, -0.5f, 0.5f), Vec3<float>(0, 0, -1), Vec2<float>(0, 0)),
    Vertex(Vec3<float>(0.5f, -0.5f, 0.5f), Vec3<float>(0, 0, -1), Vec2<float>(1, 0)),
    Vertex(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<float>(0, 0, -1), Vec2<float>(1, 1)),

    Vertex(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<float>(0, 0, -1), Vec2<float>(1, 1)),
    Vertex(Vec3<float>(-0.5f, 0.5f, 0.5f), Vec3<float>(0, 0, -1), Vec2<float>(0, 1)),
    Vertex(Vec3<float>(-0.5f, -0.5f, 0.5f), Vec3<float>(0, 0, -1), Vec2<float>(0, 0)),

    // front
    Vertex(Vec3<float>(-0.5f, 0.5f, 0.5f), Vec3<float>(0, -1, 0), Vec2<float>(1, 0)),
    Vertex(Vec3<float>(-0.5f, 0.5f, -0.5f), Vec3<float>(0, -1, 0), Vec2<float>(1, 1)),
    Vertex(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<float>(0, -1, 0), Vec2<float>(0, 1)),

    Vertex(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<float>(0, -1, 0), Vec2<float>(0, 1)),
    Vertex(Vec3<float>(-0.5f, -0.5f, 0.5f), Vec3<float>(0, -1, 0), Vec2<float>(0, 0)),
    Vertex(Vec3<float>(-0.5f, 0.5f, 0.5f), Vec3<float>(0, -1, 0), Vec2<float>(1, 0)),

    // back
    Vertex(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<float>(0, 1, 0),  Vec2<float>(1, 0)),
    Vertex(Vec3<float>(0.5f, 0.5f, -0.5f), Vec3<float>(0, 1, 0),  Vec2<float>(1, 1)),
    Vertex(Vec3<float>(0.5f, -0.5f, -0.5f), Vec3<float>(0, 1, 0),  Vec2<float>(0, 1)),

    Vertex(Vec3<float>(0.5f, -0.5f, -0.5f), Vec3<float>(0, 1, 0),  Vec2<float>(0, 1)),
    Vertex(Vec3<float>(0.5f, -0.5f, 0.5f), Vec3<float>(0, 1, 0),  Vec2<float>(0, 0)),
    Vertex(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<float>(0, 1, 0),  Vec2<float>(1, 0)),

    // right
    Vertex(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<float>(-1, 0, 0),  Vec2<float>(0, 1)),
    Vertex(Vec3<float>(0.5f, -0.5f, -0.5f), Vec3<float>(-1, 0, 0),  Vec2<float>(1, 1)),
    Vertex(Vec3<float>(0.5f, -0.5f, 0.5f), Vec3<float>(-1, 0, 0),  Vec2<float>(1, 0)),

    Vertex(Vec3<float>(0.5f, -0.5f, 0.5f), Vec3<float>(-1, 0, 0),  Vec2<float>(1, 0)),
    Vertex(Vec3<float>(-0.5f, -0.5f, 0.5f), Vec3<float>(-1, 0, 0),  Vec2<float>(0, 0)),
    Vertex(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<float>(-1, 0, 0),  Vec2<float>(0, 1)),

    // left
    Vertex(Vec3<float>(-0.5f, 0.5f, -0.5f), Vec3<float>(1, 0, 0),  Vec2<float>(0, 1)),
    Vertex(Vec3<float>(0.5f, 0.5f, -0.5f), Vec3<float>(1, 0, 0),  Vec2<float>(1, 1)),
    Vertex(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<float>(1, 0, 0),  Vec2<float>(1, 0)),

    Vertex(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<float>(1, 0, 0),  Vec2<float>(1, 0)),
    Vertex(Vec3<float>(-0.5f, 0.5f, 0.5f), Vec3<float>(1, 0, 0),  Vec2<float>(0, 0)),
    Vertex(Vec3<float>(-0.5f, 0.5f, -0.5f), Vec3<float>(1, 0, 0),  Vec2<float>(0, 1))
};

#endif // __CUBE_MESH__
