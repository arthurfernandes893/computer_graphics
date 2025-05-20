// https://cs.lmu.edu/~ray/notes/openglexamples/
// g++ litsolids.cpp -lX11 -lGL -lGLU -lglut -g -Wall -O2 -o r.exe
//
// This program shows three cyan objects illuminated with a single yellow
// light source.  It illustrates several of the lighting parameters.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>

float cameraAngle = 0.0f; // In degrees
const float radius = 5.0f;





// Clears the window and depth buffer and draws three solids.
//
// The solids are placed so that they either sit or float above the x-z plane;
// therefore note one of the first things that is done is to rotate the whole
// scene 20 degrees about x to turn the top of the scene toward the viewer.
// This lets the viewer see how the torus goes around the cone.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);

    float radians = cameraAngle * 3.14159f / 180.0f;
    float camX = radius * sinf(radians);
    float camZ = radius * cosf(radians);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // Reset matrix before gluLookAt

    gluLookAt(camX, 1.0, camZ,   // Camera position (1.0 height)
            0.0, 1.0, 0.0,     // Look at center of cube
            0.0, 1.0, 0.0);    // Up direction

     
    glPushMatrix();
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(3.0, 0.2, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();
    
    float legHeight = 1.0;
    float x = 1.3, z = 0.9;

    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
                glTranslatef(i * x, legHeight / 2, j * z); 
                glScalef(0.2, legHeight, 0.2);
                glutSolidCube(1.0);
            glPopMatrix();
        }
    }


    glFlush();
    glutSwapBuffers();
}

// We don't want the scene to get distorted when the window size changes, so
// we need a reshape callback.  We'll always maintain a range of -2.5..2.5 in
// the smaller of the width and height for our viewbox, and a range of -10..10
// for the viewbox depth.

//PARAMETROS glOrtho
//left, right :Specify the coordinates for the left and right vertical clipping planes.
//bottom, top :Specify the coordinates for the bottom and top horizontal clipping planes.
//nearVal, farVal:Specify the distances to the nearer and farther depth clipping planes. These values are negative if the plane is to be behind the viewer.

/**/
void reshape(GLint w, GLint h) {
  glMatrixMode(GL_PROJECTION);
  GLfloat aspect = GLfloat(w) / GLfloat(h);
  glLoadIdentity();

/* if (w <= h) {
    // width is smaller, so stretch out the height
    glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
  } else {
    // height is smaller, so stretch out the width
    glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
  }
  */
  gluPerspective (60,aspect, 0.1, 100);

}

// Performs application specific initialization.  It defines lighting
// parameters for light source GL_LIGHT0: black for ambient, yellow for
// diffuse, white for specular, and makes it a directional source
// shining along <-1, -1, -1>.  It also sets a couple material properties
// to make cyan colored objects with a fairly low shininess value.  Lighting
// and depth buffer hidden surface removal are enabled here.
void init() {

  GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat direction[] = { 0.0, -10.0, 0.0, 1.0 };
  GLfloat direction1[] = { 0.0, 10.0, 0.0, 1.0 };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);

  glLightfv(GL_LIGHT0, GL_AMBIENT, black);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_POSITION, direction);

  glLightfv(GL_LIGHT1, GL_AMBIENT, black);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  glLightfv(GL_LIGHT1, GL_POSITION, direction1);

  glEnable(GL_LIGHTING);                // so the renderer considers light
  glEnable(GL_LIGHT0);                  // turn LIGHT0 on
  glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);              // so the renderer considers depth

}



void keyboard(unsigned char key, int x, int y)
{
    float dAngle = 5.0f; // Degrees to rotate per key press

    switch (key) {
        case 'a': case 'A':
            cameraAngle -= dAngle;
            break;
        case 'd': case 'D':
            cameraAngle += dAngle;
            break;
    }

    glutPostRedisplay(); // Request redraw
}




// The usual application statup code.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Cyan Shapes in Yellow Light");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

    
  glutKeyboardFunc(keyboard);


  init();
  glutMainLoop();
}