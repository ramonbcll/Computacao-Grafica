#include <C:\temp\include\GL\glut.h>
#include <C:\temp\include\GLFW\glfw3.h>
#include "colors.h"
#include <vector>
#include <cmath>
#include "Cam.h"

void rectTex(vec3 p1, vec3 p2, vec3 p3, vec3 p4) {
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3fv(&p1.x);
        glTexCoord2f(1.0, 0.0); glVertex3fv(&p2.x);
        glTexCoord2f(1.0, 1.0); glVertex3fv(&p3.x);
        glTexCoord2f(0.0, 1.0); glVertex3fv(&p4.x);
    glEnd();
}

void drawCube_wTex(GLuint id, float x, float y, float z, GLuint texid) {
    vec3 v1(-x,  y,  z);
    vec3 v2(-x, -y,  z);
    vec3 v3( x, -y,  z);
    vec3 v4( x,  y,  z);
    vec3 v5( x,  y, -z);
    vec3 v6( x, -y, -z);
    vec3 v7(-x, -y, -z);
    vec3 v8(-x,  y, -z);

	glNewList(id, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, texid);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float ambiente[] = {0.5f, 0.5f, 0.5f, 1.f};
    float especular[] = {0.5f, 0.5f, 0.5f, 1.f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);	
   
    glNormal3f(0.f, 0.f, 1.f);
    rectTex(v2, v3, v4, v1); // Front

    glNormal3f(1.f, 0.f, 0.f);
    rectTex(v4, v3, v6, v5); // Right

    glNormal3f(0.f, 0.f, -1.f);
    rectTex(v5, v8, v7, v6); // Back

    glNormal3f(-1.f, 0.f, 0.f);
    rectTex(v1, v8, v7, v2); // Left

    glNormal3f(0.f, 1.f, 0.f);
    rectTex(v1, v4, v5, v8); // Top

    glNormal3f(0.f, -1.f, 0.f);
    rectTex(v2, v7, v6, v3); // Bottom

    glBindTexture(GL_TEXTURE_2D, 0);

	glEndList();
}

void rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4, color cor) {
    glColor3fv(cor);
    glBegin(GL_QUADS);
        glVertex3fv(&p1.x);
        glVertex3fv(&p2.x);
        glVertex3fv(&p3.x);
        glVertex3fv(&p4.x);
    glEnd();
}

void drawCube(GLuint id, float x, float y, float z) {
    vec3 v1(-x,  y,  z);
    vec3 v2(-x, -y,  z);
    vec3 v3( x, -y,  z);
    vec3 v4( x,  y,  z);
    vec3 v5( x,  y, -z);
    vec3 v6( x, -y, -z);
    vec3 v7(-x, -y, -z);
    vec3 v8(-x,  y, -z);

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float ambiente[] = {0.5f, 0.5f, 0.5f, 1.f};
    float especular[] = {0.5f, 0.5f, 0.5f, 1.f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);

    glNormal3f(0.f, 0.f, 1.f);
    rect(v2, v3, v4, v1, red); // Front

    glNormal3f(1.f, 0.f, 0.f);
    rect(v4, v3, v6, v5, blue); // Right

    glNormal3f(0.f, 0.f, -1.f);
    rect(v5, v8, v7, v6, yellow); // Back

    glNormal3f(-1.f, 0.f, 0.f);
    rect(v1, v8, v7, v2, green); // Left

    glNormal3f(0.f, 1.f, 0.f);
    rect(v1, v4, v5, v8, orange); // Top

    glNormal3f(0.f, -1.f, 0.f);
    rect(v2, v7, v6, v3, violet); // Bottom

	glEndList();
}

void drawSphere(unsigned int& id, color cor, GLfloat raio, GLuint nStacks, GLuint nSectors) {
    std::vector<std::vector<GLuint> > indices;
    std::vector<vec3> points;
    const GLfloat PI = 3.14159265359;

    GLfloat deltaPhi = PI / nStacks;
    GLfloat deltaTheta = 2 * PI / nSectors;

    for(GLuint i = 0; i <= nStacks; i++) {
        GLfloat phi = -PI / 2.0 + i * deltaPhi;
        GLfloat temp = raio * cos(phi);
        GLfloat y = raio * sin(phi);

        std::vector<GLuint> pt;

        for(GLuint j = 0; j < nSectors; j++) {
            GLfloat theta = j * deltaTheta;
            GLfloat x = temp * sin(theta);
            GLfloat z = temp * cos(theta) / 3.0;

            points.push_back(vec3(x, y, z)); 
            GLuint index = points.size() - 1;
            pt.push_back(index);
        }
        indices.push_back(pt);
    }

	glNewList(id, GL_COMPILE);

	glColor3fv(cor);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	for(GLuint i = 0; i < nStacks; i++) {
		glBegin(GL_TRIANGLE_STRIP);  
			for(GLuint j = 0; j < nSectors; j++) {
				GLuint index = indices[i][j];
				glVertex3fv(&points[index].x);
				index = indices[i + 1][j];
				glVertex3fv(&points[index].x);

				if(j == nSectors - 1) {
					index = indices[i][0];
					glVertex3fv(&points[index].x);
					index = indices[i + 1][0];
					glVertex3fv(&points[index].x);
				}
			}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
    glEndList();
}

void drawGround(unsigned int id) {
    float L = 500.0;
    float incr = 1.0;
    float y = -0.5;

	glNewList(id, GL_COMPILE);
    glColor3fv(white_i);

    glBegin(GL_LINES);
    for(float i = -L; i <= L; i += incr) {
        // Verticais
		glVertex3f(i, y, -L);
        glVertex3f(i, y, L);
		// Horizontais
		glVertex3f(-L, y, i);
        glVertex3f(L, y, i);
    }
	glEnd();
	glEndList();
}

void esfera(unsigned int& id) {
	std::vector<std::vector<vec3> > pontos;
	std::vector<std::vector<vec3> > normals;

	float raio = 0.04f;
	unsigned nStacks = 10;
	unsigned nSectors = 10;
	const float PI = 3.14159265359;
	const float TWO_PI = 2 * PI;
	const float HALF_PI = PI / 2.0;

	float deltaPhi = PI / nStacks;
	float deltaTheta = TWO_PI / nSectors;


	for (unsigned i = 0; i <= nStacks; i++) {
		float phi = -HALF_PI + i * deltaPhi;
		float temp = raio * cos(phi);
		float y = raio * sin(phi)/1.5;

		std::vector<vec3> pts;

		for (unsigned j = 0; j <= nSectors; j++) {
			float theta = j * deltaTheta;
			float x = temp * sin(theta);
			float z = temp * cos(theta);

			float s = theta / TWO_PI;
			GLfloat t = phi / PI + 0.5;

			pts.push_back(vec3(x, y, z));
		}// next j

		pontos.push_back(pts);
		normals.push_back(pts);
	}// next i

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	for (unsigned i = 0; i < nStacks; i++) {
		glBegin(GL_TRIANGLE_STRIP);

		for (unsigned j = 0; j <= nSectors; j++) {
			glNormal3fv(&normals[i][j].x); glVertex3fv(&pontos[i][j].x);
			glNormal3fv(&normals[i + 1][j].x); glVertex3fv(&pontos[i + 1][j].x);
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	glEndList();
}