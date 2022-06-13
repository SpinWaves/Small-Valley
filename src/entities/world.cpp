// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "world.h"
#include <graphics/texture_atlas.h>
#include <graphics/matrixes.h>
#include <graphics/cube_mesh.h>

float World::get_height(int x, int z) noexcept
{
    x = x < 0 ? 0 : x;
    z = z < 0 ? 0 : z;
    x = x >= _height_map.size() ? _height_map.size() - 1 : x;
    z = z >= _height_map.size() ? _height_map.size() - 1 : z;
    return _height_map[x][z];
}

float World::get_block(int x, int y, int z) noexcept
{
    if(x >= 0 && x <= _map.size() && y >= 0 && y <= _map.size() && z >= 0 && z <= _map.size())
        return _map[x][y][z];
    return 0.0f;
}
void World::set_block(int x, int y, int z, int type) noexcept
{
    x = x < 0 ? 0 : x;
    y = y < 0 ? 0 : y;
    z = z < 0 ? 0 : z;
    x = x >= _map.size() ? _map.size() - 1 : x;
    y = y >= _map.size() ? _map.size() - 1 : y;
    z = z >= _map.size() ? _map.size() - 1 : z;
    _map[x][y][z] = type;
}

std::shared_ptr<World> World::create()
{
    std::shared_ptr<World> world(new World());

    log::report(log_type::message, "Creating world...");

    world->_height_map = std::move(load_height_map(RES_DIR"assets/height_map_terrain.png", 0.5));
    for(int i = 0; i < _world_size; i++)
    {
        for(int j = 0; j < _world_size; j++)
        {
            if(world->_max_height < world->get_height(i, j))
                world->_max_height = world->get_height(i, j);
        }
    }

    std::array<int, _world_size + 1> first_dim; first_dim.fill(0);
    std::array<std::array<int, _world_size + 1>, _world_size + 1> second_dim; second_dim.fill(first_dim);
    world->_map.fill(second_dim);

    world->_shader.create(MAIN_DIR"src/graphics/shaders/terrain/terrain.vert", MAIN_DIR"src/graphics/shaders/terrain/terrain.frag");
    //world->_normal_map.load_texture(RES_DIR"assets/grass_normal_map.jpg", texture_type::normal);

    world->load_meshes();

    log::report(log_type::message, "World created");

    return std::move(world);
}

void World::load_collisions()
{
    log::report(log_type::message, "Generating world collision data...");
    for(int z = 1; z <= _world_size; z++)
    {
        for(int x = 1; x <= _world_size; x++)
        {
            for(int y = 0; y < _world_size; y++)
                set_block(x, z, -(y - get_height(x - 1, z - 1)), 1);
        }
    }
    log::report(log_type::message, "World collision data generated");  
}

