//https://www.programmersought.com/article/1263524392/
//g++ -g -std=c++17  -I./include -L./lib src/main.cpp -o main -lglfw3dll -lfreeglut -lopengl32 -lglu32
#include <C:\temp\include\GL\glut.h>
#include <C:\temp\include\GLFW\glfw3.h>
#include <gl/GLU.h>
#include <iostream>
#include <cstdlib>
#include "primitivas.h"

static float angulo = 45.0;
static float lastMousePos = 0.0;
static bool firstTimeMouse = true;

// Display list
struct Obj {
    GLuint id;
    vec3 pos;
    Obj():id(0), pos(vec3(0.0, 0.0, 0.0)){}
};

const GLuint total_obj = 40;
std::vector<Obj> obj;
Cam cam(vec3(0, 0, -5));

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    float aspect = (float) w / (float) h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
}

void draw(float dt) {   
    float velocidade_ang = 50.f * dt; 
    glLoadIdentity();

    cam.activate();

    glCallList(obj[0].id);


    for(int i = 1; i < total_obj; i++) {
        float x = obj[i].pos.x;
        float y = obj[i].pos.y;
        float z = obj[i].pos.z;

        glPushMatrix();
        glTranslatef(x, y, z);
        if(i == 36 || i == 37 || i == 38)
            glRotatef(angulo, 0.0, 0.0, 1.0);
        glCallList(obj[i].id);
        glPopMatrix();
    }

    angulo += velocidade_ang;

	if (angulo >= 360.0)
	{
		angulo = 0.0;
	}
}

void callbackKeyboard(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Forward
        cam.forward();
    }
    else if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Back
        cam.back();

    }
    else if(key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Left
        cam.left();        
    }
    else if(key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        // Right
        cam.right();        
    }
}

void callbackMouse(GLFWwindow* window, double posX, double posY) {
    float dx;

    if(firstTimeMouse) {
        dx = 0;
        lastMousePos = posX;
        firstTimeMouse = false;
    }
    dx = posX - lastMousePos;
    lastMousePos = posX;
    cam.updateYaw(dx);
    cam.update();
}

