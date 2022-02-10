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

    world->load_meshes();

    return std::move(world);
}

void World::load_meshes()
{
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() + normals.size(), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size(), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size(), normals.size(), &normals[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices)));
    glVertexAttribPointer(2, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_FALSE, 0, (void*)vertices.size());
	
	glEnableVertexAttribArray(0); // vertices
	//glEnableVertexAttribArray(1); // color
	glEnableVertexAttribArray(2); // normals

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

    glBindVertexArray(_vao);
  
    glDrawElements(GL_TRIANGLES, _indices_nb, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);

    _shader.unbindShader();
}

World::~World()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}
