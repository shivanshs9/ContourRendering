#include "model.hpp"
#include "contour.hpp"
#include "glrender.hpp"


using namespace std;

Model::Model() {
    contourBox = new ContourBox;
    rStyle = SMOOTH;
    meshOn = capsOn = false;
}

void Model::addContour(){
    cout<<"Enter the controls points coordinates (x, y) :\n( For exit : -1 -1)\n";
    int x=0,y=0;
    Contour c(this->contourBox);
    while(true){
        cin>>x>>y;
        if(x==-1 && y==-1) break;
        c.addControlPt(Point(x,y));
    }
    
    ContourPlane cPlane;
    cPlane.addContour(c);

    this->contourBox->addPlane(cPlane);

    currLevel++;
    numContours++;
}

void Model::loadContour(char *filename) {
    int x, y, numVertices;
    delete contourBox;
    contourBox = new ContourBox;
    ifstream in(filename);

    in >> numContours;
    in >> sepPlane;
    rep(i, 0, numContours) {
        in >> numVertices;
        Contour newContour(contourBox);
        rep(j, 0, numVertices) {
            in >> x >> y;
            newContour.addControlPt(Point(x, y));
        }

        ContourPlane newPlane;
        newPlane.addContour(newContour);
        contourBox->addPlane(newPlane);
        contourBox->finishContourLoad(i, 0);
    }
    rep(i, 1, numContours) {
        Point upper, lower;
        upper.x = i;
        lower.x = i - 1;
        upper.y = 0;
        lower.y = 0;
        contourBox->newStrip(upper, lower);
    }
}

void Model::listContours(){
    int lev = contourBox->contourSet.size();
    vector<ContourPlane> &v = contourBox->contourSet;
    rep(i,0,lev){
        cout<<"Level : "<<i<<"\n";
        cout<<"Contours : \n";
        rep(j,0,v[i].planeContours.size()){
            cout<<"Contour No : "<<j<<" | ";
            vector<Point> &temp = v[i].planeContours[j].controlPts;
            cout<<"Points : ";
            rep(k,0,temp.size()) cout<<temp[k].x<<", "<<temp[k].y<<" ; ";
        }
        cout<<endl;
    }
}

void Model::draw3D(){
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_FOG);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel( GL_SMOOTH );
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode( GL_PROJECTION );
    // glLoadMatrixd((const GLdouble *) projection_mat.Ref());

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    this->contourBox->draw3D(sepPlane, rStyle, meshOn, capsOn);


    glDisable(GL_COLOR_MATERIAL);

    /* house shape */
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2i(0, 0);
        glVertex2i(10, 0);
        glVertex2i(10, 10);
        glVertex2i(0, 10);
    glEnd();
    cout << "Swapping buffers..." << endl;
    glutSwapBuffers();
}

void Model::refresh(){

}

void Model::eraseAll(){

}