#ifndef __TEXTURES__
#define __TEXTURES__

#include <pch.h>

class Texture
{
    public:
        Texture() = default;

        void load_texture(const char* filename);
        inline void bind_texture()   { glBindTexture(GL_TEXTURE_2D, _texture); }
        inline void unbind_texture() { glBindTexture(GL_TEXTURE_2D, 0); }
        inline void free_texture()   { glDeleteTextures(1, &_texture); _texture = 0; }

        ~Texture();

    private:
        GLuint _texture = 0;
};

#endif // __TEXTURES__
