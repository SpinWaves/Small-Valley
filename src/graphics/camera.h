// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __CAMERA__
#define __CAMERA__ 

#include <pch.h>
#include <maths/vec3.h>
#include <io/inputs.h>

class Camera3D
{
	public:
		Camera3D();

		void onEvent(const Input& input);
		void look();

		inline void setPosition(int pos_x, int pos_y, int pos_z) noexcept { _position.SET(pos_x, pos_y, pos_z); }

		~Camera3D() = default;

	private:
		float _speed = 0.15f;
		const float _sensivity = 1.2f;

		double _theta = 0;
		double _phi = -79;

		SDL_bool _isMouseGrabed = SDL_FALSE;

		void update_view();

		Vec3<double> _position;
		Vec3<double> _left;
		Vec3<double> _forward;
		const Vec3<double> _up;
		Vec3<double> _target;
		Vec3<double> _direction;
};

#endif // __CAMERA__
