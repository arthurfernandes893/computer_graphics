// TeaPot3D.cpp - Isabel H. Manssour
// Um programa OpenGL que exemplifica a visualiza??o
// de objetos 3D.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;
GLfloat r,g,b;

void DefineIluminacao (void)
{
	GLfloat luzEspecular[4]={r, g, b, 1.0};

	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor"
	//GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 30;
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}

// Fun??o callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela de visualiza??o com a cor
	// de fundo definida previamente

	/*GL_DEPTH_BUFFER BIT define que  o programa atual necessita de um buffer de profundidade, também
chamado de z-buffer, e que ele deve ser inicializado antes de cada redesenho.*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//chama a função que especifica os parâmetros de iluminação
	DefineIluminacao();

	// Troca cor corrente para azul
	//glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha o teapot com a cor corrente (wire-frame)
	//glutWireTeapot(50.0f);

    //glutSolidTeapot(50.0f); 
	/*se bserva que a mesma parece 2D. Isto ocorre porque a versão Solid 
	deve ser usada somente quando se está trabalhando com iluminação.
	*/


// --- INÍCIO DO CÓDIGO PARA A QUESTÃO 6 ---
// O código abaixo substitui o desenho do bule ou do cubo com polígonos.
// Ele desenha um cubo usando uma malha de 12 triângulos.

// Face posterior
glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1); // Normal da face 
    // Triângulo 1
    glVertex3f(50.0, 50.0, 50.0);
    glVertex3f(-50.0, 50.0, 50.0);
    glVertex3f(-50.0, -50.0, 50.0);
    // Triângulo 2
    glVertex3f(50.0, 50.0, 50.0);
    glVertex3f(-50.0, -50.0, 50.0);
    glVertex3f(50.0, -50.0, 50.0);
glEnd();

// Face frontal
glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, -1); // Normal da face 
    // Triângulo 1
    glVertex3f(50.0, 50.0, -50.0);
    glVertex3f(50.0, -50.0, -50.0);
    glVertex3f(-50.0, -50.0, -50.0);
    // Triângulo 2
    glVertex3f(50.0, 50.0, -50.0);
    glVertex3f(-50.0, -50.0, -50.0);
    glVertex3f(-50.0, 50.0, -50.0);
glEnd();

// Face lateral esquerda
glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0); // Normal da face 
    // Triângulo 1
    glVertex3f(-50.0, 50.0, 50.0);
    glVertex3f(-50.0, 50.0, -50.0);
    glVertex3f(-50.0, -50.0, -50.0);
    // Triângulo 2
    glVertex3f(-50.0, 50.0, 50.0);
    glVertex3f(-50.0, -50.0, -50.0);
    glVertex3f(-50.0, -50.0, 50.0);
glEnd();

// Face lateral direita
glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0); // Normal da face 
    // Triângulo 1
    glVertex3f(50.0, 50.0, 50.0);
    glVertex3f(50.0, -50.0, 50.0);
    glVertex3f(50.0, -50.0, -50.0);
    // Triângulo 2
    glVertex3f(50.0, 50.0, 50.0);
    glVertex3f(50.0, -50.0, -50.0);
    glVertex3f(50.0, 50.0, -50.0);
glEnd();

// Face superior
glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0); // Normal da face 
    // Triângulo 1
    glVertex3f(-50.0, 50.0, -50.0);
    glVertex3f(-50.0, 50.0, 50.0);
    glVertex3f(50.0, 50.0, 50.0);
    // Triângulo 2
    glVertex3f(-50.0, 50.0, -50.0);
    glVertex3f(50.0, 50.0, 50.0);
    glVertex3f(50.0, 50.0, -50.0);
glEnd();

// Face inferior
glBegin(GL_TRIANGLES);
    glNormal3f(0, -1, 0); // Normal da face 
    // Triângulo 1
    glVertex3f(-50.0, -50.0, -50.0);
    glVertex3f(50.0, -50.0, -50.0);
    glVertex3f(50.0, -50.0, 50.0);
    // Triângulo 2
    glVertex3f(-50.0, -50.0, -50.0);
    glVertex3f(50.0, -50.0, 50.0);
    glVertex3f(-50.0, -50.0, 50.0);
glEnd();

// --- FIM DO CÓDIGO PARA A QUESTÃO 6 ---
	// Execu??o dos comandos de desenho
	glutSwapBuffers();
}


// Inicializa??o
/* antiga inicializa*/
/*
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualiza??o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicializa a vari?vel que especifica o ?ngulo da proje??o
	// perspectiva
	angle=50;

	// Inicializa as vari?veis usadas para alterar a posi??o do
	// observador virtual
	rotX = 30;
	rotY = 0;
	obsZ = 180;
}
*/

void Inicializa(void)
{
	r=1.0; g=1.0; b=1.0;
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
	// Habilita o modelo de colorização de Gouraud
	
	//glShadeModel(GL_SMOOTH);
	
	glShadeModel(GL_SMOOTH);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=50;
	// Inicializa as variáveis usadas para alterar a posição do
	// observador virtual
	rotX = 30;
	rotY = 0;
	obsZ = 180;
}

// Fun??o usada para especificar a posi??o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	DefineIluminacao();
	// Especifica posi??o do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}


// Fun??o usada para especificar o volume de visualiza??o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje??o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje??o
	glLoadIdentity();

	// Especifica a proje??o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}


// Fun??o callback chamada quando o tamanho da janela ? alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis?o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens?es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre??o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


// Callback para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-in
			if (angle >= 10)
				angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-out
			if (angle <= 130)
				angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


// Fun??o callback chamada para gerenciar eventos de teclas especiais (F1,PgDn,...)
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
		case GLUT_KEY_HOME:	obsZ++;
							break;
		case GLUT_KEY_END:	obsZ--;
							break;
		case 'a': r+=0.05;
		case 'b': g+=0.05;
		case 'c': b+=0.05;
		case 'r': r-=0.05;
		case 'p': g-=0.05;
		case 'z': b-=0.05;
	}
	PosicionaObservador();
	glutPostRedisplay();
}


// Programa Principal
int main()
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de operacao da GLUT
	/* GLUT_DEPTH define que o o programa atual necessita de um buffer de profundidade, também
chamado de z-buffer, e que ele deve ser inicializado antes de cada redesenho.*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 


	// Especifica a posi??o inicial da janela GLUT
    glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);

	// Cria a janela passando como argumento o titulo da mesma
	glutCreateWindow("Desenho de um teapot com ilumina??o");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(Desenha);
	// Registra a funcao callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);
	// Registra a funcao callback para tratamento do redimensionamento da janela
    glutReshapeFunc(AlteraTamanhoJanela);
	// Registra a funcao callback para tratamento do mouse
	glutMouseFunc(GerenciaMouse);

	Inicializa();
	glutMainLoop();
}
