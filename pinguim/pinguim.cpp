#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h> //mac os
//#include <GL/glut.h> //linux

#include <math.h>
#include <iostream>

using namespace std;

void init(void);
void display(void);

float PI = 3.14;
int window_size = 1000;

int frameNumber = 0;
double posicao_carro = 0;
double posicao_carro_dir = 0;
double posicao_carro_esq = 0;
double previous_posicao_carro = 0;
bool keep = true;
/*Parear com o translate do objeto usando a função keyboard, para movimentar em um dx*/
/*se a divisao do frame for tal, desenhar objeto*/

struct mounts_coords{
    double m1_x = -window_size/100 + 4;
    double m2_x = -window_size/100 +10;
    double m3_x = -window_size/100 +17.5;
    double y = -window_size/130;
} mounts_coords;

struct windMill_coords{

}windmill_coords;

void init(void)
{
    // define a cor de background da janela
    //glClearColor(1.0, 1.0, 1.0, 1.0); //white

    //glClearColor(1.0f, 0.45f, 0.2f, 1.0f); //sunset

    glClearColor(0.68f, 0.85f, 0.9f, 1.0f); //morning


  // define o sistema de visualização - tipo de projeção
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-10, 10, -10, 10, -10, 10);
  glMatrixMode(GL_MODELVIEW);
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


void sun(){
    int i;
    glColor3f(1,1,0);
    
    glPushMatrix();
    glRotated(-frameNumber*0.7,0,0,1);
    for(int i = 0; i < 13; i++){
        glRotatef(360/13, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(0.75f,0);
        glEnd();
    }
    glPopMatrix();
    circle(0.5);
    glColor3f(0,0,0);
}
void drawSun(){
    glPushMatrix();
    glTranslated(window_size*0.75/100, window_size*0.75/100, 0);
    glScaled(2.5, 2.5, 1);
    sun();
    glPopMatrix();
}

void icebergs(){
   glColor3f(0.90f, 0.95f, 0.98f);
    glPushMatrix();
        glTranslated(0 ,1.5, 0);
        glScaled(1.3,2,1);

        glPushMatrix();
            glTranslated(mounts_coords.m1_x + 3 ,mounts_coords.y+1.5, 0);
            glScaled(10,6,1);
            glRotated(5,0,0,1);
            triangle();
        glPopMatrix();
        
        glPushMatrix();
            glTranslated(mounts_coords.m2_x + 2,mounts_coords.y+2, 0);
            glScaled(10,6,1);
            glRotated(-5,0,0,1);
            triangle();
        glPopMatrix();
        
        glPushMatrix();
            glTranslated(mounts_coords.m3_x ,mounts_coords.y, 0);
            glScaled(10,6,1);
            glRotated(-5,0,0,1);
            triangle();
        glPopMatrix();

        glPushMatrix();
            glTranslated(mounts_coords.m1_x ,mounts_coords.y ,0);
            glScaled(10,7,1);
            triangle();
        glPopMatrix();

        glPushMatrix();
            glTranslated(mounts_coords.m2_x,mounts_coords.y, 0);
            glScaled(10,8.5,1);
            triangle();
        glPopMatrix(); 
    glPopMatrix();
    
}

void drawIceSheet(){
    glColor3f(0.50f, 0.80f, 1.00f);
    glPushMatrix();
        glTranslated(-window_size/200, -window_size/130, 0);
        glScaled(6, 3, 1);
        square();
    glPopMatrix();
}

void drawSea(){
    glColor3f(0.00f, 0.50f, 0.70f);
    glPushMatrix();
        glTranslated(window_size/200, -window_size/130, 0);
        glScaled(6, 3, 1);
        square();
    glPopMatrix();
}

void drawPenguim() {
    glPushMatrix();
        glTranslated(-3, -window_size/130 + 3, 0);
        glPushMatrix();
            // Corpo (óvalo preto)
            glPushMatrix();
                glColor3f(0.05f, 0.05f, 0.05f);      // preto
                glScaled(0.5f, 1.0f, 1.0f);          // torna o círculo em oval vertical
                circle(1.0);
            glPopMatrix();

            // Barriga (óvalo branco, levemente menor que o corpo)
            glPushMatrix();
                glColor3f(1.00f, 1.00f, 1.00f);      // branco
                glScaled(0.3f, 0.6f, 1.0f);
                glTranslated(0.0, 1.0f, 0.0);        // sobe para ficar centralizado na parte frontal do corpo
                circle(1.0);
            glPopMatrix();

            // Pés (dois triângulos vermelhos invertidos)
            glColor3f(0.65f, 0.10f, 0.10f);          // vermelho escuro
            // Pé esquerdo
            glPushMatrix();
                glTranslated(-0.3f, -1.0f, 0.0f);   // posiciona à esquerda e abaixo do corpo
                glScaled(0.3f, 0.3f, 1.0f);         
                glRotated(180.0, 0.0, 0.0, 1.0);    // inverte o triângulo para apontar para baixo
                triangle();
            glPopMatrix();
            // Pé direito
            glPushMatrix();
                glTranslated( 0.3f, -1.0f, 0.0f);
                glScaled(0.3f, 0.3f, 1.0f);
                glRotated(180.0, 0.0, 0.0, 1.0);
                triangle();
            glPopMatrix();

            // Cabeça (círculo verde neon)
            glPushMatrix();
                glColor3f(0.05f, 0.05f, 0.05f);     
                glScaled(0.35f, 0.35f, 1.0f);
                glTranslated(0.0, 3.3f, 0.0);        // sobe acima do corpo
                circle(1.0);
            glPopMatrix();

            // Olho (círculo branco pequeno)
            glPushMatrix();
                glColor3f(1.00f, 1.00f, 1.00f);      // branco
                glScaled(0.08f, 0.08f, 1.0f);
                // desloca relativamente ao sistema da cabeça:
                // fator de escala combinado -> 0.3 (da cabeça) * 1 (do eyeball) = 0.3
                // para mover  e.g. +0.6 no sistema final → +0.6/0.3 = +2.0 no push local
                glTranslated(2.0f, 0.9f + 3.4f/0.3f, 0.0f); 
                circle(1.0);
            glPopMatrix();

            // Bico (triângulo amarelo apontando para a direita)
            glPushMatrix();
                glColor3f(1.00f, 0.65f, 0.00f);      // laranja
                glTranslated(0.35f, 1.1f, 0.0f);     // corrigido: mais próximo da cabeça
                glScaled(0.2f, 0.2f, 1.0f);
                glRotated(-90.0, 0.0, 0.0, 1.0);     // gira para apontar à direita
                triangle();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
    
}
void windMillWing(){
    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0.5, -0.1, 0);
    glVertex3f(1.5, 0, 0);
    glVertex3f(0.5, 0.1, 0);
    glEnd();
};

