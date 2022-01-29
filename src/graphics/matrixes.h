#ifndef __MATRIXES__
#define __MATRIXES__

#include <pch.h>

enum class matrix { proj, model, view };

class Matrixes
{
    public:
        static void perspective(float FOV, float aspect, float near, float far);
        static void ortho(float left, float right, float top, float bottom);

        static void matrix_mode(matrix type);
        static glm::mat4 get_matrix(matrix type);
        static glm::mat4 get_current_matrix();

        static void lookAt(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z);

        static void load_identity();

        static void translate3D(double x, double y, double z);

    private:
        inline static glm::mat4 _proj;
        inline static glm::mat4 _model;
        inline static glm::mat4 _view;

        inline static matrix active_matrix;
};

#endif // __MATRIXES__
