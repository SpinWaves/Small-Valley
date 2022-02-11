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
    x = x >= _map.size() ? _map.size() - 1 : x;
    z = z >= _map.size() ? _map.size() - 1 : z;
    return _map[z][x];
}

std::shared_ptr<World> World::create()
{
    std::shared_ptr<World> world(new World());

    World::map_type<int> temp = {
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

    world->_map.swap(temp);
    world->_shader.create(MAIN_DIR"src/graphics/shaders/terrain/terrain.vert", MAIN_DIR"src/graphics/shaders/terrain/terrain.frag");
    world->_texture.load_texture(RES_DIR"assets/grass.jpg");

    world->load_meshes();

    return std::move(world);
}

void World::load_meshes()
{
    float normals_top[12] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1 };
    float normals_back[12] = { 1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0 };
    float normals_left[12] = { 0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0 };
    float normals_front[12] = { -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0 };
    float normals_right[12] = { 0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0 };
    float normals_bottom[12] = { 0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 };

    float coords_tex_top[8] = { 0, 0,   0, 1,   1, 1,   1, 0 };
    float coords_tex_back[8] = { 1, 0,   0, 0,   0, 1,   1, 1 };
    float coords_tex_left[8] = { 0, 0,   0, 1,   1, 1,   1, 0 };
    float coords_tex_front[8] = { 0, 0,   0, 1,   1, 1,   1, 0 };
    float coords_tex_right[8] = { 0, 1,   1, 1,   1, 0,   0, 0 };
    float coords_tex_bottom[8] = { 0, 0,   0, 1,   1, 1,   1, 0 };

    unsigned char indices_top[6] = { 0,  1,  2,   2,  3,  0 };
    unsigned char indices_back[6] = { 4,  5,  6,   6,  7,  4 };
    unsigned char indices_left[6] = { 8,  9, 10,  10, 11,  8 };
    unsigned char indices_front[6] = { 12, 13, 14,  14, 15, 12 };
    unsigned char indices_right[6] = { 16, 17, 18,  18, 19, 16 };
    unsigned char indices_bottom[6] = { 20, 21, 22,  22, 23, 20 };

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texture_coords;
    std::vector<unsigned int> indices;

    for(int x = 0; x < _world_size; x++)
    {
        for(int z = 0; z < _world_size; z++)
        {
            // Adding all cubes info for tests
            vertices.insert(vertices.end(), { x + 1.0f, z + 1.0f, get_height(x, z) + 1.0f,  x - 1.0f, z + 1.0f, get_height(x, z) + 1.0f,  x - 1.0f, z - 1.0f, get_height(x, z) + 1.0f, x + 1.0f, z - 1.0f, get_height(x, z) + 1.0f });
            vertices.insert(vertices.end(), { x + 1.0f, z + 1.0f, get_height(x, z) + 1.0f,  x + 1.0f, z - 1.0f, get_height(x, z) + 1.0f,  x + 1.0f, z - 1.0f, get_height(x, z) - 1.0f, x + 1.0f, z + 1.0f, get_height(x, z) - 1.0f });
            vertices.insert(vertices.end(), { x + 1.0f, z + 1.0f, get_height(x, z) + 1.0f,  x + 1.0f, z + 1.0f, get_height(x, z) - 1.0f,  x - 1.0f, z + 1.0f, get_height(x, z) - 1.0f, x - 1.0f, z + 1.0f, get_height(x, z) + 1.0f });
            vertices.insert(vertices.end(), { x - 1.0f, z + 1.0f, get_height(x, z) + 1.0f,  x - 1.0f, z + 1.0f, get_height(x, z) - 1.0f,  x - 1.0f, z - 1.0f, get_height(x, z) - 1.0f, x - 1.0f, z - 1.0f, get_height(x, z) + 1.0f });
            vertices.insert(vertices.end(), { x - 1.0f, z - 1.0f, get_height(x, z) - 1.0f,  x + 1.0f, z - 1.0f, get_height(x, z) - 1.0f,  x + 1.0f,-z + 1.0f, get_height(x, z) + 1.0f, x - 1.0f, z + 1.0f, get_height(x, z) + 1.0f });
            vertices.insert(vertices.end(), { x + 1.0f, z - 1.0f, get_height(x, z) - 1.0f,  x - 1.0f, z - 1.0f, get_height(x, z) - 1.0f,  x - 1.0f, z + 1.0f, get_height(x, z) - 1.0f, x + 1.0f, z + 1.0f, get_height(x, z) - 1.0f });

            normals.insert(normals.end(), normals_top, normals_top + 12);
            normals.insert(normals.end(), normals_back, normals_back + 12);
            normals.insert(normals.end(), normals_left, normals_left + 12);
            normals.insert(normals.end(), normals_front, normals_front + 12);
            normals.insert(normals.end(), normals_right, normals_right + 12);
            normals.insert(normals.end(), normals_bottom, normals_bottom + 12);

            texture_coords.insert(texture_coords.end(), coords_tex_top, coords_tex_top + 8);
            texture_coords.insert(texture_coords.end(), coords_tex_back, coords_tex_back + 8);
            texture_coords.insert(texture_coords.end(), coords_tex_left, coords_tex_left + 8);
            texture_coords.insert(texture_coords.end(), coords_tex_front, coords_tex_front + 8);
            texture_coords.insert(texture_coords.end(), coords_tex_right, coords_tex_right + 8);
            texture_coords.insert(texture_coords.end(), coords_tex_bottom, coords_tex_bottom + 8);

            indices.insert(indices.end(), indices_top, indices_top + 6);
            indices.insert(indices.end(), indices_back, indices_back + 6);
            indices.insert(indices.end(), indices_left, indices_left + 6);
            indices.insert(indices.end(), indices_front, indices_front + 6);
            indices.insert(indices.end(), indices_right, indices_right + 6);
            indices.insert(indices.end(), indices_bottom, indices_bottom + 6);
        }
    }
    _indices_nb = indices.size();

    glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);
    if(glIsBuffer(_ebo) == GL_TRUE)
        glDeleteBuffers(1, &_ebo);

	glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() + normals.size() + texture_coords.size(), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size(), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size(), normals.size(), &normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() + normals.size(), texture_coords.size(), &texture_coords[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)vertices.size());
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)(vertices.size() + normals.size()));
	
	glEnableVertexAttribArray(0); // vertices
	//glEnableVertexAttribArray(1); // color
	glEnableVertexAttribArray(2); // normals
    glEnableVertexAttribArray(3);

    if(glIsBuffer(_vbo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO) for the terrain mesh");
    if(glIsBuffer(_ebo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Element Buffer Object (EBO) for the terrain mesh");
    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO) for the terrain mesh");
    
    glBindVertexArray(0);
}

void World::render()
{
    _shader.bindShader();

    _shader.setMat4("model", Matrixes::get_matrix(matrix::model));
    _shader.setMat4("view", Matrixes::get_matrix(matrix::view));
    _shader.setMat4("proj", Matrixes::get_matrix(matrix::proj));

    _texture.bind_texture();

    glBindVertexArray(_vao);
  
    glDrawElements(GL_TRIANGLES, _indices_nb, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);

    _texture.unbind_texture();

    _shader.unbindShader();
}

World::~World()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}
