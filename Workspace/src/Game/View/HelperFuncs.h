#ifndef HELPER_FUNCS
#define HELPER_FUNCS

#include "Common.h"
#include <GL/glew.h>
#include <GL/glut.h>


// Open Source:
// Example from
// Author: Jakob Progsch
namespace Helpers 
{
    bool check_shader_compile_status(GLuint obj);
    bool check_program_link_status(GLuint obj);
}


#endif