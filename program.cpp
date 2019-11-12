#include "glrender.hpp"
#include "contour.hpp"
#include "model.hpp"

Model model;

void draw2() {
    /* clear the window */
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
    model.draw3D();
}

int main(int argc, char **argv) {
    initGL();
    createWin(
        argc, argv, "Contour Rendering", GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH, 100, 100, 500, 500);
    char fname[40];
    cout << "Input contour filename: ";
    cin >> fname;
    model.loadContour(fname);
    glutDisplayFunc(draw2);
    glutMainLoop();
    return 0;
}
