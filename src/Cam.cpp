#include "Cam.h"
#include <C:\temp\include\GL\glut.h>
#include <gl/GLU.h>

Cam::Cam(vec3 pos) {
	m_pos = vec3(pos);
	m_dir = vec3(0, 0, -1);
	m_left = vec3(-1, 0, 0);
	m_up = vec3(0, 1, 0);
    m_spd = vec3(0, 0, 0);
}

Cam::~Cam() {
}

void Cam::activate() {
	vec3 look = m_pos + m_dir;
    gluLookAt(m_pos.x + 0.4, m_pos.y + 0.5, m_pos.z, look.x + 0.4, look.y + 0.3, look.z, m_up.x, m_up.y, m_up.z);
}

void Cam::forward() {
    m_spd = m_dir * m_scl;
    m_pos = m_pos + m_spd;
}

void Cam::back() {
    m_spd = m_dir * (-m_scl);
    m_pos = m_pos + m_spd;
}

void Cam::left() {
    m_spd = m_left * m_scl;
    m_pos = m_pos + m_spd;
}

void Cam::right() {
    m_spd = m_left * (-m_scl);
    m_pos = m_pos + m_spd;
}

void Cam::updateYaw(float dYaw) {
    m_yaw += dYaw;
}

void Cam::update() {
    float ang = toRad(m_yaw);
    m_dir.x = sin(ang);
    m_dir.z = -cos(ang);
    m_dir.normaliza();
    m_left = m_up.prodVetorial(m_dir);
}

float Cam::toRad(float ang) {
    return (ang * m_PI) / 180.0;
}