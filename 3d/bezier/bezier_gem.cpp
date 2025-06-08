#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "bezier.hpp"

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// --- Estruturas e Constantes do Código Original ---

struct XYZ
{
    float x;
    float y;
    float z;
};

// Operador de subtração para vetores (necessário para cálculo de normais)
XYZ operator-(const XYZ& a, const XYZ& b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

// Definição da grade de pontos de controle
#define NI 18
#define NJ 6
XYZ inp[NI + 1][NJ + 1];

// Resolução da superfície final (malha de vértices)
#define RESOLUTIONI (3 * NI)
#define RESOLUTIONJ (3 * NJ)
XYZ outp[RESOLUTIONI][RESOLUTIONJ];
XYZ normals[RESOLUTIONI][RESOLUTIONJ]; // Array para armazenar as normais

// --- Variáveis Globais para Interação ---
int lastMouseX, lastMouseY;
float rotateX = 20.0f, rotateY = -30.0f;
bool isDragging = false;

// --- Funções do Código Original (com pequenas adaptações) ---

// Calcula o polinômio de Bernstein (função de mistura de Bézier)
double BezierBlend(int k, double mu, int n)
{
    int nn, kn, nkn;
    double blend = 1;

    nn = n;
    kn = k;
    nkn = n - k;

    while (nn >= 1)
    {
        blend *= nn;
        nn--;
        if (kn > 1)
        {
            blend /= (double)kn;
            kn--;
        }
        if (nkn > 1)
        {
            blend /= (double)nkn;
            nkn--;
        }
    }
    if (k > 0)
        blend *= pow(mu, (double)k);
    if (n - k > 0)
        blend *= pow(1 - mu, (double)(n - k));

    return (blend);
}

// Gera os pontos de controle para a superfície
void generateControlPoints()
{
    float nMax = 2.0f;
    float nMin = -2.0f;
    for (int i = 0; i <= NI; i++)
    {
        for (int j = 0; j <= NJ; j++)
        {
            inp[i][j].x = i;
            inp[i][j].y = j;
            // Gera um valor Z aleatório para dar a forma ondulada
            inp[i][j].z = nMin + (float)rand() / RAND_MAX * (nMax - nMin);
        }
    }
}

// Calcula os vértices da superfície de Bézier a partir dos pontos de controle
void generateSurface()
{
    double mui, muj, bi, bj;
    for (int i = 0; i < RESOLUTIONI; i++)
    {
        mui = i / (double)(RESOLUTIONI - 1);
        for (int j = 0; j < RESOLUTIONJ; j++)
        {
            muj = j / (double)(RESOLUTIONJ - 1);
            outp[i][j] = {0, 0, 0}; // Reseta o ponto
            for (int ki = 0; ki <= NI; ki++)
            {
                bi = BezierBlend(ki, mui, NI);
                for (int kj = 0; kj <= NJ; kj++)
                {
                    bj = BezierBlend(kj, muj, NJ);
                    outp[i][j].x += (inp[ki][kj].x * bi * bj);
                    outp[i][j].y += (inp[ki][kj].y * bi * bj);
                    outp[i][j].z += (inp[ki][kj].z * bi * bj);
                }
            }
        }
    }
}

// --- Novas Funções para Renderização com OpenGL ---

// Calcula o produto vetorial de dois vetores
XYZ crossProduct(const XYZ& v1, const XYZ& v2) {
    XYZ result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

// Normaliza um vetor
void normalize(XYZ& v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length > 0.0f) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
}

// Calcula as normais para cada vértice da superfície para a iluminação
void calculateNormals() {
    for (int i = 0; i < RESOLUTIONI - 1; i++) {
        for (int j = 0; j < RESOLUTIONJ - 1; j++) {
            XYZ v1 = outp[i + 1][j] - outp[i][j];
            XYZ v2 = outp[i][j + 1] - outp[i][j];
            XYZ normal = crossProduct(v1, v2);
            normalize(normal);
            normals[i][j] = normal;
        }
    }
}

// Função de inicialização do OpenGL
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo preto
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    glEnable(GL_LIGHTING);   // Habilita iluminação
    glEnable(GL_LIGHT0);     // Habilita a luz 0

    // Configura a luz
    GLfloat light_pos[] = {0.0f, 0.0f, 50.0f, 1.0f}; // Posição da luz
    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};   // Luz ambiente
    GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};   // Luz difusa
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    glEnable(GL_NORMALIZE); // Normaliza as normais automaticamente
    glShadeModel(GL_SMOOTH); // Sombreamento suave

    // Gera a geometria da superfície
    srand(time(NULL));
    generateControlPoints();
    generateSurface();
    calculateNormals();
}

// Função para desenhar uma única superfície
void drawSurface(const GLfloat* color) {
    // Define o material da superfície
    GLfloat specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);

    // Desenha a superfície usando tiras de quads
    for (int i = 0; i < RESOLUTIONI - 1; ++i) {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j < RESOLUTIONJ; ++j) {
            // Vértice e normal para a linha atual
            glNormal3f(normals[i][j].x, normals[i][j].y, normals[i][j].z);
            glVertex3f(outp[i][j].x, outp[i][j].y, outp[i][j].z);
            // Vértice e normal para a próxima linha
            glNormal3f(normals[i+1][j].x, normals[i+1][j].y, normals[i+1][j].z);
            glVertex3f(outp[i+1][j].x, outp[i+1][j].y, outp[i+1][j].z);
        }
        glEnd();
    }
}


// Função de exibição (Display Callback)
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,20,6,0,0,0,0,0,1);

    // Configura a câmera
    // Translada o centro da cena para a origem e afasta
    glTranslatef(-NI / 2.0f, -NJ / 2.0f, -20.0f);
    


    // --- Desenha as três superfícies com deslocamentos ---

    // Superfície Vermelha (topo)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 8.0);
    drawSurface(red);
    glPopMatrix();

    // Superfície Verde (meio)
    glPushMatrix();
    drawSurface(green);
    glPopMatrix();
    
    // Superfície Azul (baixo)
    glPushMatrix();
    glTranslatef(0.0, 0.0, -8.0);
    drawSurface(blue);
    glPopMatrix();

    glutSwapBuffers();
}

// Função de redimensionamento da janela (Reshape Callback)
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 100.0);
}

// Funções de callback do mouse para interatividade
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isDragging = false;
        }
    }
}

void motion(int x, int y) {
    if (isDragging) {
        rotateY += (x - lastMouseX);
        rotateX += (y - lastMouseY);
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay(); // Redesenha a cena
    }
}

// Função Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Superficie de Bezier - OpenGL");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}