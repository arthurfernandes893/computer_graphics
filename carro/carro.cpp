#define GL_SILENCE_DEPRECATION
//#include <GLUT/glut.h> //mac os
#include <GL/glut.h> //linux

#include <math.h>


void init(void);
void display(void);

float PI = 3.14;

void init(void)
{
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-10, 10, -10, 10, -10, 10);
}

void square()
{
	  glBegin(GL_POLYGON);
	    glVertex3f(-1, -1, 0);
	    glVertex3f(1, -1, 0);
	    glVertex3f(1, 1, 0);
	    glVertex3f(-1, 1, 0);
	  glEnd();
}

void triangle() {
	glBegin(GL_POLYGON);
	  glVertex3f(-1, 0, 0);
	  glVertex3f(0, 1, 0);
	  glVertex3f(1, 0, 0);
	glEnd();
}

void circle(double radius){
    glBegin(GL_POLYGON);
    for (int i = 0; i<32; i++){
        double angle = (2*PI/32)*i;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}


void drawCar(){
    glColor3f(0, 0.7, 1);
    
    //rodas
    double scale = 0.5;
    struct translate{
        double x = 1.0;
        double y = 0.3;
    } translate;
    double roda = 1.0;
    double midroda = 0.55;
    double subroda = 0.3;
    glPushMatrix();
    glTranslated(-translate.x, translate.y, 0);
    glScaled(scale, scale, 1);
    circle(roda);
    glPopMatrix();

    glPushMatrix();
    glTranslated(translate.x, translate.y, 0);
    glScaled(scale, scale, 1);
    circle(roda);
    glPopMatrix();

    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslated(-translate.x, translate.y, 0);
    glScaled(scale, scale, 1);
    circle(midroda*roda);
    glPopMatrix();

    glPushMatrix();
    glTranslated(translate.x, translate.y, 0);
    glScaled(scale, scale, 1);
    circle(midroda*roda);
    glPopMatrix();
    

    glColor3f(1, 0, 0);
    //carroceria
    glPushMatrix();
    glTranslated(0, 0.7, 0);
    glScaled(1.8, 0.4, 1);
    square();
    glPopMatrix();

    //capo
    glPushMatrix();
    glTranslated(-0.5, 1.25, 0);
    glScaled(1.2, 0.4, 1);
    square();
    glPopMatrix();
}
void display() {

    // Limpa a janela, colocando na tela a cor definida pela função glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    drawCar();
    // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
    glFlush();
}



int main(int argc, char** argv)
{

 //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
 //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize (800, 800);
  glutInitWindowPosition (200, 200);

  // Cria uma janela e define seu título
  glutCreateWindow ("Primeiro OpenGL");

  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();

  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
  glutDisplayFunc(display);

  //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}