void World::gen_mesh(std::vector<Vertex>& mesh_data)
{
    log::report(log_type::message, "Generating world mesh...");
    for(int z = 1; z <= _world_size; z++)
    {
        if(z == 1 || z == _world_size) // remove edges
            continue;
        
        for(int x = 1; x <= _world_size; x++)
        {
            if(x == 1 || x == _world_size) // remove edges
                continue;
            
            for(int y = 0; y < _world_size; y++)
            {
                if(-(y - get_height(x - 1, z - 1)) <= 0 || -(y - get_height(x - 1, z - 1)) == _max_height) // remove edges
                    continue;

                // top
                if(!get_block(x, z, -(y - get_height(x - 1, z - 1)) - 1))
                {
                    mesh_data.push_back(Vertex(cube_mesh[0].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[0].normals, cube_mesh[0].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[1].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[1].normals, cube_mesh[1].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[2].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[2].normals, cube_mesh[2].texture_coords));

                    mesh_data.push_back(Vertex(cube_mesh[3].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[3].normals, cube_mesh[3].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[4].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[4].normals, cube_mesh[4].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[5].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[5].normals, cube_mesh[5].texture_coords));
                }

                // bottom
                if(!get_block(x, z, -(y - get_height(x - 1, z - 1)) + 1))
                {
                    mesh_data.push_back(Vertex(cube_mesh[6].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[6].normals, cube_mesh[6].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[7].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[7].normals, cube_mesh[7].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[8].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[8].normals, cube_mesh[8].texture_coords));

                    mesh_data.push_back(Vertex(cube_mesh[9].position  + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[9].normals, cube_mesh[9].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[10].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[10].normals, cube_mesh[10].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[11].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[11].normals, cube_mesh[11].texture_coords));
                }

                // front
                if(!get_block(x - 1, z, -(y - get_height(x - 1, z - 1))))
                {
                    mesh_data.push_back(Vertex(cube_mesh[12].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[12].normals, cube_mesh[12].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[13].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[13].normals, cube_mesh[13].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[14].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[14].normals, cube_mesh[14].texture_coords));

                    mesh_data.push_back(Vertex(cube_mesh[15].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[15].normals, cube_mesh[15].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[16].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[16].normals, cube_mesh[16].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[17].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[17].normals, cube_mesh[17].texture_coords));
                }

                // back
                if(!get_block(x + 1, z, -(y - get_height(x - 1, z - 1))))
                {
                    mesh_data.push_back(Vertex(cube_mesh[18].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[18].normals, cube_mesh[18].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[19].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[19].normals, cube_mesh[19].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[20].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[20].normals, cube_mesh[20].texture_coords));

                    mesh_data.push_back(Vertex(cube_mesh[21].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[21].normals, cube_mesh[21].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[22].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[22].normals, cube_mesh[22].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[23].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[23].normals, cube_mesh[23].texture_coords));
                }

                // right
                if(!get_block(x, z - 1, -(y - get_height(x - 1, z - 1))))
                {
                    mesh_data.push_back(Vertex(cube_mesh[24].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[24].normals, cube_mesh[24].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[25].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[25].normals, cube_mesh[25].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[26].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[26].normals, cube_mesh[26].texture_coords));

                    mesh_data.push_back(Vertex(cube_mesh[27].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[27].normals, cube_mesh[27].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[28].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[28].normals, cube_mesh[28].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[29].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[29].normals, cube_mesh[29].texture_coords));
                }

                // left
                if(!get_block(x, z + 1, -(y - get_height(x - 1, z - 1))))
                {
                    mesh_data.push_back(Vertex(cube_mesh[30].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[30].normals, cube_mesh[30].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[31].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[31].normals, cube_mesh[31].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[32].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[32].normals, cube_mesh[32].texture_coords));

                    mesh_data.push_back(Vertex(cube_mesh[33].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[33].normals, cube_mesh[33].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[34].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[34].normals, cube_mesh[34].texture_coords));
                    mesh_data.push_back(Vertex(cube_mesh[35].position + Vec3<float>(x, z, -(y - get_height(x - 1, z - 1))), cube_mesh[35].normals, cube_mesh[35].texture_coords));
                }
            }
        }
    }
    _vertex_count = mesh_data.size();
    log::report(log_type::message, "World mesh generated");
}

void World::load_meshes()
{
    std::vector<Vertex> mesh_data;

    load_collisions();
    gen_mesh(mesh_data);

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
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO) for the terrain mesh");
    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO) for the terrain mesh");
    
    glBindVertexArray(0);
}

void World::render(const Vec3<double>& cam_pos)
{
    _shader.bindShader();

    _shader.setMat4("view", Matrixes::get_matrix(matrix::view));
    _shader.setMat4("proj", Matrixes::get_matrix(matrix::proj));
    _shader.setMat4("model", Matrixes::get_matrix(matrix::model));
    _shader.setVec3("viewPos", cam_pos.X, cam_pos.Y, cam_pos.Z);

    //glActiveTexture(GL_TEXTURE0);
    TextureAtlas::bind(GRASS_TEXTURE);
    //glActiveTexture(GL_TEXTURE1);
    //_normal_map.bind_texture();
  
    glBindVertexArray(_vao);
    
    glDrawArrays(GL_TRIANGLES, 0, _vertex_count);

    glBindVertexArray(0);

    Texture::unbind_texture();
    //_normal_map.unbind_texture();

    _shader.unbindShader();
}

World::~World()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}
