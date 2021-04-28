//g++ -g -std=c++17  -I./include -L./lib src/*.cpp -o main -lglfw3dll -lfreeglut -lopengl32 -lglu32
#include <C:\temp\include\GL\glut.h>
#include <C:\temp\include\GLFW\glfw3.h>
#include <gl/GLU.h>
#include <iostream>
#include <cstdlib>
#include "primitivas.h"
#include "stb_image.h"

static float lastMousePos = 0.0;
static bool firstTimeMouse = true;
GLuint texID[16];
float r = 0.0;
static int moveDoor = 0;
static int moveWindow = 0;
static int luzA = 0;
static int luzG = 1;

struct Obj {
    GLuint id;
    vec3 pos;
    Obj():id(0), pos(vec3(0.0, 0.0, 0.0)){}
};

const GLuint total_obj = 52;
std::vector<Obj> obj;
Cam cam(vec3(0, 0, -5)); // Posição inicial da câmera
//vec3 lightPos(0.7, 0.27, -4.4);

void loadTexture(GLuint tex_id, std::string filePath) {
	unsigned char* imgData;
	int largura, altura, canais;

	//stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load(filePath.c_str(), &largura, &altura, &canais, 4);
	
    if(imgData) {
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		stbi_image_free(imgData);
	}
	else {
		std::cout << "ERRO:: Nao foi possivel carregar a textura!" << filePath.c_str() << std::endl;
	}	
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    float aspect = (float) w / (float) h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 500);

    glMatrixMode(GL_MODELVIEW);
}

