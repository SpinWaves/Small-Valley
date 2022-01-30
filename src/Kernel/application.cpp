#include "application.h"
#include <graphics/matrixes.h>

Application::Application() : _shader(), _camera(), _cube() {}

void Application::init(const char* name)
{
    _win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!_win)
    {
        SDL_Quit();
        log::report(log_type::fatal_error, "Unable to create the window");
    }

    _context = SDL_GL_CreateContext(_win);
    if(!_context)
    {
        SDL_DestroyWindow(_win);
        SDL_Quit();
        log::report(log_type::fatal_error, "Unable to create OpenGL context");
    }
    SDL_GL_MakeCurrent(_win, _context);

    GLuint GLEWerr = glewInit();
    if(GLEW_OK != GLEWerr)
    {
        SDL_DestroyWindow(_win);
        SDL_Quit();
        log::report(log_type::fatal_error, "Unable to init GLEW");
    }

    _shader.create(MAIN_DIR"src/graphics/shaders/main_3D.vert", MAIN_DIR"src/graphics/shaders/main_3D.frag");
    _shader.bindShader();

    _camera.setPosition(-2, -2, 2);

    _tex = new Texture();
    _tex->load_texture(RES_DIR"assets/grass.jpg");

    _cube.create(1, 1, 1);

    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
}

void Application::update(const Input& in)
{
    SDL_GL_SetSwapInterval(0);

    _camera.onEvent(in);
    _camera.look();

    Matrixes::matrix_mode(matrix::proj);
    Matrixes::perspective(90, (float)1280/720, 0.01, 100);

    Matrixes::matrix_mode(matrix::model);
    Matrixes::load_identity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.49f, 0.66f, 0.85f, 1.0f);

    _shader.setMat4("view", Matrixes::get_matrix(matrix::view));
    _shader.setMat4("proj", Matrixes::get_matrix(matrix::proj));
    _shader.setMat4("model", Matrixes::get_matrix(matrix::model));

    glEnable(GL_TEXTURE_2D);
    _tex->bind_texture();

    _cube.render();

    _tex->unbind_texture();

    SDL_GL_SwapWindow(_win);
}

void Application::destroy()
{
    delete _tex;
    
    SDL_GL_DeleteContext(_context);
    SDL_DestroyWindow(_win);
    _win = nullptr;
}

Application::~Application()
{
    if(_win != nullptr)
        destroy();
}
