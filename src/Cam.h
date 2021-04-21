#include "cg.h"

class Cam {
    private:
        vec3 m_pos;
        vec3 m_dir;
        vec3 m_left;
        vec3 m_up;
        vec3 m_spd;
        float m_scl = 0.25;
        float m_yaw;
        float m_PI = 3.14159265;

    public:
        Cam(vec3 pos);
        ~Cam();
        void activate();

        void forward();
        void back();
        void left();
        void right();
        void updateYaw(float dYaw);
        void update();

    private:
        float toRad(float ang);

};