#ifndef _TEXTURE_
#define _TEXTURE_


#include "Common.h"
#include <gl/glut.h>

namespace View {

// Responsible for: Reading of texture images, obtaining colors for a textcoord
class Texture 
{
public:
    // constrs
    Texture();
    Texture( const Texture& other );
    Texture( const char* fileName );

    void use() const;

private:
    void createTexture(const char* filename); // C stle IO used. So, const char* makes sense :D

    GLuint        _texID;
    unsigned char _texelData[TEX_WIDTH][TEX_HEIGHT][3];
    static int    _texIDs;
    int           _uniqeId;
};

}

#endif
