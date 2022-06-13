// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "cube.h"
#include "world.h"
#include <graphics/matrixes.h>
#include <graphics/cube_mesh.h>
#include <graphics/texture_atlas.h>

Cube::Cube(Cube::type t, Vec3<float> pos, Vec3<float> size) : _type(t), _vPos(std::move(pos)), _vSize(std::move(size)) {}
Cube::Cube(Cube::type t, float x, float y, float z, float w, float h, float d) : _type(t), _vPos(x, y, z), _vSize(w, h, d) {}

void Cube::set_pos(World& world, Vec3<float> pos) noexcept 
{
    for(int x = -std::ceil(_vSize.X / 2) + 1; x < std::ceil(_vSize.X / 2); x++)
        for(int y = -std::ceil(_vSize.Y / 2) + 1; y < std::ceil(_vSize.Y / 2); y++)
            for(int z = -std::round(_vSize.Z / 2); z < std::round(_vSize.Z / 2); z++)
                world.set_block(_vPos.X + x, _vPos.Y + y, _vPos.Z + z, 0);

    _vPos = std::move(pos);

    for(int x = -std::ceil(_vSize.X / 2) + 1; x < std::ceil(_vSize.X / 2); x++)
        for(int y = -std::ceil(_vSize.Y / 2) + 1; y < std::ceil(_vSize.Y / 2); y++)
            for(int z = -std::round(_vSize.Z / 2); z < std::round(_vSize.Z / 2); z++)
                world.set_block(_vPos.X + x, _vPos.Y + y, _vPos.Z + z, 1);
}

void Cube::set_pos(World& world, float x, float y, float z) noexcept
{
    for(int x = -std::ceil(_vSize.X / 2) + 1; x < std::ceil(_vSize.X / 2); x++)
        for(int y = -std::ceil(_vSize.Y / 2) + 1; y < std::ceil(_vSize.Y / 2); y++)
            for(int z = -std::round(_vSize.Z / 2); z < std::round(_vSize.Z / 2); z++)
                world.set_block(_vPos.X + x, _vPos.Y + y, _vPos.Z + z, 0);

    _vPos.SET(x, y, z);

    for(int x = -std::ceil(_vSize.X / 2) + 1; x < std::ceil(_vSize.X / 2); x++)
        for(int y = -std::ceil(_vSize.Y / 2) + 1; y < std::ceil(_vSize.Y / 2); y++)
            for(int z = -std::round(_vSize.Z / 2); z < std::round(_vSize.Z / 2); z++)
                world.set_block(_vPos.X + x, _vPos.Y + y, _vPos.Z + z, 1);
}

void Cube::set_size(World& world, Vec3<float> size) noexcept
{
    _vSize = std::move(size);
    for(int x = -std::ceil(_vSize.X / 2) + 1; x < std::ceil(_vSize.X / 2); x++)
        for(int y = -std::ceil(_vSize.Y / 2) + 1; y < std::ceil(_vSize.Y / 2); y++)
            for(int z = -std::round(_vSize.Z / 2); z < std::round(_vSize.Z / 2); z++)
                world.set_block(_vPos.X + x, _vPos.Y + y, _vPos.Z + z, 1);
}

void Cube::set_size(World& world, float x, float y, float z) noexcept
{
    _vSize.SET(x, y, z);
    for(int x = -std::ceil(_vSize.X / 2) + 1; x < std::ceil(_vSize.X / 2); x++)
        for(int y = -std::ceil(_vSize.Y / 2) + 1; y < std::ceil(_vSize.Y / 2); y++)
            for(int z = -std::round(_vSize.Z / 2); z < std::round(_vSize.Z / 2); z++)
                world.set_block(_vPos.X + x, _vPos.Y + y, _vPos.Z + z, 1);
}

