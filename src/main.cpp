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

const GLuint total_obj = 8;
std::vector<Obj> obj;
Cam cam(vec3(-100, 0, 0));

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    float aspect = (float) w / (float) h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
}

void draw(float dt) {
    float veloc_ang = 60.0 * dt; // 60 graus por segundo
    
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

	angulo += veloc_ang;
	if (angulo >= 360.0)
		angulo = 0.0;
}

float random(float a, float b) {
    float n = (float) rand() / RAND_MAX;
    float t = b - a;
    float r = a + n * t;

    return r;
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

    for(int i = 1; i < total_obj; i++) {
        obj[i].id = obj[0].id + i;
        float x = random(-100, 100);
        float y = random(8, 20);
        float z = random(-450, -20);
        obj[i].pos = vec3(x, 0, z);

        float k = (float) rand() / RAND_MAX;
        if(k <= 0.5) {
            color* cor;
            if(k <= 0.15) {
                cor = &green;
            }
            else {
                cor = &orange;
            }
            drawSphere(obj[i].id, *cor, 5.0, 20.0, 20.0);
        }
        else {
            drawCube(obj[i].id, 5.0);
        }
    }
}

int main(void) {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sphere", NULL, NULL);

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
