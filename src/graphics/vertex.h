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
    Vertex();
    Vertex(Vec3<float> p, Vec3<float> n, Vec2<float> t) : position(std::move(p)), normals(std::move(n)), texture_coords(std::move(t)) {}

    Vec3<float> position;
    Vec3<float> normals;
    Vec2<float> texture_coords;
};

#define MAX_BONE_INFLUENCE 4

struct Vertex_Normal_Mapped : public Vertex
{
    Vertex_Normal_Mapped();
    Vertex_Normal_Mapped(Vec3<float> p, Vec3<float> n, Vec2<float> t, Vec3<float> tan, Vec3<float> btan) : 
        Vertex(std::move(p), std::move(n), std::move(t)), tangent(std::move(tan)), bitangent(std::move(btan)) {}
    
    Vec3<float> tangent;
    Vec3<float> bitangent;
	std::array<int, MAX_BONE_INFLUENCE> boneIDs;
	std::array<float, MAX_BONE_INFLUENCE> weights;
};

#endif // __VERTEX__
