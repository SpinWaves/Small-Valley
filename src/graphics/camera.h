#ifndef __CAMERA__
#define __CAMERA__ 

#include <pch.h>
#include <maths/vec3.h>
#include <io/inputs.h>

class Camera3D
{
	public:
		Camera3D();

		void update();
		void onEvent(const Input& input);
		void look();

		void setPosition(int pos_x, int pos_y, int pos_z);

		~Camera3D() = default;

	private:
		double _speed = 0.1;
		double _sensivity;

		double _theta;
		double _phi;

		double realspeed;
		
		SDL_bool _grabMouse = SDL_FALSE;

		void VectorsFromAngles();
		void Move(double x, double y, double z);

		Vec3<double> _movement;

		Vec3<double> _position;
		Vec3<double> _left;
		Vec3<double> _forward;
		Vec3<double> _up;
		Vec3<double> _target;
		Vec3<double> _direction;
};

#endif // __CAMERA__
