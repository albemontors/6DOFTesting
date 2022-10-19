#ifndef _SERVO_H
#define _SERVO_H

#include "mbed.h"
#include "Adafruit_PWMServoDriver.h"
#include <cstdint>
#include <stdint.h>
#include <system_error>

#define SERVOMIN 10
#define SERVOMAX 170
#define USMIN  150 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150 #600
#define USMAX  525 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600 #2400
#define LOWERLIMIT 10
#define UPPERLIMIT 170

class Servo {

    public:
        Servo(uint16_t servoIDlink, Adafruit_PWMServoDriver *driverlink);
        Servo(uint16_t servoIDlink, Adafruit_PWMServoDriver *driverlink, int offset, float k);
        uint16_t move(int angle);

        enum errorCode {NO_ERROR, OUT_OF_RANGE, EVALUATION_ERROR};

    private:
        Adafruit_PWMServoDriver *driver;
        uint16_t servoID;
        uint16_t servoMin;
        uint16_t servoMax;
        uint16_t usMin;
        uint16_t usMax;
        int offset;
        float k;

};



#endif