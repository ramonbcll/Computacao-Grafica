#include <C:\Users\ramon\Downloads\freeglut\include\GL\glut.h>
#include <stdlib.h>
#include <stdio.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat vertices[27] = {
    0.0,  30.0, 30.0, // 0 
    30.0, 30.0, 30.0, // 1 
    30.0,  0.0, 30.0, // 2 
    0.0,   0.0, 30.0, // 3 
    0.0,  30.0,  0.0, // 4 
    30.0, 30.0,  0.0, // 5 
    30.0,  0.0,  0.0, // 6 
    0.0,   0.0,  0.0, // 7 
    15.0, 45.0, 15.0  // 8
}; 

static GLubyte frenteIndices[]    = {0,3,2,1};
static GLubyte trasIndices[]      = {5,6,7,4};
static GLubyte esquerdaIndices[]  = {4,7,3,0};
static GLubyte direitaIndices[]   = {1,2,6,5};
static GLubyte topoIndices[]      = {4,0,1,5};
static GLubyte fundoIndices[]     = {6,2,3,7};

static GLubyte piramide1[]        = {1,8,0};
static GLubyte piramide2[]        = {1,5,8};
static GLubyte piramide3[]        = {5,4,8};
static GLubyte piramide4[]        = {4,0,8};
    
static int eixoy, eixox;
int largura, altura;

int main(int argc, char** argv) {
    int i;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (256, 256); 
    glutInitWindowPosition (100, 100); 
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    return 0;
}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho (-50, 50, -50, 50, -50 , 50);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 
}

void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    largura=w; 
    altura=h;
}

void display(void) {
    glPushMatrix();
    glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glColor3f (AZUL); /* frente */
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frenteIndices);

    glColor3f (AMARELO); /* esquerda */
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, esquerdaIndices);

    glColor3f (VERMELHO); /* tras */
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, trasIndices);

    glColor3f (VERDE); /* direita */
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, direitaIndices);

    glColor3f (CYAN); // topo 
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topoIndices);

    glColor3f (LARANJA); /* fundo */
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fundoIndices);
    
    glColor3f (AMARELO); // piramide 1
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramide1);
    glColor3f (VERMELHO); // piramide 2 
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramide2);
    glColor3f (VERDE); // piramide 3 
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramide3);
    glColor3f (CYAN); // piramide 4 
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, piramide4);
    
    glDisableClientState (GL_VERTEX_ARRAY);

    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'a':
        printf("%d, %d\n",x,y);
        break;
    case 'y':
        eixoy = (eixoy + 5) % 360;
        glutPostRedisplay();
        break;
    case 'Y':
        eixoy = (eixoy - 5) % 360;
        glutPostRedisplay();
        break;
    case 'x':
        eixox = (eixox + 5) % 360;
        glutPostRedisplay();
        break;
    case 'X':
        eixox = (eixox - 5) % 360;
        glutPostRedisplay();
        break;
    case 'p':
        glLoadIdentity();
        gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
        gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
        glutPostRedisplay();
        break;
    case 'o':
        glLoadIdentity();
        glOrtho (-50, 50, -50, 50, -50 , 50);
        glutPostRedisplay();
        break;
    }
}
