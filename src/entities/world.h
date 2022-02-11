// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __WORLD__
#define __WORLD__

#include <pch.h>
#include <graphics/shaders.h>
#include <graphics/textures.h>
#include <maths/vec3.h>

class World : public std::enable_shared_from_this<World>
{
    inline static constexpr const int _world_size = 10;
    
    public:
        template <typename T>
        using map_type = std::array<std::array<T, _world_size>, _world_size>;

        static std::shared_ptr<World> create();
        inline std::shared_ptr<World> get_ptr() { return shared_from_this(); }
        float get_height(int x, int z) noexcept;

        void render();

        ~World();

    private:
        World() = default; // placing constructor here so the create function can access it, but not the user
        void load_meshes();
        
        GLuint _vbo = 0;
        GLuint _ebo = 0;
        GLuint _vao = 0;

        int _indices_nb = 0;

        map_type<int> _map;
        Shader _shader;
        Texture _texture;

};

#endif // __WORLD__
