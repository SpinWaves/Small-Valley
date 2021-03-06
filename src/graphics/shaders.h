// Copyright (C) 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Small Valley"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __SHADERS__
#define __SHADERS__

#include <maths/vec2.h>
#include <maths/vec3.h>
#include <maths/vec4.h>

class Shader
{
    public:
        Shader() = default;

        void create(const char* vertexFile, const char* fragmentFile);

        void bindShader();
        void unbindShader();
        bool isBinded();

        void setFloat(const std::string& name, float v);
        void setInt(const std::string& name, int v);
        void setBool(const std::string& name, bool v);
        void setVec3(const std::string& name, Vec3<float> v);
        void setVec2(const std::string& name, Vec2<float> v);
        void setVec4(const std::string& name, Vec4<float> v);
        void setVec3(const std::string& name, float x, float y, float z);
        void setVec2(const std::string& name, float x, float y);
        void setVec4(const std::string& name, float x, float y, float z, float t);
        void setMat4(const std::string& name, glm::mat4 matrix);

        ~Shader();

    private:
        char* LoadSourceShader(const char* filename);
        void createShader(const char* source, int type);

        GLuint program = 0;
        int shader = 0;

        const char* _filename = nullptr;
};

#endif // __SHADERS__
