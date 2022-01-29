#include "inputs.h"

Input::Input()
{
    _x = 0;
    _y = 0;
    _xRel = 0;
    _yRel = 0;

    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        _keys[0][i] = false;
        _keys[1][i] = false;
        if(i < 8)
        {
            _mouse[0][i] = false;
            _mouse[1][i] = false;
        }
    }
}

void Input::update()
{
    _xRel = 0;
    _yRel = 0;

    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        _keys[0][i] = false;
        if(i < 8)
            _mouse[0][i] = false;
    }

    while(SDL_PollEvent(&_event))
    {
        if(_event.window.event == SDL_WINDOWEVENT_CLOSE) 
            _end = true;

        switch(_event.type) 
        {
            case SDL_KEYDOWN: 
                _keys[1][_event.key.keysym.scancode] = true;
                _keys[0][_event.key.keysym.scancode] = false;
            break;


            case SDL_KEYUP: 
                _keys[1][_event.key.keysym.scancode] = false;
                _keys[0][_event.key.keysym.scancode] = true;
            break;

            case SDL_MOUSEBUTTONDOWN: 
                _mouse[1][_event.button.button] = true;
                _mouse[0][_event.button.button] = false;
            break;

            case SDL_MOUSEBUTTONUP: 
                _mouse[1][_event.button.button] = false;
                _mouse[0][_event.button.button] = true;
            break;

            default: break;
        }

        if(_event.type == SDL_MOUSEMOTION) 
        {
            _x = _event.motion.x;
            _y = _event.motion.y;

            _xRel = _event.motion.xrel;
            _yRel = _event.motion.yrel;
        }
    }
}
