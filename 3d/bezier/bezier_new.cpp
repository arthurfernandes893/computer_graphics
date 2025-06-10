#include <GL/glut.h>
#include <cmath>
#include <ctime>

struct XYZ {
    float x, y, z;
};

#define NI 18
#define NJ 6
XYZ inp[NI+1][NJ+1];
#define RESOLUTIONI 3*NI
#define RESOLUTIONJ 3*NJ
XYZ outp[RESOLUTIONI][RESOLUTIONJ];

static GLfloat branco[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat vermelho_amb[] = { 0.8, 0.2, 0.2, 1.0 };
static GLfloat vermelho_dif[] = { 1.0, 0.4, 0.4, 1.0 };
static GLfloat verde_amb[] = { 0.2, 0.8, 0.2, 1.0 };
static GLfloat verde_dif[] = { 0.4, 0.9, 0.4, 1.0 };
static GLfloat azul_amb[] = { 0.2, 0.2, 0.8, 1.0 };
static GLfloat azul_dif[] = { 0.4, 0.4, 0.9, 1.0 };

int frame_num = 0;

double BezierBlend(int k, double mu, int n) {
    int nn, kn, nkn;
    double blend = 1;

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
        blend *= pow(mu, (double)k);
    if (n - k > 0)
        blend *= pow(1 - mu, (double)(n - k));

    return blend;
}

void generateControlPoint()
{
	   int nMax = 2;
	   int nMin = -2;
	   int i,j;
	   srand(time(NULL));
	   for (i=0;i<=NI;i++) {
	      for (j=0;j<=NJ;j++) {
	            inp[i][j].x = i;
	            inp[i][j].y = j;

                inp[i][j].z = 4 * sin(i + frame_num * 0.5);
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

void desenharSuperficie(float setY, GLfloat* corAmb, GLfloat* corDif) {
    glMaterialfv(GL_FRONT, GL_SPECULAR, branco);
    glMaterialfv(GL_FRONT, GL_AMBIENT, corAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, corDif);
    glMaterialf(GL_FRONT, GL_SHININESS, 120);

    for (int i = 0; i < RESOLUTIONI - 1; i++) {
        for (int j = 0; j < RESOLUTIONJ - 1; j++) {
            XYZ A = outp[i][j];
            XYZ B = outp[i+1][j];
            XYZ C = outp[i+1][j+1];
            XYZ D = outp[i][j+1];

            A.y += setY;
            B.y += setY;
            C.y += setY;
            D.y += setY;

            XYZ u = { B.x - A.x, B.y - A.y, B.z - A.z };
            XYZ v = { D.x - A.x, D.y - A.y, D.z - A.z };

            XYZ normal = {
                u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x
            };

            float len = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
            if (len != 0.0f) {
                normal.x /= len;
                normal.y /= len;
                normal.z /= len;
            }

            glBegin(GL_QUADS);
                glNormal3f(normal.x, normal.y, normal.z);
                glVertex3f(A.x, A.y, A.z);
                glVertex3f(B.x, B.y, B.z);
                glVertex3f(C.x, C.y, C.z);
                glVertex3f(D.x, D.y, D.z);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(30, -50, 30, 10, 0, 0, 0, 0, 1);

    generateControlPoint();
    Surface();
    
    desenharSuperficie(-15, azul_amb, azul_dif);
    desenharSuperficie(0, verde_amb, verde_dif);
    desenharSuperficie(15, vermelho_amb, vermelho_dif);

    glutSwapBuffers();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    frame_num++;

    glutPostRedisplay();
    glutTimerFunc(70, timer, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tarefa 6");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}