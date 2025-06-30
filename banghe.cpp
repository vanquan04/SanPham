#include "banghe.h"
#include <math.h>

// Hàm vẽ chân đồ nội thất
void drawFurnitureLeg(float x, float y, float z, float height) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.4f, 0.2f, 0.1f); // Màu nâu gỗ
    glScalef(0.08f, height, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Hàm vẽ đệm ghế sofa
void drawSofaCushion(float width, float height, float depth) {
    glColor3f(0.2f, 0.5f, 0.8f); // Màu xanh đệm
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Hàm vẽ tựa lưng ghế sofa
void drawSofaBack(float width, float height, float depth) {
    glColor3f(0.15f, 0.4f, 0.7f); // Màu xanh đậm hơn
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Hàm vẽ ghế sofa đơn
void drawSofaChair(float x, float y, float z, float rotateY) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotateY, 0, 1, 0);
    // Khung ghế chính
    glColor3f(0.3f, 0.15f, 0.08f);
    glPushMatrix();
    glTranslatef(0, 0.25f, 0);
    glScalef(1.8f, 0.1f, 0.9f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Đệm ngồi
    glPushMatrix();
    glTranslatef(0, 0.35f, 0);
    drawSofaCushion(1.7f, 0.15f, 0.8f);
    glPopMatrix();
    // Tựa lưng
    glPushMatrix();
    glTranslatef(0, 0.6f, -0.35f);
    drawSofaBack(1.7f, 0.6f, 0.15f);
    glPopMatrix();
    // Tay vịn trái
    glPushMatrix();
    glTranslatef(-0.75f, 0.5f, 0);
    drawSofaBack(0.2f, 0.4f, 0.8f);
    glPopMatrix();
    // Tay vịn phải
    glPushMatrix();
    glTranslatef(0.75f, 0.5f, 0);
    drawSofaBack(0.2f, 0.4f, 0.8f);
    glPopMatrix();
    // 4 chân ghế
    drawFurnitureLeg(-0.7f, 0.125f, -0.35f, 0.25f);
    drawFurnitureLeg(0.7f, 0.125f, -0.35f, 0.25f);
    drawFurnitureLeg(-0.7f, 0.125f, 0.35f, 0.25f);
    drawFurnitureLeg(0.7f, 0.125f, 0.35f, 0.25f);
    glPopMatrix();
}

// Hàm vẽ bàn trà
void drawCoffeeTable(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Mặt bàn
    glColor3f(0.6f, 0.4f, 0.2f); // Màu gỗ sáng
    glPushMatrix();
    glTranslatef(0, 0.4f, 0);
    glScalef(1.2f, 0.08f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Viền mặt bàn
    glColor3f(0.5f, 0.3f, 0.15f); // Màu gỗ đậm hơn
    glPushMatrix();
    glTranslatef(0, 0.42f, 0);
    glScalef(1.25f, 0.04f, 0.85f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng dưới (kệ sách/đồ)
    glColor3f(0.55f, 0.35f, 0.18f);
    glPushMatrix();
    glTranslatef(0, 0.15f, 0);
    glScalef(1.1f, 0.06f, 0.7f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 4 chân bàn
    drawFurnitureLeg(-0.5f, 0.2f, -0.3f, 0.4f);
    drawFurnitureLeg(0.5f, 0.2f, -0.3f, 0.4f);
    drawFurnitureLeg(-0.5f, 0.2f, 0.3f, 0.4f);
    drawFurnitureLeg(0.5f, 0.2f, 0.3f, 0.4f);

    // Thanh ngang giữa các chân (tăng độ chắc chắn)
    glColor3f(0.4f, 0.2f, 0.1f);
    // Thanh ngang trước-sau
    glPushMatrix();
    glTranslatef(0, 0.1f, -0.3f);
    glScalef(1.0f, 0.04f, 0.04f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.1f, 0.3f);
    glScalef(1.0f, 0.04f, 0.04f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Thanh ngang trái-phải
    glPushMatrix();
    glTranslatef(-0.5f, 0.1f, 0);
    glScalef(0.04f, 0.04f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.1f, 0);
    glScalef(0.04f, 0.04f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

// Hàm vẽ bộ bàn ghế sofa - điều chỉnh vị trí
void drawBanGheSofa() {
    // Đặt bộ bàn ghế dưới đồng hồ và hướng vào trong phòng

    // Ghế sofa chính (hướng vào giữa phòng - xoay 90 độ để hướng vào trong)
    drawSofaChair(-4.5f, 0.0f, 3.25f, 90.0f);

    // Ghế sofa thứ hai (tạo góc vuông với ghế chính)
    drawSofaChair(-3.25f, 0.0f, 4.5f, -180.0f);

    // Bàn trà 
    drawCoffeeTable(-3.1f, 0.0f, 3.25f);

    glPopMatrix();

}