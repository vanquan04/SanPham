// gau.h
#ifndef GAU_H
#define GAU_H

void drawToyBear(float x, float y, float z, float scale);
void updateBearPosition();
void moveBearToTarget(float x, float y, float z);
void moveBearToCarpet();
bool checkBearClick(float mouseX, float mouseY, float mouseZ, float radius);

// Biến toàn cục để xác định tư thế đứng của gấu
extern bool isStanding;
extern bool isMoving;
extern float bearX, bearY, bearZ;
extern bool atCarpet;
extern float originalBearX, originalBearY, originalBearZ;

#endif