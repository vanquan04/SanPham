#include "glut.h"
#include "gau.h"
#include <math.h>

bool isStanding = false;
bool isMoving = false;
float bearX = 4.2f;
float bearY = 0.5f;
float bearZ = -4.4f;
float targetX = 0.0f;
float targetY = 0.01f;
float targetZ = 0.0f;
float moveSpeed = 0.02f;
float originalBearX = 4.2f;
float originalBearY = 0.5f;
float originalBearZ = -4.4f;
bool atCarpet = false; // Trạng thái gấu có ở thảm hay không

void updateBearPosition() {
    if (isMoving) {
        // Tính khoảng cách đến đích
        float dx = targetX - bearX;
        float dy = targetY - bearY;
        float dz = targetZ - bearZ;
        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        // Nếu đã gần đích thì dừng lại
        if (distance < 0.05f) { // Giảm ngưỡng từ 0.1f xuống 0.05f để chính xác hơn
            bearX = targetX;
            bearY = targetY;
            bearZ = targetZ;
            isMoving = false;
            isStanding = false; // Gấu ngồi xuống khi đến đích
        }
        else {
            // Di chuyển theo hướng đích với tốc độ phù hợp
            float normalizedSpeed = moveSpeed;
            if (distance < 1.0f) {
                // Chậm lại khi gần đích
                normalizedSpeed *= distance;
            }

            bearX += (dx / distance) * normalizedSpeed;
            bearY += (dy / distance) * normalizedSpeed;
            bearZ += (dz / distance) * normalizedSpeed;
        }
    }
}

void moveBearToTarget(float x, float y, float z) {
    targetX = x;
    targetY = y;
    targetZ = z;
    isMoving = true;
    isStanding = true; // Gấu đứng lên khi di chuyển
}

void moveBearToCarpet() {
    if (!atCarpet) {
        // Di chuyển đến thảm (tăng Y lên để không bị thấp)
        moveBearToTarget(0.0f, 0.8f, 0.0f); // Tăng Y từ 0.01f lên 0.3f
        atCarpet = true;
    }
    else {
        // Về vị trí ban đầu
        moveBearToTarget(originalBearX, originalBearY, originalBearZ);
        atCarpet = false;
    }
}

// Kiểm tra xem click có trúng gấu không
bool checkBearClick(float mouseX, float mouseY, float mouseZ, float radius) {
    float dx = mouseX - bearX;
    float dy = mouseY - bearY;
    float dz = mouseZ - bearZ;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance <= radius;
}

void drawToyBear(float x, float y, float z, float scale) {
    // Cập nhật vị trí nếu đang di chuyển
    if (isMoving) {
        updateBearPosition();
    }

    glPushMatrix();
    glTranslatef(bearX, bearY, bearZ);
    glScalef(scale, scale, scale);
    glColor3f(0.6f, 0.4f, 0.2f); // màu nâu

    // Thân
    glPushMatrix(); glTranslatef(0, 0, 0); glutSolidSphere(0.3f, 16, 12); glPopMatrix();

    // Đầu
    glPushMatrix(); glTranslatef(0, 0.4f, 0); glutSolidSphere(0.2f, 16, 12); glPopMatrix();

    // Tai
    glPushMatrix(); glTranslatef(-0.12f, 0.55f, 0); glutSolidSphere(0.07f, 10, 8); glPopMatrix();
    glPushMatrix(); glTranslatef(0.12f, 0.55f, 0); glutSolidSphere(0.07f, 10, 8); glPopMatrix();

    // Tay
    glPushMatrix();
    if (isStanding)
        glTranslatef(-0.25f, 0.15f, 0);  // cao hơn
    else
        glTranslatef(-0.25f, 0.05f, 0);  // bình thường
    glutSolidSphere(0.1f, 10, 8); glPopMatrix();

    glPushMatrix();
    if (isStanding)
        glTranslatef(0.25f, 0.15f, 0);
    else
        glTranslatef(0.25f, 0.05f, 0);
    glutSolidSphere(0.1f, 10, 8); glPopMatrix();

    // Chân
    glPushMatrix();
    if (isStanding)
        glTranslatef(-0.12f, -0.1f, 0); // thu chân lại
    else
        glTranslatef(-0.12f, -0.25f, 0);
    glutSolidSphere(0.1f, 10, 8); glPopMatrix();

    glPushMatrix();
    if (isStanding)
        glTranslatef(0.12f, -0.1f, 0);
    else
        glTranslatef(0.12f, -0.25f, 0);
    glutSolidSphere(0.1f, 10, 8); glPopMatrix();
    glColor3f(0, 0, 0);
    glPushMatrix(); glTranslatef(-0.05f, 0.45f, 0.17f); glutSolidSphere(0.025f, 8, 6); glPopMatrix();
    glPushMatrix(); glTranslatef(0.05f, 0.45f, 0.17f); glutSolidSphere(0.025f, 8, 6); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 0.4f, 0.2f); glutSolidSphere(0.03f, 8, 6); glPopMatrix();
    glPopMatrix();
}