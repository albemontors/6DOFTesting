#include "Path.h"
#include <cstdint>


Path::Path(Leg* leg, vector3D home){
    
    this->leg = leg;
    savedPoses.push_back(home);
    this->leg->move(home);
    this->xShift = 0;
    this->yShift = 0;
    this->zShift = 0;
    this->pathProgress = 0;

}

Path::Path(Leg* leg){

    this->leg = leg;

}

uint16_t Path::update(int progress){

    this->pathProgress = progress;

    vector3D pose = path(this->selectedPath, progress);

    pose.x += this->xShift;
    pose.y += this->yShift;
    pose.z += this->zShift;

    this->leg->move(pose);

    return 0;

}

int Path::incrementalUpdate(int increment){

    this->pathProgress += increment;

    int progress = this->pathProgress;

    vector3D pose = path(this->selectedPath, progress);

    pose.x += this->xShift;
    pose.y += this->yShift;
    pose.z += this->zShift;

    this->leg->move(pose);

    return progress;

}

uint16_t Path::setPath(uint16_t pathCode){

    this->selectedPath = pathCode;
    return 0;

}

uint16_t Path::go(uint16_t positionCode){

    this->leg->move(this->savedPoses.at(positionCode));
    return 0;

}

uint16_t Path::savePose(vector3D pose){

    this->savedPoses.push_back(pose);
    return 0;

}

uint16_t Path::setShitfX(float xShift){

    this->xShift = xShift;
    return 0;

}

uint16_t Path::setShitfY(float yShift){

    this->yShift = yShift;
    return 0;

}

uint16_t Path::setShitfZ(float zShift){

    this->zShift = zShift;
    return 0;

}

vector3D path(int code, int progress){

    vector3D pose;

    float stage;

    switch(code){

        default:
        case 0:
            // standard path data
            progress = progress % 1000;
            pose.y = 0;

            if(progress > 905){
                stage = (progress - 905.0f) / 95.0f;
                pose.z = 60.0f + (10.0f * (1.0f - stage));
                pose.x = -90.0f * stage;
                break;
            }
            if(progress > 865){
                stage = (progress - 865.0f) / 40.0f;
                pose.z = 70.0f;
                pose.x = 40.0f * (1.0f - stage);
                break;
            }
            if(progress > 835){
                stage = (progress - 835.0f) / 30.0f;
                pose.z = 70.0f + 30 * (1.0f - stage);
                pose.x = 40.0f;
                break;
            }
            if(progress > 45){
                stage = (progress - 45.0f) / 790.0f;
                pose.z = 100.0f;
                pose.x = -60.0f + 100.0f * stage;
                break;
            }
            stage = progress / 45.0f;
            pose.z = 60.0f + 40.0f * stage;
            pose.x = -90.0f + 30.0f * stage;

            break;

    }
    return pose;
}