#ifndef BANGHE_H
#define BANGHE_H

#include "glut.h"

// Hàm vẽ bộ bàn ghế sofa góc phòng
void drawBanGheSofa();

// Hàm vẽ ghế sofa đơn
void drawSofaChair(float x, float y, float z, float rotateY);

// Hàm vẽ bàn trà
void drawCoffeeTable(float x, float y, float z);

// Hàm vẽ tựa ghế
void drawSofaBack(float width, float height, float depth);

// Hàm vẽ đệm ghế
void drawSofaCushion(float width, float height, float depth);

// Hàm vẽ chân ghế/bàn
void drawFurnitureLeg(float x, float y, float z, float height);

#endif#pragma once
