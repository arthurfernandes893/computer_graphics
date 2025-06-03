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
#include "../materiais.hpp"

float cameraAngle = 0.0f; // In degrees
const float radius = 5.0f;



void chair() {
    // Define chair dimensions
    float seatWidth = 0.8f;
    float seatHeight = 0.1f;
    float seatDepth = 0.8f;
    float legHeight = 0.5f;
    float legSide = 0.1f; // Thickness of the leg (assuming square legs)
    float backrestWidth = seatWidth;
    float backrestHeight = 0.7f;
    float backrestThickness = 0.1f;

    // Base of the chair is at (0,0,0) in its local coordinates

    // Draw Seat
    glPushMatrix();
    // The seat is placed on top of the legs.
    // Center of the seat: (0, legHeight + seatHeight/2, 0)
    glTranslatef(0.0f, legHeight + seatHeight / 2.0f, 0.0f);
    glScalef(seatWidth, seatHeight, seatDepth);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw Legs (4 legs)
    float legOffsetW = seatWidth / 2.0f - legSide / 2.0f;
    float legOffsetD = seatDepth / 2.0f - legSide / 2.0f;
    float legCenterY = legHeight / 2.0f;

    // Positions for the center of each leg's base
    float legPositions[4][3] = {
        { legOffsetW, legCenterY,  legOffsetD}, // Front-Right
        {-legOffsetW, legCenterY,  legOffsetD}, // Front-Left
        { legOffsetW, legCenterY, -legOffsetD}, // Back-Right
        {-legOffsetW, legCenterY, -legOffsetD}  // Back-Left
    };

    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef(legPositions[i][0], legPositions[i][1], legPositions[i][2]);
        glScalef(legSide, legHeight, legSide);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Draw Backrest
    // The backrest sits on the back edge of the seat.
    // Center Y of backrest: top of seat (legHeight + seatHeight) + backrestHeight/2
    // Center Z of backrest: back edge of seat (-seatDepth/2) - backrestThickness/2
    float backrestCenterY = (legHeight + seatHeight) + backrestHeight / 2.0f;
    float backrestCenterZ = -seatDepth / 2.0f - backrestThickness / 2.0f;

    glPushMatrix();
    glTranslatef(0.0f, backrestCenterY, backrestCenterZ);
    glScalef(backrestWidth, backrestHeight, backrestThickness);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void position_chair(){
   float x = 0.7, z = 0.9;

  for (int i = -1; i <=1; i+=2){
    for(int j = -1; j <= 1; j+=2){
      glPushMatrix();
        glTranslatef(i * x, 0, j * z);
        j > 0 ? glRotated(180,0,1,0): glRotated(0,0,0,1);
        chair();
      glPopMatrix();
    }
  }

}

void drawChairs(){
  glPushMatrix();
    int material = 7;
    materialColors(material);
    position_chair();
  glPopMatrix();
}

void towel(){
  glPushMatrix();
        glTranslatef(0.0, 0.85, 0.0);
        glScalef(0.8, 0.04, 0.7);
        glutSolidCube(1.0);
  glPopMatrix();
}

void position_towel(){
  float x = 0.7, z = 0.65;

  for (int i = -1; i <=1; i+=2){
    for(int j = -1; j <= 1; j+=2){
      glPushMatrix();
        glTranslatef(i * x, 0, j * z);
        towel();
      glPopMatrix();
    }
  }

}

void drawTowels(){
  glPushMatrix();
    int material = 11;
    materialColors(material);
    position_towel();
  glPopMatrix();
}

void plate(){
    glPushMatrix();
       glTranslatef(0.0, 0.9, 0.0);
      glRotated(90,1,0,0);
      glScalef(0.5, 0.5, 0.09);
      glutSolidTorus(0.175, 0.25, 16, 40);
    glPopMatrix();
}

void position_plates(){
  float x = 0.7, z = 0.65;

  for (int i = -1; i <=1; i+=2){
    for(int j = -1; j <= 1; j+=2){
      glPushMatrix();
        glTranslatef(i * x, 0, j * z);
        plate();
      glPopMatrix();
    }
  }

}

void drawPlates(){
    glPushMatrix();
    int material = 6;
    materialColors(material);
    position_plates();
  glPopMatrix();

}

void cup(){}

void table(){
  glPushMatrix();
        glTranslatef(0.0, 0.8, 0.0);
        glScalef(3.0, 0.1, 2.0);
        glutSolidCube(1.0);
  glPopMatrix();
    
    float legHeight = 0.8;
    float x = 1.3, z = 0.9;

    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
                glTranslatef(i * x, legHeight / 2, j * z); 
                glScalef(0.15, legHeight, 0.15);
                glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}

void drawTable(){

  glPushMatrix();
    int material = 0;
    materialColors(material);
    table();
  glPopMatrix();
}
// Clears the window and depth buffer and draws three solids.
//
// The solids are placed so that they either sit or float above the x-z plane;
// therefore note one of the first things that is done is to rotate the whole
// scene 20 degrees about x to turn the top of the scene toward the viewer.
// This lets the viewer see how the torus goes around the cone.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      
    GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat brown[] = { 0.6, 0.3, 0.1, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };

    glMatrixMode(GL_MODELVIEW);

    float radians = cameraAngle * 3.14159f / 180.0f;
    float camX = radius * sinf(radians);
    float camZ = radius * cosf(radians);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // Reset matrix before gluLookAt

    //gluLookAt(camX, 2.0, camZ,   // Camera position (1.0 height)
    //        0.0, 1.0, 0.0,     // Look at center of cube
    //        0.0, 1.0, 0.0);    // Up direction

    gluLookAt(-3.0, 2.5, 3.0,
        0.0, 1.0, 0.0,    
        0.0, 1.0, 0.0);   

    
    //onde a luz esta, qual tipo de luz,  sua cor
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, brown);
    drawChairs();
    drawTable();
    drawTowels();
    drawPlates();

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

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_NORMALIZE);

  glEnable(GL_LIGHTING);                // so the renderer considers light
  glEnable(GL_LIGHT0);                  // turn LIGHT0 on
  glEnable(GL_LIGHT1);
  //glEnable(GL_LIGHT2);  
  //glEnable(GL_LIGHT3);  
  //glEnable(GL_LIGHT4);  
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
  glutCreateWindow("Mesa Posta de Jantar");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

    
  glutKeyboardFunc(keyboard);


  init();
  glutMainLoop();
}