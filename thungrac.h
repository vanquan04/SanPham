#ifndef thungrac_H
#define thungrac_H

#include "glut.h"

class thungrac {
private:
    float posX, posY, posZ; 
    float scaleX, scaleY, scaleZ; 
    float angleX, angleY, angleZ; 
    float bodyColorR, bodyColorG, bodyColorB; 
    float lidColorR, lidColorG, lidColorB; 

public:
    thungrac();


    void setPosition(float x, float y, float z);
    void setScale(float sx, float sy, float sz);
    void setRotation(float ax, float ay, float az);
    void setBodyColor(float r, float g, float b);
    void setLidColor(float r, float g, float b);


    void draw();
};

#endif