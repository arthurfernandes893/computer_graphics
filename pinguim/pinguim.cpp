#define GL_SILENCE_DEPRECATION
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

void init(void);
void display(void);

/*=================UTILS===============*/
float PI = 3.14;
int max_height = 1000;
bool front = true;
int frameNumber = 0;
double posicao_penguim = 0;
double posicao_penguim_dir = 0;
double posicao_penguim_esq = 0;
double previous_posicao_penguim = 0;

double BIRD_INIT_VERTICAL = max_height/100 -3;
double BIRD_INIT_HORIZONTAL = -4;
double BIRD_MOVEMENT;
double SEA_MAX_RIGHT = max_height/100;
double SEA_MAX_LEFT = SEA_MAX_RIGHT - 4;

double gameTimeRemaining = 5*60;
double sessionTimeRemainingForWin = 0;
bool keep = true;

struct mounts_coords{
    double m1_x = -max_height/100 + 4;
    double m2_x = -max_height/100 +10;
    double m3_x = -max_height/100 +17.5;
    double y = -max_height/130;
} mounts_coords;

std::string formatTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    char buffer[6];
    return std::string(buffer);
}

void updateGameTime() {
    static int lastFrame = 0;

    // Check if a second has passed based on frame count
    if (frameNumber - lastFrame >= 30) { // Assuming 30 FPS
        if (gameTimeRemaining > 0) {
            gameTimeRemaining--; // Decrease game time by 1 second
        }
        lastFrame = frameNumber; // Update the last frame count
    }
}
/*===================PRIMITVAS=================== 
Utilizadas para facilitar a construcao de estruturas mais complexas
*/
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


/*===================BACKGROUND===================
Definicao das funcoes que desenham o cenario*/
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
        glTranslated(-max_height/200, -max_height/130, 0);
        glScaled(6, 3, 1);
        square();
    glPopMatrix();
}

void drawSea(){
    glColor3f(0.00f, 0.50f, 0.70f);
    glPushMatrix();
        glTranslated(max_height/200, -max_height/130, 0);
        glScaled(6, 3, 1);
        square();
    glPopMatrix();
}

void drawScenario(){
    icebergs();
    drawSea();
    drawIceSheet();
}


/*===================PERSONAGENS===================
Definicao das funcoes que desenham os personagens*/
void drawPenguim(bool isBaby) {
    glPushMatrix();
        glTranslated(-3, -max_height/130 + 3, 0);
        glPushMatrix();
            glPushMatrix();
                glColor3f(0.05f, 0.05f, 0.05f);
                glScaled(0.5f, 1.0f, 1.0f);
                circle(1.0);
            glPopMatrix();

            glPushMatrix();
                glColor3f(1.00f, 1.00f, 1.00f);
                glScaled(0.3f, 0.6f, 1.0f);
                glTranslated(0.0, 1.0f, 0.0);
                circle(1.0);
            glPopMatrix();

            glColor3f(0.65f, 0.10f, 0.10f);
            glPushMatrix();
                glTranslated(-0.3f, -1.0f, 0.0f);
                glScaled(0.3f, 0.3f, 1.0f);
                glRotated(180.0, 0.0, 0.0, 1.0);
                triangle();
            glPopMatrix();
            glPushMatrix();
                glTranslated(0.3f, -1.0f, 0.0f);
                glScaled(0.3f, 0.3f, 1.0f);
                glRotated(180.0, 0.0, 0.0, 1.0);
                triangle();
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.05f, 0.05f, 0.05f);
                glScaled(0.35f, 0.35f, 1.0f);
                glTranslated(0.0, 3.3f, 0.0);
                circle(1.0);
            glPopMatrix();
            
            /*Lógica aplicada para definir em qual direcao desenhar o rosto do penguim
            Se front true, desenhar para a direita, senao, esquerda
            */

            if ((!front) && (!isBaby)) {
                glPushMatrix();
                    glPushMatrix();
                        glColor3f(1.00f, 1.00f, 1.00f);
                        glScaled(0.08f, 0.08f, 1.0f);
                        glTranslated(-1.0f, 1.0f + 3.4f / 0.3f, 0.0f);
                       
                        circle(1.0);
                    glPopMatrix();

                    glPushMatrix();
                        glColor3f(1.00f, 0.65f, 0.00f);
                        glTranslated(-0.35f, 1.1f, 0.0f);
                        glScaled(-0.2f, 0.2f, 1.0f);
                        triangle();
                    glPopMatrix();
                glPopMatrix();
            } else {
                glPushMatrix();
                    glColor3f(1.00f, 1.00f, 1.00f);
                    glScaled(0.08f, 0.08f, 1.0f);
                    glTranslated(1.0f, 1.0f + 3.4f / 0.3f, 0.0f);
                    circle(1.0);
                glPopMatrix();

                glPushMatrix();
                    glColor3f(1.00f, 0.65f, 0.00f);
                    glTranslated(0.35f, 1.1f, 0.0f);
                    glScaled(0.2f, 0.2f, 1.0f);
                    triangle();
                glPopMatrix();
            }
        glPopMatrix();
    glPopMatrix();
}

