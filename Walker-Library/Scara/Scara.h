#ifndef _SCARA_H
#define _SCARA_H

#include "mbed.h"
#include "Servo.h"
#include <cstdint>
#include <stdint.h>
#include <math.h>

#define PI 3.141592

struct vector2D{
    float x;
    float y;
};

class Scara {

    public:
        Scara(Servo* J1, Servo* J2, uint16_t a, uint16_t b);
        uint16_t move(vector2D pose);

    private:
        Servo* J1;
        Servo* J2;
        uint16_t a;
        uint16_t b;

};

#endif