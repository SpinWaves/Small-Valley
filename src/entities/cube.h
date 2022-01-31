#ifndef __CUBE__
#define __CUBE__

#include <pch.h>
#include <maths/vec3.h>
#include <graphics/textures.h>
#include <graphics/shaders.h>
#include "world.h"

class Cube
{
    public:
        Cube(std::shared_ptr<World> world);

        inline void set_pos(Vec3<int> pos) noexcept { _vPos = std::move(pos); _world->set_block(_vPos.X, _vPos.Y, _vPos.Z, 1); }
        inline void set_pos(int x, int y, int z) noexcept { _vPos.SET(x, y, z); _world->set_block(x, y, z, 1); }

        void create(int x, int y, int z);
        void render(Shader& shader);

        ~Cube();

    private:
        GLuint _vbo = 0;
        GLuint _ebo = 0;
        GLuint _vao = 0;

        Vec3<int> _vPos;
        std::shared_ptr<World> _world;

        std::array<std::shared_ptr<Texture>, 6> _texture_atlas;
};

#endif // __CUBE__
