#include "cube.h"
#include <graphics/matrixes.h>

Cube::Cube(std::shared_ptr<World> world) : _world(std::move(world)) {}

void Cube::create(int x, int y, int z)
{
    //    v6--------v5
    //   /|        /|
    //  v1--------v0|
    //  | |       | |
    //  | v7------|-v4
    //  |/        |/
    //  v2--------v3

    // vertex position array
    float vertices[72] = {
         1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,  1.0f,-1.0f, 1.0f, // top
         1.0f, 1.0f, 1.0f,   1.0f,-1.0f, 1.0f,   1.0f,-1.0f,-1.0f,  1.0f, 1.0f,-1.0f, // back
         1.0f, 1.0f, 1.0f,   1.0f, 1.0f,-1.0f,  -1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f, // left
        -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,-1.0f,  -1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, // front
        -1.0f,-1.0f,-1.0f,   1.0f,-1.0f,-1.0f,   1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, // right
         1.0f,-1.0f,-1.0f,  -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,  1.0f, 1.0f,-1.0f  // bottom
    };

    // texture coord array
    float coords_tex[48] = {
        0, 0,   0, 1,   1, 1,   1, 0, // top
        1, 0,   0, 0,   0, 1,   1, 1, // back
        0, 0,   0, 1,   1, 1,   1, 0, // left
        0, 0,   0, 1,   1, 1,   1, 0, // front
        0, 1,   1, 1,   1, 0,   0, 0, // right
        0, 0,   0, 1,   1, 1,   1, 0  // bottom
    };

    unsigned int indices[36] = {
         0,  1,  2,   2,  3,  0, // top
         4,  5,  6,   6,  7,  4, // back
         8,  9, 10,  10, 11,  8, // left
        12, 13, 14,  14, 15, 12, // front
        16, 17, 18,  18, 19, 16, // right
        20, 21, 22,  22, 23, 20  // bottom
    };

    glGenVertexArrays(1, &_vao);

    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO)");

	glBindVertexArray(_vao);

    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);
    if(glIsBuffer(_ebo) == GL_TRUE)
        glDeleteBuffers(1, &_ebo);

	glGenBuffers(1, &_vbo);
    if(glIsBuffer(_vbo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO)");
    
    glGenBuffers(1, &_ebo);
    if(glIsBuffer(_ebo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate an Element Buffer Object (EBO)");

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(coords_tex), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(coords_tex), coords_tex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    _vPos.SET(x, y, z);
    _world->set_block(x, y, z, 1);

    //_texture_atlas = std::move(texture_atlas);
}

void Cube::render(Shader& shader)
{
    //if(!_texture_atlas.empty())
    //    _texture_atlas[0]->bind_texture();
    Matrixes::matrix_mode(matrix::model);
    Matrixes::load_identity();
    Matrixes::translate3D(_vPos.X, _vPos.Y, _vPos.Z);
    shader.setMat4("model", Matrixes::get_matrix(matrix::model));

    glBindVertexArray(_vao);
  
    std::cout << "test3" << std::endl;
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    std::cout << "test4" << std::endl;
    glBindVertexArray(0);
    std::cout << "test5" << std::endl;

    //if(!_texture_atlas.empty())
    //    _texture_atlas[0]->unbind_texture();
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}
