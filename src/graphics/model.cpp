// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "model.h"

Model::Model(const std::string& path)
{
    /*
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        log::report(log_type::error, "Assimp : cannot load a file \"%s\" : %s", path, import.GetErrorString());
        return;
    }
    _directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
    */
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    /*
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *_mesh = scene->mMeshes[node->mMeshes[i]]; 
        _meshes.push_back(processMesh(_mesh, scene));			
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
    */
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    /*
    std::vector<Vertex_Normal_Mapped> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex_Normal_Mapped vertex;
        Vec3<float> vector;

        vector.X = mesh->mVertices[i].x;
        vector.Y = mesh->mVertices[i].y;
        vector.Z = mesh->mVertices[i].z;
        vertex.position = vector;

        if(mesh->HasNormals())
        {
            vector.X = mesh->mNormals[i].x;
            vector.Y = mesh->mNormals[i].y;
            vector.Z = mesh->mNormals[i].z;
            vertex.normals = vector;
        }

        if(mesh->mTextureCoords[0]) 
        {
            Vec2<float> vec;
            vec.X = mesh->mTextureCoords[0][i].x; 
            vec.Y = mesh->mTextureCoords[0][i].y;
            vertex.texture_coords = vec;

            vector.X = mesh->mTangents[i].x;
            vector.Y = mesh->mTangents[i].y;
            vector.Z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.X = mesh->mBitangents[i].x;
            vector.Y = mesh->mBitangents[i].y;
            vector.Z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.texture_coords = Vec2<float>(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    Mesh final_mesh;
    final_mesh.init(vertices, indices, textures);
    return std::move(final_mesh);
    */
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    /*
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return std::move(textures);
    */
}
