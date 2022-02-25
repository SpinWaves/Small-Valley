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
#include <Kernel/height_map.h>

struct Vertex;

class World : public std::enable_shared_from_this<World>
{
    inline static constexpr const int _world_size = 256;
    
    public:
        template <typename T>
        using map_type = std::array<std::array<std::array<T, _world_size + 1>, _world_size + 1>, _world_size + 1>;
        using height_map_type = std::vector<std::vector<int>>;

        static std::shared_ptr<World> create();
        inline std::shared_ptr<World> get_ptr() { return shared_from_this(); }
        float get_height(int x, int z) noexcept;
        inline float get_max_height() noexcept { return _max_height; }
        float get_block(int x, int y, int z) noexcept;
        void set_block(int x, int y, int z, int type) noexcept;

        void render(bool wireline, const Vec3<double>& cam_pos);

        ~World();

    private:
        World() = default; // placing constructor here so the create function can access it, but not the user
        void load_meshes();
        void load_collisions();
        void gen_mesh(std::vector<Vertex>& mesh_data);
        
        GLuint _vbo = 0;
        GLuint _vao = 0;

        GLsizei _vertex_count = 0;
        float _max_height = 0;

        height_map_type _height_map;
        map_type<int> _map;
        Shader _shader;
        Texture _texture;
        Texture _normal_map;
};

#endif // __WORLD__
