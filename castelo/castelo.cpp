#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h> //mac os
//#include <GL/glut.h> //linux


void init(void);
void display(void);


void castleDoor(double x, double y);
void square();
void triangle();
void sun();
void tower(char position,int x, int y);
void towerRoof(/*Posicao do zero do TowerRoof*/);
void towers(GLdouble x, GLdouble y);
void castle(int x, int y);

void square(){
    glBegin(GL_POLYGON);
       glColor3f(1, 0, 0); // vermelho
        glVertex3f(-1, -1, 0);
        glVertex3f( 1, -1, 0);
        glVertex3f( 1, 1, 0);
        glVertex3f(-1, 1, 0);
    glEnd();
}

void triangle(){
     glBegin(GL_POLYGON);
        glColor3f(0, 1, 0); // verde
        glVertex3f(0, 1, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(-1, 0, 0);
    glEnd();
}

void sun(){
    glLoadIdentity();
    glColor3f(1, 1, 0); // amarelo

    square();
    glRotated(45,0,0,1);
    square();
    glTranslated(5,5,0);
}

void tower(char position,int x, int y){
  glLoadIdentity();
  glColor3f(0.5, 0.5, 1); // azul claro

  glScaled(2,4,1);
  position == 'l' ? glTranslated(-x-(x/2),y,0) : glTranslated(x+(x/2),y,0);
  square();
  //towerRoof();
}

void towerRoof(/*Posicao do zero do TowerRoof*/){
  glColor3f(0.7, 0.3, 0.1); // marrom

  triangle();
}

void towers(GLdouble x, GLdouble y){
  glColor3f(0.8, 0.4, 0.9); // roxo claro

  tower('l', x, y);
  tower('r', x, y);
}

void castle(int x, int y){
  glLoadIdentity();
  glColor3f(0.4, 0.4, 0.4); // cinza

  glScaled(x,y,1);
  square();

  //castleDoor(x,y);
  //castleWindow(x,y);
}

void castleDoor(double x, double y){
  glLoadIdentity();
  glColor3f(0.6, 0.3, 0); // marrom escuro

  double reduction = 0.3;
  glScaled(reduction * x, reduction * y,1);
  square();
}

void castleWindow(double x, double y){
  glLoadIdentity();
  glColor3f(0, 1, 1); // ciano

  double reduction = 0.3;
  glScaled(reduction * x, reduction * y,1);
  square();
}

void init(void)
{
  glClearColor(0, 0, 0, 0);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-10, 10, -10, 10, -10, 10);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    int x = 4; int y = 3;
    
    castle(x,y);
    towers(x, y);
    sun();
    
    glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (800, 800);
  glutInitWindowPosition (200, 200);
  glutCreateWindow ("Primeiro OpenGL");

  init();
  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}
