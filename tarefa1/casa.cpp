#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>


void init(void);
void display(void);


int polygon = 4;

void init(void)
{
  // define a cor de background da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // define o sistema de visualização - tipo de projeção
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-10, 10, -10, 10, -10, 10);
}

void display(){
    // Limpa a janela, colocando na tela a cor definida pela função glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    //casa
    glBegin(GL_POLYGON);
        glColor3f(0, 70.0, 70.0);
        glVertex3f(-6, -5, 0);
        glVertex3f( 6, -5, 0);
        glVertex3f( 6, 5, 0);
        glVertex3f(-6, 5, 0);
    glEnd();

    //telhado
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);
        glVertex3f(6, 5, 0.5);
        glColor3f(0, 1, 0);
        glVertex3f(-6, 5, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 10, 0);
    glEnd();

    //porta
    glBegin(GL_POLYGON);
      glColor3f(128, 70, 0);
      glVertex3f(-1.7, -4.8, 0);
      glVertex3f(1.7, -4.8, 0);
      glVertex3f(1.7, 3, 0);
      glVertex3f(-1.7, 3, 0);
    glEnd();

    //janela
    float janela_W0 = 2.5;
    float janela_w1 = 5;
    float janela_h0 = -0.5;
    float janela_h1 = 2.3;
    glBegin(GL_POLYGON);
        glColor3f(255, 0, 0);
        glVertex3f(janela_W0, janela_h0, 0);
        glVertex3f(janela_w1, janela_h0, 0);
        glVertex3f(janela_w1,  janela_h1, 0);
        glVertex3f(janela_W0,  janela_h1, 0);
    glEnd();

    glBegin(GL_LINES);
     
      glVertex2f(janela_W0*1.5, janela_h0);
      glVertex2f(janela_h0, janela_w1*1.5);
    glEnd();


      

  // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
  glFlush();
}

void keyboard( unsigned char key, int x, int y )
{
	switch( key ) {
	case 32 :
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
		
	break;
  
  default:
    glClearColor(1.0, 1.0, 1.0, 1.0);

	break;
	}
display();
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


  glutKeyboardFunc(keyboard);

   //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}

/*
======================================

SEGUNDA ATIVIDADE

======================================
*/

