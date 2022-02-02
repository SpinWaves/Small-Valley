#ifndef __CUBE__
#define __CUBE__

#include <pch.h>
#include <maths/vec3.h>
#include <graphics/textures.h>
#include <graphics/shaders.h>

class Cube
{
    public:
        Cube() = default;

        void set_pos(Vec3<int> pos) noexcept;
        void set_pos(int x, int y, int z) noexcept;
        
        void create(int x, int y, int z);
        void render(Shader& shader);

        ~Cube();

    private:
        GLuint _vbo = 0;
        GLuint _ebo = 0;
        GLuint _vao = 0;

        Vec3<int> _vPos;

        std::array<std::shared_ptr<Texture>, 6> _texture_atlas;
};

#endif // __CUBE__
