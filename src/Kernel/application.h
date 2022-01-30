#ifndef __APPLICATION__
#define __APPLICATION__

#include <pch.h>
#include <io/inputs.h>
#include <graphics/shaders.h>
#include <graphics/camera.h>
#include <entities/cube.h>

class Application
{
    public:
        Application();

        void init(const char* name);
        void update(const Input& in);
        void destroy();

        ~Application();

    private:
        SDL_Window* _win = nullptr;
        SDL_GLContext _context;

        Shader _shader;
        Camera3D _camera;
        Cube _cube;
        Texture* _tex = nullptr;
};

#endif // __APPLICATION__
