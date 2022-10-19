#include "Scara.h"


Scara::Scara(Servo* J1, Servo* J2, uint16_t a, uint16_t b){
    this->J1 = J1;
    this->J2 = J2;
    this->a = a;
    this->b = b;
}

uint16_t Scara::move(vector2D pose){

    float c = sqrt(pow(pose.x, 2) + pow(pose.y, 2));
    if(c > a + b) return 1;
    float gamma = acos((pow(c, 2) - pow(a, 2) - pow(b, 2)) / ((-2.0f) * a * b ));
    float beta = PI - gamma;
    float phi = acos((pow(b, 2) - pow(a, 2) - pow(c, 2)) / ((-2.0f) * a * c ));
    //float theta = pose.x ? atan(pose.y / pose.x) : 90.0f; // safe atan calculation // deprecated for pose being float now
    float theta = atan(pose.y / pose.x);
    if(theta < 0) theta += PI;
    float alpha = theta - phi;
    if(alpha > PI) alpha -= 2*PI;

    int angleJ1 = alpha / PI * 180.0f;
    int angleJ2 = beta / PI * 180.0f;

    printf(" Angle 1: %d Angle 2: %d Theta = %d Phi = %d Gamma = %d \n", angleJ1, angleJ2, (int)(theta/PI*180), (int)(phi/PI*180), (int)(gamma/PI*180));
    
    int J1control = this->J1->move(angleJ1);
    int J2control = this->J2->move(angleJ2 + angleJ1 - 90);

    printf("servos returns are : %d, %d \n", J1control, J2control);

    return 0;

}

