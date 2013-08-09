#include "DrawElement.h"
#include "Board.h"

using namespace View;
bool once = false;

Board* b;

void initShaders()
{
    DrawElement::init();
    b = new Board;
    b->createGeometry();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    b->draw();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Chess4Dummies");

    glutDisplayFunc(display);

    if (glewInit())
    {
        assert(0);
        return 1;
    }

    initShaders();
    glutMainLoop();
    return 0;
}