//atualizacao do movimento do penguim a partir da global posicao_penguim
void movePenguim(){
    //movement
    glPushMatrix();   
        glTranslated(posicao_penguim, 0, 0);     
        drawPenguim(false);
    glPopMatrix();
}

void drawBaby(){
    glPushMatrix();
        glTranslated(-max_height/260 - 3, -max_height/260 + 3, 0);
        glScaled(0.8,0.8,1);
        drawPenguim(true);
    glPopMatrix();

}


/*===================FISH SECTION===================*/
const float SEA_LEFT   = 2.0f;
const float SEA_RIGHT  =  10.0f;
const float SEA_BOTTOM =  -10.0f;
const float SEA_TOP    =   -4.5f; 

// Número de peixes
const int   NUM_FISHES = 6;

struct Fish {
    float x, y;          
    float speed;         
    bool  isRight;       

    Fish(): x(0), y(0), speed(0), isRight(true) {}
};

// Vetor global de peixes
std::vector<Fish> fishes;

// Inicializa vetor com os peixes
void initializeFishes() {
    fishes.clear();
    srand((unsigned)time(nullptr));
    for (int i = 0; i < NUM_FISHES; ++i) {
        Fish f;

        f.x = SEA_LEFT + static_cast<float>(rand()) / RAND_MAX * (SEA_RIGHT - SEA_LEFT);
        f.y = SEA_BOTTOM + static_cast<float>(rand()) / RAND_MAX * (SEA_TOP - SEA_BOTTOM);

        //Velocidade definida como 0.005 + 15% de um valor aleatorio normalizado
        f.speed = 0.005f + static_cast<float>(rand()) / RAND_MAX * 0.15f;
        f.isRight = (rand() % 2 == 0); //probabilidade de 50% de ser criado pra direita ou esquerda
        fishes.push_back(f);
    }
}

void drawFishBody(double radiusX, double radiusY)
{
  glBegin(GL_POLYGON);
  for (int i = 0; i < 32; i++){
    double ellipse_angle = (2 * M_PI / 32) * i;
    glVertex3f(radiusX * cos(ellipse_angle), radiusY * sin(ellipse_angle), 0);
  }
  glEnd();
}

// Atualiza posição de cada peixe, invertendo direção ao bater na borda
void updateFishes() {
    for (auto &f : fishes) {
        if (f.isRight) {
            f.x += f.speed;
            if (f.x > SEA_RIGHT) {
                f.x = SEA_RIGHT;
                f.isRight = false;
            }
        } else {
            f.x -= f.speed;
            if (f.x < SEA_LEFT) {
                f.x = SEA_LEFT;
                f.isRight = true;
            }
        }
    }
}

void drawFish() {
  // cauda
  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-2, 0, 1);
    glScalef(1, 0.5, 1);
    glRotatef(270, 0, 0, 1);
    triangle();
  glPopMatrix();

  // corpo
  glPushMatrix();
    glColor3f(0, 0, 0);
    glScalef(1, 1, 1);
    glTranslatef(0, 0, 0);
    drawFishBody(1, 0.5);
  glPopMatrix();
}


