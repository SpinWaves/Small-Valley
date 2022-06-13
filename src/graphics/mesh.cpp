// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "mesh.h"

void Mesh::init(std::vector<Vertex_Normal_Mapped> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
    /*
    _vertices = std::move(vertices);
    _indices = std::move(indices);
    _textures = std::move(textures);
 
    load_mesh();
    */
}

void Mesh::load_mesh()
{
    /*
    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);
    if(glIsBuffer(_ebo) == GL_TRUE)
        glDeleteBuffers(1, &_ebo);
    if(glIsVertexArray(_vao) == GL_TRUE)
        glDeleteVertexArrays(1, &_vao);

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
  
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords));

    glBindVertexArray(0);

    if(glIsBuffer(_vbo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO) for a mesh");
    if(glIsBuffer(_ebo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate an Element Buffer Object (EBO) for a mesh");
    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO) for a mesh");
    */
}

void Mesh::render(Shader &shader)
{
    /*
    int diffuseNr = 1;
    int specularNr = 1;
    for(int i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name;
        if(_textures[i].get_type() == texture_type::diffuse)
        {
            number = std::to_string(diffuseNr++);
            name = "deffuse";
        }
        else if(_textures[i].get_type() == texture_type::specular)
        {
            number = std::to_string(specularNr++);
            name = "specular";
        }

        shader.setFloat(std::string("material." + name + number).c_str(), i);
        _textures[i].bind_texture();
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    */
}

Mesh::~Mesh()
{
    /*
    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);
    if(glIsBuffer(_ebo) == GL_TRUE)
        glDeleteBuffers(1, &_ebo);
    if(glIsVertexArray(_vao) == GL_TRUE)
        glDeleteVertexArrays(1, &_vao);
    */
}