void windMill(){
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslated(0, 1.5, 0);
    glScaled(0.05, 1.5, 1);
    square();
    glPopMatrix();
    
	
    //wings
    glColor3f(1, 0.5, 0.5);
    glPushMatrix();
    glTranslated(0, 3, 0);
	glRotated(frameNumber * (180.0/46), 0, 0, 1);
	glColor3f(0.4f, 0.4f, 0.8f);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
        glRotated(120*i, 0, 0, 1);
        windMillWing();
        glPopMatrix();
	}
    glPopMatrix();
}
void drawWindMills(){
    glPushMatrix();
    glTranslated(0, 1.3, 0);
    glScaled(1.2,1.2,1);
    windMill();
    glPopMatrix();

    glPushMatrix();
    glTranslated(mounts_coords.m1_x,0,0);
    glScaled(0.8, 0.8, 1);
    windMill();
    glPopMatrix();

    glPushMatrix();
    glTranslated(mounts_coords.m3_x, mounts_coords.y + 6,0);
    glScaled(0.7, 0.7, 1);
    windMill();
    glPopMatrix();
};
void drawStreet(){
    glColor3f(0.64, 0.64, 0.64);
    glPushMatrix();
    glTranslated(0, -window_size/130, 0);
    glScaled((window_size/100)+5, 1.4, 1);
    square();
    glPopMatrix();

    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslated(0, -window_size/130, 0);
    glScaled((window_size/100)+5, 0.175, 1);
    square();
    glPopMatrix();
    
}
void wheel(){
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glScaled(0.95, 0.95, 1);
    circle(1.0);
    glPopMatrix();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glScaled(0.4, 0.4, 1);
    circle(1.0);
    glPopMatrix();
    
    //animation
    if(previous_posicao_carro == posicao_carro){
        glRotatef(-frameNumber*0,0,0,1);
    }
    if(posicao_carro > 0 ){
        glRotatef(-frameNumber*5,0,0,1);
    }else if(posicao_carro < -1){
        glRotatef(frameNumber*5,0,0,1);
    }
	

    glColor3f(0, 0, 0);
    glPushMatrix();
    glBegin(GL_LINES);
        for(int i =0; i < 12; i++){
            float angle = ((2*PI)/12)*i;
            glVertex3f(0,0,0);
            glVertex3f(cos(angle), sin(angle), 0);
        }
    glEnd();
    glPopMatrix();
}
void car(){
    glPushMatrix();
    glTranslatef(-1.5f, -0.1f, 0);
    glScalef(0.8f, 0.8f, 1);
    wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, -0.1f, 0);
    glScalef(0.8f, 0.8f, 1);
    wheel();
    glPopMatrix();

    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0, 0.7f, 0);
    glScalef(3, 0.8f, 1);
    square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 2.0, 0);
    glScalef(1.5, 0.8, 1);
    square();
    glPopMatrix();

    
}
void drawCar(){
    glPushMatrix();
    glTranslated(0, -window_size/150, 0);
    car();
    glPopMatrix();
}

