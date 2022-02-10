#include "matrixes.h"
#include "camera.h"

Camera3D::Camera3D() : _up(0, 0, 1)
{
	_position.SET(0, 0, 0);
	update_view();
}

void Camera3D::onEvent(const Input& input)
{
	if(_isMouseGrabed)
	{
		_theta -= input.getXRel() * _sensivity;
		_phi -= input.getYRel() * _sensivity;
		update_view();
	}

	if(input.getInKey(SDL_SCANCODE_F1, action::up))
	{
		_isMouseGrabed = _isMouseGrabed ? SDL_FALSE : SDL_TRUE;
		SDL_SetRelativeMouseMode(_isMouseGrabed);
	}
	if(!_isMouseGrabed && input.getInMouse(1))
	{
		_isMouseGrabed = SDL_TRUE;
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	
	_speed = 0.15f;

	if(input.getInKey(SDL_SCANCODE_Q))
		_speed = 0.3f;
	if(input.getInKey(SDL_SCANCODE_W) || input.getInKey(SDL_SCANCODE_UP))
		_position -= _forward * _speed;
	if(input.getInKey(SDL_SCANCODE_S) || input.getInKey(SDL_SCANCODE_DOWN))
		_position += _forward * _speed;
	if(input.getInKey(SDL_SCANCODE_A) || input.getInKey(SDL_SCANCODE_LEFT))
		_position += _left * _speed;
	if(input.getInKey(SDL_SCANCODE_D) || input.getInKey(SDL_SCANCODE_RIGHT))
		_position -= _left * _speed;
	if(input.getInKey(SDL_SCANCODE_LSHIFT) || input.getInKey(SDL_SCANCODE_RSHIFT))
		_position -= _up * _speed;
	if(input.getInKey(SDL_SCANCODE_SPACE))
		_position += _up * _speed;
}

void Camera3D::update_view()
{
	_phi = _phi > 89 ? 89 : _phi;
	_phi = _phi < -89 ? -89 : _phi;

	_direction.X = cos(_phi * M_PI / 180) * cos(_theta * M_PI / 180);
	_direction.Y = cos(_phi * M_PI / 180) * sin(_theta * M_PI / 180);	// Spherical coordinate system
	_direction.Z = sin(_phi * M_PI / 180);

	_left = _up.crossProduct(_direction);
	_left.normalize();

	_forward = _up.crossProduct(_left);
	_forward.normalize();
}

void Camera3D::look()
{
	_target = _position + _direction;
    Matrixes::matrix_mode(matrix::view);
    Matrixes::lookAt(_position.X, _position.Y, _position.Z, _target.X, _target.Y, _target.Z, 0, 0, 1);
}
