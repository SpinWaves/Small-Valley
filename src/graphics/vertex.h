// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __VERTEX__
#define __VERTEX__

#include <maths/vec2.h>
#include <maths/vec3.h>

struct Vertex
{
    Vertex(Vec3<float> p, Vec3<float> n, Vec2<float> t) : position(std::move(p)), normals(std::move(n)), texture_coords(std::move(t)) {}

    Vec3<float> position;
    Vec3<float> normals;
    Vec2<float> texture_coords;
};

struct Vertex_Normal_Mapped : public Vertex
{
    Vertex_Normal_Mapped(Vec3<float> p, Vec3<float> n, Vec2<float> t, Vec3<float> tan_1, Vec3<float> btan_1, Vec3<float> tan_2, Vec3<float> btan_2) : 
        Vertex(std::move(p), std::move(n), std::move(t)), 
        tangent_1(std::move(tan_1)), bitangent_1(std::move(btan_1)),
        tangent_2(std::move(tan_2)), bitangent_2(std::move(btan_2)) {}
    
    Vec3<float> tangent_1;
    Vec3<float> bitangent_1;
    Vec3<float> tangent_2;
    Vec3<float> bitangent_2;
};

#endif // __VERTEX__