void drawScenario(){
    //icebergs
    icebergs();
    //sea
    drawSea();
    //ice sheet
    drawIceSheet();
}

/*TODO
1. Movimento do penguim na horizontal- usar carro
2. Filhote do Penguim
3. Peixe
4. Passaro
5. Dar movimento aleaorio pros peixes
6. Dar movimento de parabola pro passaro
*/ 
void display() {

    // Limpa a janela, colocando na tela a cor definida pela função glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    drawScenario();

    drawPenguim();

    /*
    drawWindMills();
    drawStreet();
    
    glPushMatrix();
    //glRotated(-frameNumber*0.7,0,0,1);
    drawSun();
    glPopMatrix();
    
    glPushMatrix();
    //glTranslated(-3 + 13*(frameNumber % 300) / 300.0, 0, 0);
    
    glTranslated(posicao_carro, 0, 0);
    drawCar();
    glPopMatrix();

    previous_posicao_carro = posicao_carro;
	
    

    if(frameNumber%100 == 0){
        keep = true;
        glPushMatrix();
        glTranslated(4,-window_size/100, 0);
        circle(1.0);
        glPopMatrix();
        cout << "Drawing circle at frame: framenumber : " << frameNumber << endl;
    }

    */

    glutSwapBuffers();
    
    // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
    //glFlush();
}

void doFrame(int v) {
    frameNumber++;
    glutPostRedisplay();
    glutTimerFunc(30,doFrame,0);
}

void keyboard(unsigned char key, int x, int y)
{
    double dx = 0.5; // Step size for car movement

    if(posicao_carro == window_size/100){
        posicao_carro = -window_size/100;
    }else if(posicao_carro < -window_size/100){
        posicao_carro = -window_size/100;
    }else{
        switch (key) {
            case 'a': case 'A': // Move backward
                posicao_carro -= dx;
                break;
            case 'd': case 'D': // Move forward
                posicao_carro += dx;
                break;
        }
    }
    display(); // Request a redraw
}

int main(int argc, char** argv)
{

 //Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas.
 //É possível passar argumentos para a função glutInit provenientes da linha de execução, tais como informações sobre a geometria da tela
  glutInit(&argc, argv);

  //Informa à biblioteca GLUT o modo do display a ser utilizado quando a janela gráfica for criada.
  // O flag GLUT_SINGLE força o uso de uma janela com buffer simples, significando que todos os desenhos serão feitos diretamente nesta janela.
  // O flag GLUT_RGB determina que o modelo de cor utilizado será o modelo RGB.
  //glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);


   glutInitDisplayMode(GLUT_DOUBLE);
   
   
  //Define o tamanho inicial da janela, 256x256 pixels, e a posição inicial do seu canto superior esquerdo na tela, (x, y)=(100, 100).
  glutInitWindowSize (window_size, window_size);
  glutInitWindowPosition (200, 200);

  // Cria uma janela e define seu título
  glutCreateWindow ("Paisagem");

  //Nesta função é definido o estado inicial do OpenGL. Ajustes podem ser feitos para o usuário nessa função.
  init();

  // Define display() como a função de desenho (display callback) para a janela corrente.
  // Quando GLUT determina que esta janela deve ser redesenhada, a função de desenho é chamada.
  glutDisplayFunc(display);
  
  glutKeyboardFunc(keyboard);

  glutTimerFunc(200,doFrame,0); 


  //Inicia o loop de processamento de desenhos com GLUT.
  // Esta rotina deve ser chamada pelo menos uma vez em um programa que utilize a biblioteca GLUT.
  glutMainLoop();

  return 0;

}

