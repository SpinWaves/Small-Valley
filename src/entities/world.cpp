// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "world.h"
#include <graphics/matrixes.h>

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

    World::height_map_type<int> temp = {
        std::array<int, 10>{8, 6, 5, 4, 2, 1, 2, 5, 9, 12},
        std::array<int, 10>{8, 5, 4, 2, 1, 0, 1, 4, 8, 13},
        std::array<int, 10>{7, 5, 3, 1, 0, 0, 0, 3, 7, 11},
        std::array<int, 10>{4, 4, 2, 0, 2, 0, 0, 2, 4, 8},
        std::array<int, 10>{3, 2, 1, 0, 1, 0, 1, 3, 5, 7},
        std::array<int, 10>{4, 3, 1, 0, 0, 0, 0, 2, 2, 4},
        std::array<int, 10>{5, 4, 3, 1, 1, 1, 1, 2, 5, 6},
        std::array<int, 10>{8, 7, 6, 4, 3, 2, 2, 3, 5, 8},
        std::array<int, 10>{12, 10, 8, 6, 4, 4, 3, 6, 7, 10},
        std::array<int, 10>{16, 14, 10, 8, 5, 5, 7, 8, 10, 11}
    };

    world->_height_map.swap(temp);

    std::array<int, _map_size> first_dim; first_dim.fill(0);
    std::array<std::array<int, _map_size>, _map_size> second_dim; second_dim.fill(first_dim);
    world->_map.fill(second_dim);

    world->_shader.create(MAIN_DIR"src/graphics/shaders/terrain/terrain.vert", MAIN_DIR"src/graphics/shaders/terrain/terrain.frag");
    world->_texture.load_texture(RES_DIR"assets/grass.jpg");

    world->load_meshes();

    return std::move(world);
}

void World::load_meshes()
{
    _cube_mesh = {
        // top
        World::Vertex_Data(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<int>(0, 0, 1), Vec2<int>(0, 0)),
        World::Vertex_Data(Vec3<float>(-0.5f, 0.5f, 0.5f), Vec3<int>(0, 0, 1), Vec2<int>(0, 1)),
        World::Vertex_Data(Vec3<float>(-0.5f, -0.5f, 0.5f), Vec3<int>(0, 0, 1), Vec2<int>(1, 1)),
        World::Vertex_Data(Vec3<float>(0.5f, -0.5f, 0.5f), Vec3<int>(0, 0, 1), Vec2<int>(1, 0)),
        // back
        World::Vertex_Data(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<int>(1, 0, 0), Vec2<int>(1, 0)),
        World::Vertex_Data(Vec3<float>(0.5f, -0.5f, 0.5f), Vec3<int>(1, 0, 0), Vec2<int>(0, 1)),
        World::Vertex_Data(Vec3<float>(0.5f, -0.5f, -0.5f), Vec3<int>(1, 0, 0), Vec2<int>(0, 1)),
        World::Vertex_Data(Vec3<float>(0.5f, 0.5f, -0.5f), Vec3<int>(1, 0, 0), Vec2<int>(1, 1)),
        // left
        World::Vertex_Data(Vec3<float>(0.5f, 0.5f, 0.5f), Vec3<int>(0, 1, 0), Vec2<int>(0, 0)),
        World::Vertex_Data(Vec3<float>(0.5f, 0.5f, -0.5f), Vec3<int>(0, 1, 0), Vec2<int>(0, 1)),
        World::Vertex_Data(Vec3<float>(-0.5f, 0.5f, -0.5f), Vec3<int>(0, 1, 0), Vec2<int>(1, 1)),
        World::Vertex_Data(Vec3<float>(-0.5f, 0.5f, 0.5f), Vec3<int>(0, 1, 0), Vec2<int>(1, 0)),
        // front
        World::Vertex_Data(Vec3<float>(-0.5f, 0.5f, 0.5f), Vec3<int>(-1, 0, 0), Vec2<int>(0, 0)),
        World::Vertex_Data(Vec3<float>(-0.5f, 0.5f, -0.5f), Vec3<int>(-1, 0, 0), Vec2<int>(0, 1)),
        World::Vertex_Data(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<int>(-1, 0, 0), Vec2<int>(1, 1)),
        World::Vertex_Data(Vec3<float>(-0.5f, -0.5f, 0.5f), Vec3<int>(-1, 0, 0), Vec2<int>(1, 0)),
        // right
        World::Vertex_Data(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<int>(0, -1, 0), Vec2<int>(0, 1)),
        World::Vertex_Data(Vec3<float>(0.5f, -0.5f, -0.5f), Vec3<int>(0, -1, 0), Vec2<int>(1, 1)),
        World::Vertex_Data(Vec3<float>(0.5f, -0.5f, 0.5f), Vec3<int>(0, -1, 0), Vec2<int>(1, 0)),
        World::Vertex_Data(Vec3<float>(-0.5f, -0.5f, 0.5f), Vec3<int>(0, -1, 0), Vec2<int>(0, 0)),
        // bottom
        World::Vertex_Data(Vec3<float>(0.5f, -0.5f, -0.5f), Vec3<int>(0, 0, -1), Vec2<int>(0, 0)),
        World::Vertex_Data(Vec3<float>(-0.5f, -0.5f, -0.5f), Vec3<int>(0, 0, -1), Vec2<int>(0, 1)),
        World::Vertex_Data(Vec3<float>(-0.5f, 0.5f, -0.5f), Vec3<int>(0, 0, -1), Vec2<int>(1, 1)),
        World::Vertex_Data(Vec3<float>(0.5f, 0.5f, -0.5f), Vec3<int>(0, 0, -1), Vec2<int>(1, 0)),
    };

    glm::mat4 translations[_world_size * _world_size * _world_size];
    for(int z = 1; z <= _world_size; z++)
    {
        for(int x = 1; x <= _world_size; x++)
        {
            for(int y = 0; y < _world_size; y++)
            {
                glm::mat4 translation(1.0f);
                translation = glm::translate(translation, glm::vec3((float)x, (float)z, -(y - get_height(x - 1, z - 1))));
                translations[_instance_nb++] = std::move(translation);
                set_block(x, z, -(y - get_height(x - 1, z - 1)), 1);
            }
        }
    }
    glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);

	glGenBuffers(1, &_vbo);
    
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals) + sizeof(texture_coords), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), sizeof(texture_coords), texture_coords);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertices));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices) + sizeof(normals)));

	glEnableVertexAttribArray(0); // vertices
	glEnableVertexAttribArray(2); // normals
    glEnableVertexAttribArray(3); // texture coords

    if(glIsBuffer(_vbo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO) for the terrain mesh");
    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO) for the terrain mesh");
    
    glBindVertexArray(0);
}

void World::render()
{
    _shader.bindShader();

    _shader.setMat4("view", Matrixes::get_matrix(matrix::view));
    _shader.setMat4("proj", Matrixes::get_matrix(matrix::proj));
    _shader.setMat4("model", Matrixes::get_matrix(matrix::model));

    _texture.bind_texture();
  
    glBindVertexArray(_vao);
    
    glDrawArrays(GL_TRIANGLES, 0, _vertex_count);

    glBindVertexArray(0);

    _texture.unbind_texture();

    _shader.unbindShader();
}

World::~World()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}
