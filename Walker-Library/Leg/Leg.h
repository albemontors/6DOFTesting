#ifndef _LEG_H
#define _LEG_H

#include "mbed.h"
#include "Scara.h"
#include "Servo.h"
#include <cstdint>
#include <stdint.h>

struct vector3D{
    float x;
    float y;
    float z;
};

class Leg {
    public:
        Leg(Servo* J1, Scara* scara);
        uint16_t move(vector3D pose);
    
    private:
        Servo* J1;
        Scara* scara;
        
};

#endif