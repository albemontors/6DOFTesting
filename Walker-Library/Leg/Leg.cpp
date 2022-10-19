#include "Leg.h"


Leg::Leg(Servo* J1, Scara* scara){

    this->scara = scara;
    this->J1 = J1;

}

uint16_t Leg::move(vector3D pose){

    vector2D scaraPose;

    //float theta = pose.y ? atan(pose.z / pose.y) : 90.0f; // safe atan calculation // deprecated for pose being float now
    float theta = atan(pose.z / pose.y);
    if(theta < 0) theta += PI;
    scaraPose.x = pose.x;
    scaraPose.y = sqrt(pow(pose.y, 2) + pow(pose.z, 2));
    theta = theta / PI * 180;
    //printf("%d \n", (int)theta);

    // write the values to J1 and scara
    this->J1->move(theta);
    this->scara->move(scaraPose);

    // return no issue code
    return 0;

}
