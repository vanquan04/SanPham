#include "ketu.h"
#include "cua.h"

// Hàm vẽ kệ hình chữ S
void drawSShapedShelf() {
    float shelfX = -4.5f;  // Sát tường trái (x gần -5)
    float shelfZ = -4.8f;  // Sát tường sau  (z gần -5)


    glColor3f(0.6f, 0.4f, 0.2f); // Màu gỗ

    // Cột dọc chính của kệ
    glPushMatrix();
    glTranslatef(shelfX, 1.0f, shelfZ);
    glScalef(0.1f, 2.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng 1 (dưới cùng) - hướng về phía phải
    glPushMatrix();
    glTranslatef(shelfX + 0.3f,0.4f, shelfZ);
    glScalef(0.6f, 0.05f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng 2 (giữa) - hướng về phía trái  
    glPushMatrix();
    glTranslatef(shelfX - 0.2f,0.8f, shelfZ);
    glScalef(0.5f, 0.05f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng 3 (trên cùng) - hướng về phía phải
    glPushMatrix();
    glTranslatef(shelfX + 0.25f,1.2f, shelfZ);
    glScalef(0.5f, 0.05f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng 4 (cao nhất) - hướng về phía trái
    glPushMatrix();
    glTranslatef(shelfX - 0.15f,1.6f, shelfZ);
    glScalef(0.4f, 0.05f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Thêm các thanh ngang nối để tạo hình chữ S
    glColor3f(0.5f, 0.3f, 0.15f); // Màu gỗ đậm hơn

    // Thanh nối 1-2
    glPushMatrix();
    glTranslatef(shelfX + 0.05f,0.6f, shelfZ);
    glRotatef(20, 0, 0, 1);
    glScalef(0.35f, 0.03f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Thanh nối 2-3
    glPushMatrix();
    glTranslatef(shelfX + 0.025f,1.0f, shelfZ);
    glRotatef(-25, 0, 0, 1);
    glScalef(0.35f, 0.03f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Thanh nối 3-4
    glPushMatrix();
    glTranslatef(shelfX + 0.05f,1.4f, shelfZ);
    glRotatef(15, 0, 0, 1);
    glScalef(0.3f, 0.03f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Vẽ con cua đồ chơi trên các tầng kệ
    drawToyCrab(shelfX + 0.3f,0.5f, shelfZ, 0.4f);      // Tầng 1
    drawToyCrab(shelfX - 0.2f,0.9f, shelfZ, 0.35f);     // Tầng 2
    drawToyCrab(shelfX + 0.25f,1.3f, shelfZ, 0.3f);     // Tầng 3
    drawToyCrab(shelfX - 0.15f,1.7f, shelfZ, 0.25f);    // Tầng 4
}