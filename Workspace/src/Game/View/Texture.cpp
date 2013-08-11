#define _DEBUG_TEX
#undef  _DEBUG_TEX

#include "Common.h"
#include "Shader.h"
#include "Texture.h"

using namespace View;

Texture::Texture()
{
    _uniqeId = _texIDs++;
}

void Texture::createTexture(const char* filename)
{
    FILE* texFile;
    unsigned char arr[54];
    _uniqeId = _texIDs++;

    if ( (texFile = fopen(filename, "rb")) == NULL ) 
    {
        std::cout << "\nError: Cannot open file for texture!";
        assert(0);
    } 
    else 
    {
        std::cout << "\nFile: " << filename << " Opened!";
        fread(arr, 1, 54, texFile);
        fread(_texelData, 1, TEX_WIDTH * TEX_HEIGHT * 3, texFile);

        glGenTextures(1, &_texID);
        glBindTexture(GL_TEXTURE_2D, _texID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_WIDTH, TEX_HEIGHT,
                     0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _texelData);
        glBindTexture(GL_TEXTURE_2D, 0);
        fclose(texFile);
    }
}



View::Texture::Texture( const char* fileName )
{
    createTexture(fileName);
}

void View::Texture::use() const
{
    glActiveTexture(GL_TEXTURE0 + _uniqeId);
    glBindTexture(GL_TEXTURE_2D, _texID);
}

void View::Texture::unUse() const
{
    // Doing this every frame. Is this ok?!
    glBindTexture(GL_TEXTURE_2D, 0);
}

int View::Texture::_texIDs = 0;
