// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __MESH__
#define __MESH__

#include <pch.h>
#include "vertex.h"
#include "textures.h"
#include "shaders.h"

class Mesh
{
    public:
        Mesh() = default;
        void init(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
        void render(Shader &shader);
        ~Mesh();

    private:
        void load_mesh();

        GLuint _vao;
        GLuint _vbo;
        GLuint _ebo;

        std::vector<Vertex>  _vertices;
        std::vector<GLuint>  _indices;
        std::vector<Texture> _textures;

};

#endif // __MESH__