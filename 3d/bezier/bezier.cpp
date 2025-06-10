struct XYZ
{
    float x;
    float y;
    float z;
};
#define GL_SILENCE_DEPRECATION

#ifndef NI
    #define NI 18
    #define NJ 6
    XYZ inp[NI+1][NJ+1];
    #define RESOLUTIONI 6*NI
    #define RESOLUTIONJ 6*NJ
    XYZ outp[RESOLUTIONI][RESOLUTIONJ];
#endif

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../materiais.hpp"
#include <iostream>
double frameNum = 0;

// Calcula o polinômio de Bernstein (função de mistura de Bézier)
double BezierBlend(int k,double mu, int n)
{
   int nn,kn,nkn;
   double blend=1;

   nn = n;
   kn = k;
   nkn = n - k;

   while (nn >= 1) {
      blend *= nn;
      nn--;
      if (kn > 1) {
         blend /= (double)kn;
         kn--;
      }
      if (nkn > 1) {
         blend /= (double)nkn;
         nkn--;
      }
   }
   if (k > 0)
      blend *= pow(mu,(double)k);
   if (n-k > 0)
      blend *= pow(1-mu,(double)(n-k));

   return(blend);
}



void generateControlPoint()
{
	   int nMax = 2;
	   int nMin = -2;
	   int i,j;
	   srandom(time(NULL));
	   for (i=0;i<=NI;i++) {
	      for (j=0;j<=NJ;j++) {
	         inp[i][j].x = i;
	         inp[i][j].y = j;
	         inp[i][j].z = random()%((nMax+1)-nMin) + nMin;
	         inp[i][j].z = 4*sin(i * frameNum*0.5);
	      }
	   }
}

void Surface()
{
   int i,j,ki,kj;
   double mui,muj,bi,bj;
   /* Create a random surface */
   for (i=0;i<RESOLUTIONI;i++) {
      mui = i / (double)(RESOLUTIONI-1);
      for (j=0;j<RESOLUTIONJ;j++) {
         muj = j / (double)(RESOLUTIONJ-1);
         outp[i][j].x = 0;
         outp[i][j].y = 0;
         outp[i][j].z = 0;
         for (ki=0;ki<=NI;ki++) {
            bi = BezierBlend(ki,mui,NI);
            for (kj=0;kj<=NJ;kj++) {
               bj = BezierBlend(kj,muj,NJ);
               outp[i][j].x += (inp[ki][kj].x * bi * bj);
               outp[i][j].y += (inp[ki][kj].y * bi * bj);
               outp[i][j].z += (inp[ki][kj].z * bi * bj);
            }
         }
      }
   }

}
void drawSurface() {
   for (int i = 0; i < RESOLUTIONI - 1; i++) {
      for (int j = 0; j < RESOLUTIONJ - 1; j++) {
         // Assign colors based on the position of the surface
         if (i < RESOLUTIONI / 3) {
            glColor3f(0.0, 0.0, 1.0); // Blue for the first third
         } else if (i < 2 * RESOLUTIONI / 3) {
            glColor3f(0.0, 1.0, 0.0); // Green for the second third
         } else {
            glColor3f(1.0, 0.0, 0.0); // Red for the last third
         }

         glBegin(GL_QUADS);
         glVertex3f(outp[i][j].x, outp[i][j].y, outp[i][j].z);
         glVertex3f(outp[i + 1][j].x, outp[i + 1][j].y, outp[i + 1][j].z);
         glVertex3f(outp[i + 1][j + 1].x, outp[i + 1][j + 1].y, outp[i + 1][j + 1].z);
         glVertex3f(outp[i][j + 1].x, outp[i][j + 1].y, outp[i][j + 1].z);
         glEnd();
      }
   }
}
void display(){

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat brown[] = { 0.6, 0.3, 0.1, 1.0 };
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // Reset matrix before gluLookAt

    gluLookAt(30.0, 70.0, 30.0,
        0.0, 0.0, 0.0,    
        0.0, 1.0, 0.0);   

   generateControlPoint();
   Surface();
   drawSurface();

   glFlush();
   glutSwapBuffers();

}

void doFrame(int v) {
    frameNum++;
    glutPostRedisplay();
    glutTimerFunc(100,doFrame,0);
}

// Função de redimensionamento da janela (Reshape Callback)
void reshape(int w, int h)
{
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

void init(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
   GLfloat blue_light[] = { 0.0, 0.0, 1.0, 1.0 };
   GLfloat light_position[] = { 10.0, 10.0, 10.0, 1.0 };

   glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light);
   glLightfv(GL_LIGHT2, GL_POSITION, light_position);
   glEnable(GL_LIGHT2);
    glEnable(GL_DEPTH_TEST);    

    glClearColor(1.0, 1.0, 1.0, 1.0); // fundo branco
}


/*void init(){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);                  // turn LIGHT0 on
    glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);  
    //glEnable(GL_LIGHT3);  
    //glEnable(GL_LIGHT4);  
    glEnable(GL_DEPTH_TEST);    
}*/

// Função Principal
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Mesa Posta de Jantar");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutTimerFunc(200,doFrame,0); 
  init();
  glutMainLoop();
}