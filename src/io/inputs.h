// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __INPUTS__
#define __INPUTS__

#include <pch.h>

enum class action { up, down };

class Input
{
    public:
        Input();

        void update();

        inline bool getInKey(const SDL_Scancode key, action type = action::down) const noexcept { return type == action::down ? _keys[1][key] : _keys[0][key]; }

        inline bool getInMouse(const uint8_t button, action type = action::down) const noexcept { return type == action::down ? _mouse[1][button] : _mouse[0][button]; }
        inline bool isMouseMoving() const noexcept { return _xRel || _yRel ? true : false; }

        inline int getX() const noexcept { return _x; }
        inline int getY() const noexcept { return _y; }

        inline int getXRel() const noexcept { return _xRel; }
        inline int getYRel() const noexcept { return _yRel; }

        inline bool isEnded() const noexcept { return _end; }
        inline void finish() noexcept { _end = true; }

        ~Input() = default;

    private:
        SDL_Event _event;
        std::array<std::array<bool, 2>, SDL_NUM_SCANCODES> _keys;
        std::array<std::array<bool, 2>, 8> _mouse;

        int _x = 0;
        int _y = 0;
        int _xRel = 0;
        int _yRel = 0;

        bool _end = false;
};

#endif // __INPUTS__
