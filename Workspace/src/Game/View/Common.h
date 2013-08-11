#ifndef _COMMON_
#define _COMMON_

#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <functional>

#define TEX_WIDTH  256
#define TEX_HEIGHT 256

#define MAX_TEXTURES 10

// These are just visually "right" things. To be changed as appears right.
#define BOARD_TRANS  -8.0f
#define PIECE_TRANS  -7.96f
#define FOV_Y         25.0f 
#define BOARD_ROT     130.0f
#define BOARD_SCALE   (3.3f * 0.75f), (3.3f * 0.75f), (1.0f * 0.75f)
#define ASPECT_RATIO  1.0f
#define BOARD_SIZE    3.3f * 0.75f
#define PIECE_SIZE    (3.3f * 0.75f * 0.85f) / (8.0f) // 85% of each block

// #define  CHECK_GL_ERROR \{
//                         \    GLenum err = glGetError();
//                         \    assert( err == GL_NO_ERROR );
//                         \}
#endif
