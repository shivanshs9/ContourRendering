#include "glrender.hpp"
#include "contour.hpp"
#include "model.hpp"

Model model;

void draw2() {
    /* clear the window */
    model.draw3D();
}

int main(int argc, char **argv) {
    initGL();
    createWin(
        argc, argv, "Contour Rendering", GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, 100, 100, 500, 500);
    char fname[40];
    cout << "Input contour filename: ";
    cin >> fname;
    model.loadContour(fname);
    glutDisplayFunc(draw2);
    glutMainLoop();
    return 0;
}
