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

const GLuint total_obj = 9;
std::vector<Obj> obj;
Cam cam(vec3(0, 0, 0));

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
    // Parede esquerda
    obj[3].id = obj[0].id + 3;
    obj[3].pos = vec3(-3.0, 0.5, -7.05);      // Posição
    drawCube(obj[3].id, 0.05, 1.0, 3.0, 3);   // Tamanho
    // Parede frente/direita
    obj[4].id = obj[0].id + 4;
    obj[4].pos = vec3(0.6, 0.5, -4.10);       // Posição
    drawCube(obj[4].id, 2.40, 1.0, 0.05, 4);  // Tamanho
    // Parede frente/esquerda
    obj[5].id = obj[0].id + 5;
    obj[5].pos = vec3(-2.9, 0.5, -4.10);      // Posição
    drawCube(obj[5].id, -0.14, 1.0, 0.05, 5); // Tamanho
    // Parede frente/cima
    obj[6].id = obj[0].id + 6;
    obj[6].pos = vec3(-0.8, 1.2, -4.10);      // Posição
    drawCube(obj[6].id, -2.0, 0.3, 0.05, 6);  // Tamanho
    // Teto
    obj[7].id = obj[0].id + 7;
    obj[7].pos = vec3(0.0, 1.4, -7.05);       // Posição
    drawCube(obj[7].id, -3.0, 0.05, 3.0, 7);  // Tamanho
    // Piso
    obj[8].id = obj[0].id + 8;
    obj[8].pos = vec3(0.0, -0.5, -7.05);      // Posição
    drawCube(obj[8].id, -3.05, 0.007, 3.0, 8);  // Tamanho
}

int main(void) {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1366, 768, "Sphere", NULL, NULL);

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