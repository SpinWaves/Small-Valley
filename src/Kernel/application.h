#ifndef __APPLICATION__
#define __APPLICATION__

#include <pch.h>
#include <io/inputs.h>
#include <graphics/shaders.h>
#include <graphics/camera.h>
#include <entities/world.h>
#include <graphics/textures.h>

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
        Texture* _tex = nullptr;
        std::shared_ptr<World> _world;
};

#endif // __APPLICATION__
