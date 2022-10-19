#ifndef _WALKER_H
#define _WALKER_H

#include "ns_types.h"
#include <cstdint>
#include "Leg.h"

struct PoseList{
    Leg** vector3D;
    uint16_t legNumber;
    uint16_t poseCode;
    PoseList* next;
};


class Walker{

    public:
        Walker(Leg** LegArray, uint16_t legNumber);
        uint16_t update();
        uint16_t motionSet(uint16_t motionCode, int speed);
        uint16_t setPose(uint16_t poseCode);
        uint16_t getPose();
        uint16_t getProgress();
        uint16_t getState();
        uint16_t createPose(Leg** vector3D, uint16_t legNumber, uint16_t poseCode);

        enum State {AG_IN_POSE, AG_IN_MOTION};
        enum Poses {REST, READY, HAPPY, SAD};
        enum Motions {WALK, RUN, PISS};

    private:
        uint16_t legNumber;
        Leg** LegArray;
        PoseList* poseList;

};

#endif