void Cube::create(World& world)
{
    std::vector<Vertex> mesh_data;

    // top
    if(!world.get_block(_vPos.X, _vPos.Z, -(_vPos.Y - world.get_height(_vPos.X - 1, _vPos.Z - 1)) - 1) || _vSize.X != 1.0f || _vSize.Y != 1.0f || _vSize.Z != 1.0f)
    {
        mesh_data.push_back(Vertex((cube_mesh[1].position  * _vSize) + _vPos, cube_mesh[1].normals, cube_mesh[1].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[2].position  * _vSize) + _vPos, cube_mesh[2].normals, cube_mesh[2].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[0].position  * _vSize) + _vPos, cube_mesh[0].normals, cube_mesh[0].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));

        mesh_data.push_back(Vertex((cube_mesh[3].position  * _vSize) + _vPos, cube_mesh[3].normals, cube_mesh[3].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[4].position  * _vSize) + _vPos, cube_mesh[4].normals, cube_mesh[4].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[5].position  * _vSize) + _vPos, cube_mesh[5].normals, cube_mesh[5].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
    }

    // bottom
    if(!world.get_block(_vPos.X, _vPos.Z, -(_vPos.Y - world.get_height(_vPos.X - 1, _vPos.Z - 1)) + 1) || _vSize.X != 1.0f ||_vSize.Y != 1.0f|| _vSize.Z != 1.0f)
    {
        mesh_data.push_back(Vertex((cube_mesh[6].position  * _vSize) + _vPos, cube_mesh[6].normals, cube_mesh[6].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[7].position  * _vSize) + _vPos, cube_mesh[7].normals, cube_mesh[7].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[8].position  * _vSize) + _vPos, cube_mesh[8].normals, cube_mesh[8].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));

        mesh_data.push_back(Vertex((cube_mesh[9].position  * _vSize) + _vPos, cube_mesh[9].normals,  cube_mesh[9].texture_coords  * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[10].position * _vSize) + _vPos, cube_mesh[10].normals, cube_mesh[10].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
        mesh_data.push_back(Vertex((cube_mesh[11].position * _vSize) + _vPos, cube_mesh[11].normals, cube_mesh[11].texture_coords * Vec2<float>(_vSize.X, _vSize.Y)));
    }

    // front
    if(!world.get_block(_vPos.X - 1, _vPos.Z, -(_vPos.Y - world.get_height(_vPos.X - 1, _vPos.Z - 1))) || _vSize.X != 1.0f|| _vSize.Y != 1.0f ||_vSize.Z != 1.0f)
    {
        mesh_data.push_back(Vertex((cube_mesh[12].position * _vSize) + _vPos, cube_mesh[12].normals, cube_mesh[12].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[13].position * _vSize) + _vPos, cube_mesh[13].normals, cube_mesh[13].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[14].position * _vSize) + _vPos, cube_mesh[14].normals, cube_mesh[14].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));

        mesh_data.push_back(Vertex((cube_mesh[15].position * _vSize) + _vPos, cube_mesh[15].normals, cube_mesh[15].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[16].position * _vSize) + _vPos, cube_mesh[16].normals, cube_mesh[16].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[17].position * _vSize) + _vPos, cube_mesh[17].normals, cube_mesh[17].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
    }

    // back
    if(!world.get_block(_vPos.X + 1, _vPos.Z, -(_vPos.Y - world.get_height(_vPos.X - 1, _vPos.Z - 1))) || _vSize.X != 1.0f || _vSize.Y != 1.0f || _vSize.Z != 1.0f)
    {
        mesh_data.push_back(Vertex((cube_mesh[18].position * _vSize) + _vPos, cube_mesh[18].normals, cube_mesh[18].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[19].position * _vSize) + _vPos, cube_mesh[19].normals, cube_mesh[19].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[20].position * _vSize) + _vPos, cube_mesh[20].normals, cube_mesh[20].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));

        mesh_data.push_back(Vertex((cube_mesh[21].position * _vSize) + _vPos, cube_mesh[21].normals, cube_mesh[21].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[22].position * _vSize) + _vPos, cube_mesh[22].normals, cube_mesh[22].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[23].position * _vSize) + _vPos, cube_mesh[23].normals, cube_mesh[23].texture_coords * Vec2<float>(_vSize.Y, _vSize.Z)));
    }

    // right
    if(!world.get_block(_vPos.X, _vPos.Z - 1, -(_vPos.Y - world.get_height(_vPos.X - 1, _vPos.Z - 1))) || _vSize.X != 1.0f || _vSize.Y != 1.0f || _vSize.Z != 1.0f)
    {
        mesh_data.push_back(Vertex((cube_mesh[24].position * _vSize) + _vPos, cube_mesh[24].normals, cube_mesh[24].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[25].position * _vSize) + _vPos, cube_mesh[25].normals, cube_mesh[25].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[26].position * _vSize) + _vPos, cube_mesh[26].normals, cube_mesh[26].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));

        mesh_data.push_back(Vertex((cube_mesh[27].position * _vSize) + _vPos, cube_mesh[27].normals, cube_mesh[27].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[28].position * _vSize) + _vPos, cube_mesh[28].normals, cube_mesh[28].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[29].position * _vSize) + _vPos, cube_mesh[29].normals, cube_mesh[29].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
    }

    // left
    if(!world.get_block(_vPos.X, _vPos.Z + 1, -(_vPos.Y - world.get_height(_vPos.X - 1, _vPos.Z - 1))) || _vSize.X != 1.0f || _vSize.Y != 1.0f || _vSize.Z != 1.0f)
    {
        mesh_data.push_back(Vertex((cube_mesh[30].position * _vSize) + _vPos, cube_mesh[30].normals, cube_mesh[30].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[31].position * _vSize) + _vPos, cube_mesh[31].normals, cube_mesh[31].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[32].position * _vSize) + _vPos, cube_mesh[32].normals, cube_mesh[32].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));

        mesh_data.push_back(Vertex((cube_mesh[33].position * _vSize) + _vPos, cube_mesh[33].normals, cube_mesh[33].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[34].position * _vSize) + _vPos, cube_mesh[34].normals, cube_mesh[34].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
        mesh_data.push_back(Vertex((cube_mesh[35].position * _vSize) + _vPos, cube_mesh[35].normals, cube_mesh[35].texture_coords * Vec2<float>(_vSize.X, _vSize.Z)));
    }

    _vertex_count = mesh_data.size();

    for(int x = -std::ceil(_vSize.X / 2) + 1; x < std::ceil(_vSize.X / 2); x++)
        for(int y = -std::ceil(_vSize.Y / 2) + 1; y < std::ceil(_vSize.Y / 2); y++)
            for(int z = -std::round(_vSize.Z / 2); z < std::round(_vSize.Z / 2); z++)
                world.set_block(_vPos.X + x, _vPos.Y + y, _vPos.Z + z, 1);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);

    glGenBuffers(1, &_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertex_count, &mesh_data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords));

    glEnableVertexAttribArray(0); // vertices
    glEnableVertexAttribArray(2); // normals
    glEnableVertexAttribArray(3); // texture coords

    if(glIsBuffer(_vbo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO) for a cube mesh");
    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO) for a cube mesh");
    
    glBindVertexArray(0);
}

void Cube::render()
{
    switch(_type)
    {
        case Cube::type::grass : TextureAtlas::bind(GRASS_TEXTURE); break;
        case Cube::type::wood  : TextureAtlas::bind(WOOD_TEXTURE); break;
        case Cube::type::plank : TextureAtlas::bind(WOOD_PLANK_TEXTURE); break;
    }

    glBindVertexArray(_vao);
    
    glDrawArrays(GL_TRIANGLES, 0, _vertex_count);

    glBindVertexArray(0);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}