void init(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, callbackMouse);
    glfwSetKeyCallback(window, callbackKeyboard);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMaximizeWindow(window);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    for(int i = 0; i < total_obj; i++) {
        Obj p;
        obj.push_back(p);
    }

    obj[0].id = glGenLists(total_obj);
    drawGround(obj[0].id);
    // Parede fundo
    obj[1].id = obj[0].id + 1;
    obj[1].pos = vec3(0.0, 0.5, -10.0);       // Posição
    drawCube(obj[1].id, 3.0, 1.0, 0.05, 1, 0);   // Tamanho
    // Parede direita
    obj[2].id = obj[0].id + 2;
    obj[2].pos = vec3(3.0, 0.5, -7.05);       // Posição
    drawCube(obj[2].id, 0.05, 1.0, 3.0, 2, 0);   // Tamanho
    // Parede esquerda/frente
    obj[3].id = obj[0].id + 3;
    obj[3].pos = vec3(-3.0, 0.5, -5.25);      // Posição
    drawCube(obj[3].id, 0.05, 1.0, 1.2, 3, 0);   // Tamanho
    // Parede esquerda/cima
    obj[4].id = obj[0].id + 4;
    obj[4].pos = vec3(-3.0, 1.15, -7.05);      // Posição
    drawCube(obj[4].id, 0.05, 0.35, 3.0, 4, 0);   // Tamanho
    // Parede esquerda/baixo
    obj[5].id = obj[0].id + 5;
    obj[5].pos = vec3(-3.0, -0.15, -7.05);     // Posição
    drawCube(obj[5].id, 0.05, 0.35, 3.0, 5, 0);   // Tamanho
    // Parede esquerda/fundo
    obj[6].id = obj[0].id + 6;
    obj[6].pos = vec3(-3.0, 0.5, -8.85);      // Posição
    drawCube(obj[6].id, 0.05, 1.0, 1.2, 6, 0);   // Tamanho
    // Parede frente/direita
    obj[7].id = obj[0].id + 7;
    obj[7].pos = vec3(0.6, 0.5, -4.10);       // Posição
    drawCube(obj[7].id, 2.40, 1.0, 0.05, 7, 0);  // Tamanho
    // Parede frente/esquerda
    obj[8].id = obj[0].id + 8;
    obj[8].pos = vec3(-2.9, 0.5, -4.10);      // Posição
    drawCube(obj[8].id, -0.14, 1.0, 0.05, 8, 0); // Tamanho
    // Parede frente/cima
    obj[9].id = obj[0].id + 9;
    obj[9].pos = vec3(-0.8, 1.2, -4.10);      // Posição
    drawCube(obj[9].id, -2.0, 0.3, 0.05, 9, 0);  // Tamanho
    // Teto
    obj[10].id = obj[0].id + 10;
    obj[10].pos = vec3(0.0, 1.4, -7.05);         // Posição
    drawCube(obj[10].id, -3.0, 0.05, 3.0, 10, 0);   // Tamanho
    // Piso
    obj[11].id = obj[0].id + 11;
    obj[11].pos = vec3(0.0, -0.5, -7.05);        // Posição
    drawCube(obj[11].id, -3.05, 0.007, 3.0, 11, 0); // Tamanho
    
    // Tapete
    obj[12].id = obj[0].id + 12;
    obj[12].pos = vec3(0.0, -0.49, -7.05);       // Posição
    drawCube(obj[12].id, 1.0, -0.007, 1.0, 12, 0); // Tamanho

    // Pé 1 cama
    obj[13].id = obj[0].id + 13;
    obj[13].pos = vec3(1.5, -0.4, -7.05);         // Posição
    drawCube(obj[13].id, -0.03, 0.08, 0.03, 13, 0);  // Tamanho
    // Pé 2 cama
    obj[14].id = obj[0].id + 14;
    obj[14].pos = vec3(1.5, -0.4, -6.55);         // Posição
    drawCube(obj[14].id, -0.03, 0.08, 0.03, 14, 0);  // Tamanho
    // Pé 3 cama
    obj[15].id = obj[0].id + 15;
    obj[15].pos = vec3(2.8, -0.4, -7.05);         // Posição
    drawCube(obj[15].id, -0.03, 0.08, 0.03, 15, 0);  // Tamanho
    // Pé 4 cama
    obj[16].id = obj[0].id + 16;
    obj[16].pos = vec3(2.8, -0.4, -6.55);         // Posição
    drawCube(obj[16].id, -0.03, 0.08, 0.03, 16, 0);  // Tamanho
    // Colchão box
    obj[17].id = obj[0].id + 17;
    obj[17].pos = vec3(2.15, -0.25, -6.8);       // Posição
    drawCube(obj[17].id, -0.7, 0.15, 0.3, 17, 0);   // Tamanho
    // Cabeceira da cama box
    obj[18].id = obj[0].id + 18;
    obj[18].pos = vec3(2.87, -0.1, -6.8);       // Posição
    drawCube(obj[18].id, -0.03, 0.3, 0.3, 18, 0);  // Tamanho

    // Mesa
    obj[19].id = obj[0].id + 19;
    obj[19].pos = vec3(1.0, 0.0, -4.4);          // Posição
    drawCube(obj[19].id, -0.7, 0.005, 0.2, 19, 0);   // Tamanho
    // Perna 1 mesa
    obj[20].id = obj[0].id + 20;
    obj[20].pos = vec3(1.6, -0.27, -4.57);        // Posição
    drawCube(obj[20].id, -0.01, 0.27, 0.01, 20, 0);  // Tamanho
    // Perna 2 mesa
    obj[21].id = obj[0].id + 21;
    obj[21].pos = vec3(1.6, -0.27, -4.23);        // Posição
    drawCube(obj[21].id, -0.01, 0.27, 0.01, 21, 0);  // Tamanho
    // Perna 3 mesa
    obj[22].id = obj[0].id + 22;
    obj[22].pos = vec3(0.39, -0.27, -4.57);        // Posição
    drawCube(obj[22].id, -0.01, 0.27, 0.01, 22, 0);   // Tamanho
    // Perna 4 mesa
    obj[23].id = obj[0].id + 23;
    obj[23].pos = vec3(0.39, -0.27, -4.23);       // Posição
    drawCube(obj[23].id, -0.01, 0.27, 0.01, 23, 0);  // Tamanho

    // Cadeira
    obj[24].id = obj[0].id + 24;
    obj[24].pos = vec3(1.0, -0.2, -4.7);         // Posição
    drawCube(obj[24].id, 0.15, 0.005, 0.15, 24, 0);   // Tamanho
    // Perna 1 cadeira
    obj[25].id = obj[0].id + 25;
    obj[25].pos = vec3(1.12, -0.37, -4.57);        // Posição
    drawCube(obj[25].id, 0.01, 0.17, 0.01, 25, 0);  // Tamanho
    // Perna 2 cadeira
    obj[26].id = obj[0].id + 26;
    obj[26].pos = vec3(1.12, -0.37, -4.83);        // Posição
    drawCube(obj[26].id, 0.01, 0.17, 0.01, 26, 0);  // Tamanho
    // Perna 3 cadeira
    obj[27].id = obj[0].id + 27;
    obj[27].pos = vec3(0.87, -0.37, -4.57);        // Posição
    drawCube(obj[27].id, 0.01, 0.17, 0.01, 27, 0);   // Tamanho
    // Perna 4 cadeira
    obj[28].id = obj[0].id + 28;
    obj[28].pos = vec3(0.87, -0.37, -4.83);       // Posição
    drawCube(obj[28].id, 0.01, 0.17, 0.01, 28, 0);   // Tamanho
    // Encosto cadeira
    obj[29].id = obj[0].id + 29;
    obj[29].pos = vec3(1.0, -0.05, -4.83);         // Posição
    drawCube(obj[29].id, 0.15, 0.15, 0.005, 29, 0);   // Tamanho

    // Livro
    obj[30].id = obj[0].id + 30;
    obj[30].pos = vec3(1.0, 0.02, -4.4);         // Posição
    drawCube(obj[30].id, -0.1, -0.005, 0.1, 30, 0);   // Tamanho

    // Guarda-roupas
    obj[31].id = obj[0].id + 31;
    obj[31].pos = vec3(0.5, 0.2, -9.6);           // Posição
    drawCube(obj[31].id, 1.6, 0.7, -0.3, 31, 0);   // Tamanho

    //Criado mudo
    obj[32].id = obj[0].id + 32;
    obj[32].pos = vec3(2.5, -0.3, -4.4);           // Posição
    drawCube(obj[32].id, 0.25, 0.23, 0.2, 32, 0);  // Tamanho

    //Base ventilador
    obj[33].id = obj[0].id + 33;
    obj[33].pos = vec3(2.5, -0.05, -4.4);           // Posição
    drawCube(obj[33].id, 0.08, 0.01, 0.08, 33, 0);  // Tamanho
    //Tronco ventilador
    obj[34].id = obj[0].id + 34;
    obj[34].pos = vec3(2.5, -0.03, -4.35);          // Posição
    drawCube(obj[34].id, 0.02, 0.08, 0.02, 34, 0);  // Tamanho
    //Motor ventilador
    obj[35].id = obj[0].id + 35;
    obj[35].pos = vec3(2.5, 0.05, -4.37);           // Posição
    drawCube(obj[35].id, 0.05, 0.04, 0.05, 35, 0);  // Tamanho
    obj[36].id = obj[0].id + 36;
    obj[36].pos = vec3(2.5, 0.05, -4.39);           // Posição
    drawCube(obj[36].id, 0.01, 0.01, 0.05, 35, 0);  // Tamanho
    // Hélice 1
    obj[37].id = obj[0].id + 37;
    obj[37].pos = vec3(2.5, 0.05, -4.45);           // Posição
    drawCube(obj[37].id, 0.06, 0.01, 0.01, 35, 0);  // Tamanho
    // Hélice 2
    obj[38].id = obj[0].id + 38;
    obj[38].pos = vec3(2.5, 0.05, -4.45);           // Posição
    drawCube(obj[38].id, 0.01, 0.06, 0.01, 35, 1);  // Tamanho

    // Bola infantil
    obj[39].id = obj[0].id + 39;
    obj[39].pos = vec3(2.5, -0.2, -9.45);             // Posição
    drawSphere(obj[39].id, white_i, 0.27, 20.0, 20.0);  // Tamanho
}

int main(void) {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1366, 768, "Bedroom", NULL, NULL);

    glfwMakeContextCurrent(window);

    // Início
    init(window);

    float value = 0.0;
    float lastTime = 0.0;

    while(!glfwWindowShouldClose(window)) {
        float currentTime = (float) glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        resize(width, height);
        draw(dt);

        glfwSwapBuffers(window);
    }

    glDeleteLists(obj[0].id, total_obj);
    glfwTerminate();
    return 0;
}