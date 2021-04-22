//https://www.programmersought.com/article/1263524392/
//g++ -g -std=c++17  -I./include -L./lib src/main.cpp -o main -lglfw3dll -lfreeglut -lopengl32 -lglu32
#include <C:\temp\include\GL\glut.h>
#include <C:\temp\include\GLFW\glfw3.h>
#include <gl/GLU.h>
#include <iostream>
#include <cstdlib>
#include "primitivas.h"

static float angulo = 0.0;
static float lastMousePos = 0.0;
static bool firstTimeMouse = true;

// Display list
struct Obj {
    GLuint id;
    vec3 pos;
    Obj():id(0), pos(vec3(0.0, 0.0, 0.0)){}
};

const GLuint total_obj = 31;
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
    glLoadIdentity();

    cam.activate();

    glCallList(obj[0].id);


    for(int i = 1; i < total_obj; i++) {
        float x = obj[i].pos.x;
        float y = obj[i].pos.y;
        float z = obj[i].pos.z;

        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(angulo, 1.0, 1.0, 0.0);
        glCallList(obj[i].id);
        glPopMatrix();
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
    drawCube(obj[1].id, 3.0, 1.0, 0.05, 1);   // Tamanho
    // Parede direita
    obj[2].id = obj[0].id + 2;
    obj[2].pos = vec3(3.0, 0.5, -7.05);       // Posição
    drawCube(obj[2].id, 0.05, 1.0, 3.0, 2);   // Tamanho
    // Parede esquerda/frente
    obj[3].id = obj[0].id + 3;
    obj[3].pos = vec3(-3.0, 0.5, -5.25);      // Posição
    drawCube(obj[3].id, 0.05, 1.0, 1.2, 3);   // Tamanho
    // Parede esquerda/cima
    obj[4].id = obj[0].id + 4;
    obj[4].pos = vec3(-3.0, 1.15, -7.05);      // Posição
    drawCube(obj[4].id, 0.05, 0.35, 3.0, 4);   // Tamanho
    // Parede esquerda/baixo
    obj[5].id = obj[0].id + 5;
    obj[5].pos = vec3(-3.0, -0.15, -7.05);     // Posição
    drawCube(obj[5].id, 0.05, 0.35, 3.0, 5);   // Tamanho
    // Parede esquerda/fundo
    obj[6].id = obj[0].id + 6;
    obj[6].pos = vec3(-3.0, 0.5, -8.85);      // Posição
    drawCube(obj[6].id, 0.05, 1.0, 1.2, 6);   // Tamanho
    // Parede frente/direita
    obj[7].id = obj[0].id + 7;
    obj[7].pos = vec3(0.6, 0.5, -4.10);       // Posição
    drawCube(obj[7].id, 2.40, 1.0, 0.05, 7);  // Tamanho
    // Parede frente/esquerda
    obj[8].id = obj[0].id + 8;
    obj[8].pos = vec3(-2.9, 0.5, -4.10);      // Posição
    drawCube(obj[8].id, -0.14, 1.0, 0.05, 8); // Tamanho
    // Parede frente/cima
    obj[9].id = obj[0].id + 9;
    obj[9].pos = vec3(-0.8, 1.2, -4.10);      // Posição
    drawCube(obj[9].id, -2.0, 0.3, 0.05, 9);  // Tamanho
    // Teto
    obj[10].id = obj[0].id + 10;
    obj[10].pos = vec3(0.0, 1.4, -7.05);         // Posição
    drawCube(obj[10].id, -3.0, 0.05, 3.0, 10);   // Tamanho
    // Piso
    obj[11].id = obj[0].id + 11;
    obj[11].pos = vec3(0.0, -0.5, -7.05);        // Posição
    drawCube(obj[11].id, -3.05, 0.007, 3.0, 11); // Tamanho
    
    // Tapete
    obj[12].id = obj[0].id + 12;
    obj[12].pos = vec3(0.0, -0.49, -7.05);       // Posição
    drawCube(obj[12].id, -2.55, 0.007, 2.5, 12); // Tamanho

    // Pé 1 cama
    obj[13].id = obj[0].id + 13;
    obj[13].pos = vec3(1.5, -0.4, -7.05);         // Posição
    drawCube(obj[13].id, -0.03, 0.08, 0.03, 13);  // Tamanho
    // Pé 2 cama
    obj[14].id = obj[0].id + 14;
    obj[14].pos = vec3(1.5, -0.4, -6.55);         // Posição
    drawCube(obj[14].id, -0.03, 0.08, 0.03, 14);  // Tamanho
    // Pé 3 cama
    obj[15].id = obj[0].id + 15;
    obj[15].pos = vec3(2.8, -0.4, -7.05);         // Posição
    drawCube(obj[15].id, -0.03, 0.08, 0.03, 15);  // Tamanho
    // Pé 4 cama
    obj[16].id = obj[0].id + 16;
    obj[16].pos = vec3(2.8, -0.4, -6.55);         // Posição
    drawCube(obj[16].id, -0.03, 0.08, 0.03, 16);  // Tamanho
    // Colchão box
    obj[17].id = obj[0].id + 17;
    obj[17].pos = vec3(2.15, -0.25, -6.8);       // Posição
    drawCube(obj[17].id, -0.7, 0.15, 0.3, 17);   // Tamanho
    // Cabeceira da cama box
    obj[18].id = obj[0].id + 18;
    obj[18].pos = vec3(2.87, -0.1, -6.8);       // Posição
    drawCube(obj[18].id, -0.03, 0.3, 0.3, 18);  // Tamanho

    // Mesa
    obj[19].id = obj[0].id + 19;
    obj[19].pos = vec3(1.0, 0.0, -4.4);          // Posição
    drawCube(obj[19].id, -0.7, 0.005, 0.2, 19);   // Tamanho
    // Perna 1 mesa
    obj[20].id = obj[0].id + 20;
    obj[20].pos = vec3(1.6, -0.27, -4.57);        // Posição
    drawCube(obj[20].id, -0.01, 0.27, 0.01, 20);  // Tamanho
    // Perna 2 mesa
    obj[21].id = obj[0].id + 21;
    obj[21].pos = vec3(1.6, -0.27, -4.23);        // Posição
    drawCube(obj[21].id, -0.01, 0.27, 0.01, 21);  // Tamanho
    // Perna 3 mesa
    obj[22].id = obj[0].id + 22;
    obj[22].pos = vec3(0.39, -0.27, -4.57);        // Posição
    drawCube(obj[22].id, -0.01, 0.27, 0.01, 22);   // Tamanho
    // Perna 4 mesa
    obj[23].id = obj[0].id + 23;
    obj[23].pos = vec3(0.39, -0.27, -4.23);       // Posição
    drawCube(obj[23].id, -0.01, 0.27, 0.01, 23);  // Tamanho

    // Cadeira
    obj[24].id = obj[0].id + 24;
    obj[24].pos = vec3(1.0, -0.2, -4.7);         // Posição
    drawCube(obj[24].id, 0.15, 0.005, 0.15, 24);   // Tamanho
    // Perna 1 cadeira
    obj[25].id = obj[0].id + 25;
    obj[25].pos = vec3(1.12, -0.37, -4.57);        // Posição
    drawCube(obj[25].id, 0.01, 0.17, 0.01, 25);  // Tamanho
    // Perna 2 cadeira
    obj[26].id = obj[0].id + 26;
    obj[26].pos = vec3(1.12, -0.37, -4.83);        // Posição
    drawCube(obj[26].id, 0.01, 0.17, 0.01, 26);  // Tamanho
    // Perna 3 cadeira
    obj[27].id = obj[0].id + 27;
    obj[27].pos = vec3(0.87, -0.37, -4.57);        // Posição
    drawCube(obj[27].id, 0.01, 0.17, 0.01, 27);   // Tamanho
    // Perna 4 cadeira
    obj[28].id = obj[0].id + 28;
    obj[28].pos = vec3(0.87, -0.37, -4.83);       // Posição
    drawCube(obj[28].id, 0.01, 0.17, 0.01, 28);   // Tamanho
    // Encosto cadeira
    obj[29].id = obj[0].id + 29;
    obj[29].pos = vec3(1.0, -0.05, -4.83);         // Posição
    drawCube(obj[29].id, 0.15, 0.15, 0.005, 29);   // Tamanho

    // Livro
    obj[30].id = obj[0].id + 30;
    obj[30].pos = vec3(1.0, 0.02, -4.4);         // Posição
    drawCube(obj[30].id, 0.1, 0.005, 0.1, 30);   // Tamanho
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