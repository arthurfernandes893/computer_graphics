#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>


void init(void);
void display(void);

void square(){

    glBegin(GL_POLYGON);
       glColor3f(1, 0, 0);
        glVertex3f(-1, -1, 0);
        glVertex3f( 1, -1, 0);
        glVertex3f( 1, 1, 0);
        glVertex3f(-1, 1, 0);
    glEnd();

}

void triangle(){

     glBegin(GL_POLYGON);
        glColor3f(0, 1, 0);
        glVertex3f(0, 1, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(-1, 0, 0);
    glEnd();
 
}

void sun(){

    square();
    glRotated(45,0,0,1);
    square();
    glTranslated(5,5,0);
}

void tower(char position){
  glScaled(2,4,1);

  //position == 'l' ? glTranslated(-5,,0) : glTranslated(,,0);

  square();
  towerRoof();
}

void towerRoof(/*Posicao do zero do TowerRoof*/){

  //glScaled(x,y,1);
  triangle();

}

void towers(GLdouble x, GLdouble y){

  tower('l');
  tower('r');

}
void castle(int x, int y){
  
  glScaled(x,y,1);
  square();

  castleDoor(x,y);
  castleWindow(x,y);
  
}

void castleDoor(double x, double y){
 
  double reduction = 0.3;
  glScaled(reduction * x, reduction * y,1);
  square();

}

void castleWindow(double x, double y){
  double reduction = 0.3;
  glScaled(reduction * x, reduction * y,1);
  //glTranslated(x,y,0);
  square();

}
void init(void)
{
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  glOrtho (-10, 10, -10, 10, -10, 10);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    int x = 4; int y = 3;
    /*
    castle(x,y);
    towers(x, y);
    sun();
     */

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

/**CALL STACK 
 * display
 * | castle
 *   | castledoor
 *   | castlewindow
 * | towers
 *   | tower
 *     | towerroof
 *   | tower
 *     | towerroof
 * | sun
 */
