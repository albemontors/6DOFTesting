/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "PinNames.h"
#include <cstdint>
#include <cstdlib>


#include "mbed.h"
#include <Adafruit_PWMServoDriver.h>

#include "3DofWalkerLib.h"

//#define POSITIONTEST

// Blinking rate in milliseconds
#define BLINKING_RATE   500ms
#define SERVO_FREQ      50 // Analog servos run at ~50 Hz updates
#define UP              0
#define DOWN            1
#define MAX        130
#define MIN        60
#define MAXSPEED      25

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    DigitalIn SW1(D2);
    SW1.mode(PullUp);

    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PB_7, PB_6, 0x80);

    printf("Init processing... \n");

    int control = 0;
    bool direction = 0;
    uint16_t error_code = 0;

    led.write(0);
    pwm.begin();
    wait_us(100000);
    //pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    wait_us(100000);

    Servo J1 = Servo(0, &pwm, -21, 1.0f);
    Servo J2 = Servo(1, &pwm, 163, -1.0f);
    Servo J3 = Servo(2, &pwm, -75, 1.0f);
    //Servo J3 = Servo(2, &pwm, 90, -1.0f);

    Servo J4 = Servo(3, &pwm, 75, 1.0f);
    Servo J5 = Servo(4, &pwm, 90, -1.0f);
    Servo J6 = Servo(5, &pwm, 90, 1.0f);

    Scara scara1 = Scara(&J2,  &J3,  80, 80);

    Leg arm = Leg(&J1, &scara1);

    vector3D home = {-100, 0, 50};
    vector3D pos1 = {-120, 0, 50};
    vector3D pos2 = {-120, 0, 30};
    vector3D pos3 = {-100, 0, 30};
    vector3D posDes = {-80, 0, 50};

    int stage = 0;
    float dx = 2.0f;
    
    printf("Init complete. \n");
    
#ifdef POSITIONTEST
    while (true) {
        J1.move(90);
        J2.move(90);
        control = J3.move(90);
        J4.move(0);
        J5.move(0);
        J6.move(0);
        wait_us(1000000);
        printf(" control: %d \n", control);
        //scanf("%d", &control);
    }
#endif

    while(1) {
        arm.move(posDes);
        wait_us(1000);
        switch(stage){
            case 0:
                posDes.x-= dx;
                if(posDes.x <= -120) stage = 1;
                break;
            case 1:
                posDes.z -= dx;
                if(posDes.z <= 10) stage = 2;
                break;
            case 2:
                posDes.x += dx;
                if(posDes.x >= -80) stage = 3;
                break;
            case 3:
                posDes.z += dx;
                if(posDes.z >= 80) stage = 0;
                break;
            default:
                while(1); //block execution if something fucked happens
        }

        

    }
}
