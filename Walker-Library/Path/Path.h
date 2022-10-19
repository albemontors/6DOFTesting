#ifndef _PATH_H
#define _PATH_H

#include "mbed.h"

#include "Leg.h"
#include <cstdint>
#include <stdint.h>
#include <vector>

class Path {

    public:
        Path(Leg* leg, vector3D home);
        Path(Leg* leg);
        uint16_t update(int progress);
        int      incrementalUpdate(int increment);
        uint16_t setPath(uint16_t pathCode);
        uint16_t go(uint16_t positionCode);
        uint16_t savePose(vector3D pose);
        uint16_t setShitfX(float xShift);
        uint16_t setShitfY(float yShift);
        uint16_t setShitfZ(float zShift);

    private:
        int pathProgress;
        Leg* leg;
        vector<vector3D> savedPoses;
        uint16_t selectedPath;
        float xShift;
        float yShift;
        float zShift;
        
};

vector3D path(int code, int progress);

#endif