// Função de desenho dos peixes do array
void drawFishes() {
    for (const auto &f : fishes) {
        glPushMatrix();
          glTranslatef(f.x, f.y, 0.0f);
          if (!f.isRight) {
              glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
          }
          glScalef(0.5f, 0.5f, 1.0f);
          drawFish(); 
        glPopMatrix();
    }
}


/*===================PASSARO===================
Implementação do pássaro*/

void drawBird(){
    glPushMatrix();
        glColor3f(0.9f, 0.50f, 0.70f);
        glTranslated(BIRD_INIT_HORIZONTAL,BIRD_INIT_VERTICAL,0);
        glPushMatrix();
            glTranslated(-0.75, 0.75, 0);
            glRotated(315, 0, 0, 1);
            glScaled(1, 0.1, 1);
            square();
        glPopMatrix();

        glPushMatrix();
            glTranslated(0.75, 0.75, 0);
            glRotated(45, 0, 0, 1);
            glScaled(1, 0.1, 1);
            square();
        glPopMatrix();
    glPopMatrix();
   
}

//movimento do passaro em formato de parabola com curvatura para cima
void moveBird() {
    static bool movingForward = true; // Direction of the bird's movement
    double x, y;

    glPushMatrix();
        if (movingForward) {
            BIRD_MOVEMENT += 0.1; // Increment movement
            x = BIRD_INIT_HORIZONTAL + BIRD_MOVEMENT;
        } else {
            BIRD_MOVEMENT -= 0.1; // Decrement movement
            x = BIRD_INIT_HORIZONTAL + BIRD_MOVEMENT;
        }

        // Parabolic trajectory equation
        y = BIRD_INIT_VERTICAL - ((x - BIRD_INIT_HORIZONTAL) * (x - BIRD_INIT_HORIZONTAL)) / 10;

        // Ensure the bird stays within the defined limits
        if (x > SEA_MAX_RIGHT) {
            x = SEA_MAX_RIGHT;
            movingForward = false;
        } 
        

        // Check if the bird reaches the maximum height or the starting point
        if (y <= -max_height / 100 && movingForward) {
            movingForward = false; // Start moving backward
        } else if (x <= BIRD_INIT_HORIZONTAL && !movingForward) {
            movingForward = true; 
            BIRD_MOVEMENT = 0; 
          
        }

            glTranslated(x / 10 - 1, y / 10 - 1, 0);
            drawBird();
    
    glPopMatrix();

}

/*TODO
1. OK - Movimento do penguim na horizontal- usar carro
2. OK - Filhote do Penguim
3. OK - Peixe
4. OK - Passaro
5. OK - Dar movimento aleaorio pros peixes
6. Dar movimento de parabola pro passaro
7. Inserir tempo de jogo
8. Implementar logica de coleta dos peixess
*/ 

/*===================OpenGL Functions===================*/
void init(void)
{
    glClearColor(0.68f, 0.85f, 0.9f, 1.0f); //morning

    // define o sistema de visualização - tipo de projeção
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);

    initializeFishes();
}


void display() {

    // Limpa a janela, colocando na tela a cor definida pela função glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    drawScenario();
    drawBaby();
    drawFishes();
    movePenguim();

    moveBird();


    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-max_height/100 + 1.0f, max_height/100 - 2.0f);
    std::string pinguinLifeStr = "TEMPO DE JOGO: " + formatTime(gameTimeRemaining);
    for (char c : pinguinLifeStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glutSwapBuffers();
    
    // Libera o buffer de comando de desenho para fazer o desenho acontecer o mais rápido possível.
    glFlush();
}

void doFrame(int v) {
    frameNumber++;
    BIRD_MOVEMENT++;
    updateFishes();
    glutPostRedisplay();
    glutTimerFunc(30,doFrame,0);
}

void keyboard(unsigned char key, int x, int y)
{
    double dx = 0.5; // Step size for car movement

    if(posicao_penguim == max_height/100){
        posicao_penguim = -max_height/100;
    }else if(posicao_penguim < -max_height/100){
        posicao_penguim = -max_height/100;
    }else{
        switch (key) {
            case 'a': case 'A': // Move backward
                front = false;
                posicao_penguim -= dx;
                break;
            case 'd': case 'D': // Move forward
                front = true;
                posicao_penguim += dx;
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
  glutInitWindowSize (max_height, max_height);
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

