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

#endif // __VERTEX__
