// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __MODEL__
#define __MODEL__

#include "mesh.h" // will include pch, shaders and textures

class Model
{
    public:
        Model(const char* path);

        void render(Shader& shader);

        ~Model() = default;

    private:
        std::vector<Mesh> _meshes;
        std::string _directory;

        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif // __MODEL__
