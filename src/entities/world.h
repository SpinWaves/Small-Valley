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
#include <maths/vec2.h>

class World : public std::enable_shared_from_this<World>
{
    inline static constexpr const int _world_size = 10;
    inline static constexpr const int _map_size = 60;
    
    public:
        template <typename T>
        using map_type = std::array<std::array<std::array<T, _map_size>, _map_size>, _map_size>;
        template <typename T>
        using height_map_type = std::array<std::array<T, _world_size>, _world_size>;

        static std::shared_ptr<World> create();
        inline std::shared_ptr<World> get_ptr() { return shared_from_this(); }
        float get_height(int x, int z) noexcept;
        float get_block(int x, int y, int z) noexcept;
        void set_block(int x, int y, int z, int type) noexcept;

        void render();

        ~World();

    private:
        World() = default; // placing constructor here so the create function can access it, but not the user
        void load_meshes();
        
        GLuint _vbo = 0;
        GLuint _vao = 0;

        GLsizei _vertex_count = 0;

        height_map_type<int> _height_map;
        map_type<int> _map;
        Shader _shader;
        Texture _texture;

        struct Vertex_Data
        {
            Vec3<float> pos;
            Vec3<int> normals;
            Vec2<int> texture_coords;
        };
        
        std::vector<Vertex_Data> _cube_mesh;
};

#endif // __WORLD__
