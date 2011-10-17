#include "skyline.h"

void Refresh(GLubyte, GLint, GLint);

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(50, 100);
        glutInitWindowSize(1000, 500);
        glutCreateWindow("Skyline Problem!");
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0.0, 1000, 0.0, 500); /* OpenGL Init */
        srand((unsigned) time(NULL));
        glutDisplayFunc((void(*)) Refresh);
        glutKeyboardFunc(Refresh);
        glutMainLoop();
        return(0);
}
