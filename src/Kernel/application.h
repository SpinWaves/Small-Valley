#ifndef __APPLICATION__
#define __APPLICATION__

#include <pch.h>
#include <io/inputs.h>
#include <graphics/shaders.h>
#include <graphics/camera.h>

class Application
{
    public:
        Application() = default;

        void init(const char* name);
        void update(const Input& in);
        void destroy();

        ~Application();

    private:
        SDL_Window* _win = nullptr;
        SDL_GLContext _context;
        unsigned int VBO;
        Shader* _shader;
        Camera3D* _camera;
};

#endif // __APPLICATION__
