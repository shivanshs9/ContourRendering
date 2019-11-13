#include "macros.hpp"
#include "glrender.hpp"

using namespace std;

void initGL() {
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10,10,-10,10);
}

void createWin(int argc,char** argv, char* name,int mode, int x, int y, int h,int w){
    glutInit(&argc,argv);
    glutInitDisplayMode(mode);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(x,y);
    glutCreateWindow(name);
}