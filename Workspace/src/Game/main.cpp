#include "view/DrawElement.h"
#include "view/Board.h"
#include "view/Scene.h"

using namespace View;
bool once = false;

Scene* scene;

void initShaders()
{
    DrawElement::init();
    scene = new Scene;
    const View::Position p1(2, 2);
    scene->addDrawElement(DrawElement::PAWN, p1 );

    const View::Position p2(4, 4);
    scene->addDrawElement(DrawElement::PAWN, p2 );
    
    const View::Position p3(1, 5);
    scene->addDrawElement(DrawElement::PAWN, p3 );    
    
    scene->addDrawElement(DrawElement::BOARD, p3);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->drawScene();
    glutSwapBuffers();
}

void glInitialisations()
{
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_DEPTH_TEST); //??
}
void idle()
{
    // no freeze. continuously render.
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Chess4Dummies");

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    if (glewInit())
    {
        assert(0);
        return 1;
    }

    glInitialisations();
    initShaders();
    glutMainLoop();
    return 0;
}