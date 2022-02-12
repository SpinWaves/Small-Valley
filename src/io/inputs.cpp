// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "inputs.h"

Input::Input()
{
    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        _keys[i].first = false;
        _keys[i].second = false;
        if(i < 8)
        {
            _mouse[i].first = false;
            _mouse[i].second = false;
        }
    }
}

void Input::update()
{
    _xRel = 0;
    _yRel = 0;

    for(int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        _keys[i].second = false;
        if(i < 8)
            _mouse[i].second = false;
    }
    
    while(SDL_PollEvent(&_event))
    {
        if(_event.window.event == SDL_WINDOWEVENT_CLOSE) 
            _end = true;

        switch(_event.type) 
        {
            case SDL_KEYDOWN: 
                _keys[_event.key.keysym.scancode].first = true;
                _keys[_event.key.keysym.scancode].second = false;
            break;

            case SDL_KEYUP: 
                _keys[_event.key.keysym.scancode].first = false;
                _keys[_event.key.keysym.scancode].second = true;
            break;

            case SDL_MOUSEBUTTONDOWN: 
                _mouse[_event.button.button].first = true;
                _mouse[_event.button.button].second = false;
            break;

            case SDL_MOUSEBUTTONUP: 
                _mouse[_event.button.button].first = false;
                _mouse[_event.button.button].second = true;
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