void draw() {
    glLoadIdentity();

    cam.activate();

    glCallList(obj[0].id);

    for(int i = 1; i < total_obj; i++) {
        float x = obj[i].pos.x;
        float y = obj[i].pos.y;
        float z = obj[i].pos.z;

        glPushMatrix();
        glTranslatef(x, y, z);
        if(i == 38 || i == 39 || i == 40)
            glRotatef(r, 0.0, 0.0, 1.0);
        if(i == 44 || i == 45) {
            if(moveWindow == 1) {
                if(i == 44) {
                    glTranslatef(-0.3, 0.0, 0.3);
                }
                if(i == 45) {
                    glTranslatef(-0.3, 0.0, -0.3);
                }
                glRotatef(90, 0.0, 1.0, 0.0);
            }
        }
        if(i == 43) {
            if(moveDoor == 1) {
                glTranslatef(-0.5, 0.0, 0.5);
                glRotatef(-90, 0.0, 1.0, 0.0);
            }
        }
        glCallList(obj[i].id);
        glPopMatrix();
    }

    float position_light[] = {0.7f, 0.27f, -4.4f, 1.f};
	float direction_light[] = {0.0f, -1.0f, 0.0f, 1.f};
	glLightfv(GL_LIGHT0, GL_POSITION, position_light);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction_light);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);

    if(luzA == 1) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
    if(luzG == 1) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

    r += 0.5;
	if (r >= 360.0) {
		r = 0.0;
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
    else if(key == GLFW_KEY_P && (action == GLFW_PRESS)) {
		moveDoor = (moveDoor + 1) % 2;
	}
	else if(key == GLFW_KEY_J && (action == GLFW_PRESS)) {
		moveWindow = (moveWindow + 1) % 2;
	}
    else if(key == GLFW_KEY_L && (action == GLFW_PRESS)) {
		luzA = (luzA + 1) % 2;
	}
    else if(key == GLFW_KEY_G && (action == GLFW_PRESS)) {
		luzG = (luzG + 1) % 2;
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	float globalAmb[] = { 0.2f, 0.2f, 0.2f, 1.f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

    float light0[3][4] = {
        {0.5f, 0.5f, 0.5f, 1.f},    // Ambiente
        {0.2f, 0.2f, 0.2f, 1.f},    // Difusa
        {1.f, 1.f, 1.f, 1.f},       // Especular
    };
    glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Troca a cor da superfície
    glGenTextures(16, texID);
    loadTexture(texID[0], "texturas/wall.jpg");
    loadTexture(texID[1], "texturas/wood.jfif");
    loadTexture(texID[2], "texturas/tapete.jpg");
    loadTexture(texID[3], "texturas/cor.jpg");
    loadTexture(texID[4], "texturas/capalivro.png");
    loadTexture(texID[5], "texturas/perna.png");
    loadTexture(texID[6], "texturas/relogio.png");
    loadTexture(texID[7], "texturas/gr.png");
    loadTexture(texID[8], "texturas/piso.jpg");
    loadTexture(texID[9], "texturas/porta.png");
    loadTexture(texID[10], "texturas/vangogh.png");
    loadTexture(texID[11], "texturas/mac.jpg");
    loadTexture(texID[12], "texturas/cm.jpg");
    loadTexture(texID[13], "texturas/cm2.jpg");
    loadTexture(texID[14], "texturas/janela.jpg");
    loadTexture(texID[15], "texturas/cor2.jpg");

    for(int i = 0; i < total_obj; i++) {
        Obj p;
        obj.push_back(p);
    }

    obj[0].id = glGenLists(total_obj);
    drawGround(obj[0].id);

    for(int i = 1; i < total_obj; i++) {
        obj[i].id = obj[0].id + i;
    }
    // Parede fundo
    obj[1].pos = vec3(0.0, 0.5, -10.0);                     // Posição
    drawCube_wTex(obj[1].id, 3.0, 1.0, 0.05, texID[0]);     // Tamanho
    // Parede direita
    obj[2].pos = vec3(3.0, 0.5, -7.05);                     // Posição
    drawCube_wTex(obj[2].id, 0.05, 1.0, 3.0, texID[0]);     // Tamanho
    // Parede esquerda/frente
    obj[3].pos = vec3(-3.0, 0.5, -5.25);                    // Posição
    drawCube_wTex(obj[3].id, 0.05, 1.0, 1.2, texID[0]);     // Tamanho
    // Parede esquerda/cima
    obj[4].pos = vec3(-3.0, 1.15, -7.05);                   // Posição
    drawCube_wTex(obj[4].id, 0.05, 0.27, 0.8, texID[0]);    // Tamanho
    // Parede esquerda/baixo
    obj[5].pos = vec3(-3.0, -0.15, -7.05);                  // Posição
    drawCube_wTex(obj[5].id, 0.05, 0.33, 0.8, texID[0]);    // Tamanho
    // Parede esquerda/fundo
    obj[6].pos = vec3(-3.0, 0.5, -8.85);                    // Posição
    drawCube_wTex(obj[6].id, 0.05, 1.0, 1.2, texID[0]);     // Tamanho
    // Parede frente/direita
    obj[7].pos = vec3(0.6, 0.5, -4.10);                     // Posição
    drawCube_wTex(obj[7].id, 2.40, 1.0, 0.05, texID[0]);    // Tamanho
    // Parede frente/esquerda
    obj[8].pos = vec3(-2.9, 0.5, -4.10);                    // Posição
    drawCube_wTex(obj[8].id, -0.14, 1.0, 0.05, texID[0]);   // Tamanho
    // Parede frente/cima
    obj[9].pos = vec3(-0.8, 1.2, -4.10);                    // Posição
    drawCube_wTex(obj[9].id, -2.0, 0.3, 0.05, texID[0]);    // Tamanho
    // Teto
    obj[10].pos = vec3(0.0, 1.4, -7.05);                    // Posição
    drawCube_wTex(obj[10].id, -3.0, 0.05, 3.0, texID[0]);   // Tamanho
    // Piso
    obj[11].pos = vec3(0.0, -0.5, -7.05);                   // Posição
    drawCube_wTex(obj[11].id, -3.05, 0.007, 3.0, texID[8]); // Tamanho
    
    // Tapete
    obj[12].pos = vec3(0.0, -0.49, -7.05);                  // Posição
    drawCube_wTex(obj[12].id, 1.0, -0.007, 1.0, texID[2]);  // Tamanho

    // Pé 1 cama
    obj[13].pos = vec3(1.5, -0.4, -7.05);                   // Posição
    drawCube_wTex(obj[13].id, -0.03, 0.08, 0.03, texID[3]); // Tamanho
    // Pé 2 cama
    obj[14].pos = vec3(1.5, -0.4, -6.55);                   // Posição
    drawCube_wTex(obj[14].id, -0.03, 0.08, 0.03, texID[3]); // Tamanho
    // Pé 3 cama
    obj[15].pos = vec3(2.8, -0.4, -7.05);                   // Posição
    drawCube_wTex(obj[15].id, -0.03, 0.08, 0.03, texID[3]); // Tamanho
    // Pé 4 cama
    obj[16].pos = vec3(2.8, -0.4, -6.55);                   // Posição
    drawCube_wTex(obj[16].id, -0.03, 0.08, 0.03, texID[3]); // Tamanho
    // Colchão box
    obj[17].pos = vec3(2.15, -0.25, -6.8);                  // Posição
    drawCube(obj[17].id, -0.7, 0.15, 0.3);                  // Tamanho
    // Cabeceira da cama box
    obj[18].pos = vec3(2.87, -0.1, -6.8);                   // Posição
    drawCube_wTex(obj[18].id, -0.03, 0.3, 0.3, texID[1]);   // Tamanho
    
    // Mesa
    obj[19].pos = vec3(1.0, 0.0, -4.4);                     // Posição
    drawCube_wTex(obj[19].id, 0.7, 0.01, 0.2, texID[1]);    // Tamanho
    // Perna 1 mesa
    obj[20].pos = vec3(1.6, -0.27, -4.57);                  // Posição
    drawCube_wTex(obj[20].id, -0.01, 0.27, 0.01, texID[5]); // Tamanho
    // Perna 2 mesa
    obj[21].pos = vec3(1.6, -0.27, -4.23);                  // Posição
    drawCube_wTex(obj[21].id, -0.01, 0.27, 0.01, texID[5]); // Tamanho
    // Perna 3 mesa
    obj[22].pos = vec3(0.39, -0.27, -4.57);                 // Posição
    drawCube_wTex(obj[22].id, -0.01, 0.27, 0.01, texID[5]); // Tamanho
    // Perna 4 mesa
    obj[23].pos = vec3(0.39, -0.27, -4.23);                 // Posição
    drawCube_wTex(obj[23].id, -0.01, 0.27, 0.01, texID[5]); // Tamanho

    // Cadeira
    obj[24].pos = vec3(1.0, -0.2, -4.7);                        // Posição
    drawCube_wTex(obj[24].id, 0.15, 0.005, 0.15, texID[13]);    // Tamanho
    // Perna 1 cadeira
    obj[25].pos = vec3(1.12, -0.37, -4.57);                 // Posição
    drawCube_wTex(obj[25].id, 0.01, 0.17, 0.01, texID[5]);  // Tamanho
    // Perna 2 cadeira
    obj[26].pos = vec3(1.12, -0.37, -4.83);                 // Posição
    drawCube_wTex(obj[26].id, 0.01, 0.17, 0.01, texID[5]);  // Tamanho
    // Perna 3 cadeira
    obj[27].id = obj[0].id + 27;
    obj[27].pos = vec3(0.87, -0.37, -4.57);                 // Posição
    drawCube_wTex(obj[27].id, 0.01, 0.17, 0.01, texID[5]);  // Tamanho
    // Perna 4 cadeira
    obj[28].pos = vec3(0.87, -0.37, -4.83);                 // Posição
    drawCube_wTex(obj[28].id, 0.01, 0.17, 0.01, texID[5]);  // Tamanho
    // Encosto cadeira
    obj[29].pos = vec3(1.0, -0.05, -4.83);                      // Posição
    drawCube_wTex(obj[29].id, 0.15, 0.15, 0.005, texID[13]);    // Tamanho

    // Livro
    obj[30].pos = vec3(1.5, 0.02, -4.4);                    // Posição
    drawCube_wTex(obj[30].id, -0.1, 0.01, 0.12, texID[4]);  // Tamanho

    // Guarda-roupas
    obj[31].pos = vec3(0.5, 0.3, -9.6);                     // Posição
    drawCube_wTex(obj[31].id, 1.1, 0.8, -0.3, texID[15]);   // Tamanho
    obj[32].pos = vec3(0.5, 0.3, -9.6);                         // Posição
    drawCube_wTex(obj[32].id, 1.09, 0.79, -0.301, texID[7]);    // Tamanho

    // Criado mudo
    obj[33].pos = vec3(2.5, -0.27, -4.4);                   // Posição
    drawCube_wTex(obj[33].id, 0.25, 0.2, 0.2, texID[12]);   // Tamanho
    obj[34].pos = vec3(2.5, -0.27, -4.4);                       // Posição
    drawCube_wTex(obj[34].id, 0.251, 0.201, 0.199, texID[13]);  // Tamanho

    // Base ventilador
    obj[35].pos = vec3(2.5, -0.05, -4.4);                   // Posição
    drawCube_wTex(obj[35].id, 0.08, 0.01, 0.08, texID[3]);  // Tamanho
    // Tronco ventilador
    obj[36].pos = vec3(2.5, -0.03, -4.35);                  // Posição
    drawCube_wTex(obj[36].id, 0.02, 0.08, 0.02, texID[5]);  // Tamanho
    // Motor ventilador
    obj[37].pos = vec3(2.5, 0.07, -4.37);                   // Posição
    drawCube_wTex(obj[37].id, 0.05, 0.04, 0.05, texID[3]);  // Tamanho
    // Conexão motor-hélice
    obj[38].pos = vec3(2.5, 0.07, -4.39);                       // Posição
    drawCube_wTex(obj[38].id, 0.005, 0.005, 0.05, texID[5]);    // Tamanho
    // Hélice 1
    obj[39].pos = vec3(2.5, 0.07, -4.44);                   // Posição
    drawCube(obj[39].id, 0.08, 0.01, -0.005);               // Tamanho
    // Hélice 2
    obj[40].pos = vec3(2.5, 0.07, -4.44);                   // Posição
    drawCube(obj[40].id, 0.01, 0.08, -0.005);               // Tamanho
    // Grade
    obj[41].pos = vec3(2.5, 0.07, -4.44);                   // Posição
    drawSphere(obj[41].id, black, 0.09, 25.0, 25.0);        // Tamanho

    // Relógio
    obj[42].pos = vec3(1.0, 0.8, -4.15);                    // Posição
    drawCube_wTex(obj[42].id, 0.15, 0.15, 0.005, texID[6]); // Tamanho

    // Porta
    obj[43].pos = vec3(-2.28, 0.2, -4.10);                  // Posição
    drawCube_wTex(obj[43].id, 0.477, 0.7, 0.03, texID[9]);  // Tamanho

    // Janela
    obj[44].pos = vec3(-3.0, 0.53, -6.75);                  // Posição
    drawCube_wTex(obj[44].id, -0.05, 0.35, 0.3, texID[14]); // Tamanho
    obj[45].pos = vec3(-3.0, 0.53, -7.35);                      // Posição
    drawCube_wTex(obj[45].id, -0.05, -0.35, 0.3, texID[14]);    // Tamanho

    // Quadro Van Gogh
    obj[46].pos = vec3(2.95, 0.8, -6.8);                    // Posição
    drawCube_wTex(obj[46].id, 0.01, 0.2, -0.4, texID[10]);  // Tamanho

    // Macbook
    obj[47].pos = vec3(1.0, 0.02, -4.4);                        // Posição
    drawCube_wTex(obj[47].id, -0.12, 0.01, -0.1, texID[11]);    // Tamanho

    // Esfera luz
    obj[48].pos = vec3(0.7, 0.25, -4.4);                     // Posição
    esfera(obj[48].id);
    // Suporte
    obj[49].pos = vec3(0.6, 0.26, -4.4);                     // Posição
    drawCube_wTex(obj[49].id, 0.08, 0.01, 0.01, texID[3]);   // Tamanho
    obj[50].pos = vec3(0.55, 0.14, -4.4);                    // Posição
    drawCube_wTex(obj[50].id, 0.01, 0.13, 0.01, texID[3]);   // Tamanho
    // Base abajur
    obj[51].pos = vec3(0.57, 0.02, -4.4);                    // Posição
    drawCube_wTex(obj[51].id, 0.07, 0.01, 0.07, texID[3]);   // Tamanho
}

int main(void) {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1366, 768, "Bedroom", NULL, NULL);

    glfwMakeContextCurrent(window);

    // Início
    init(window);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        resize(width, height);
        draw();

        glfwSwapBuffers(window);
    }

    glDeleteLists(obj[0].id, total_obj);
    glDeleteTextures(1, texID);
    glfwTerminate();
    return 0;
}
