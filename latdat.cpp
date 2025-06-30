#include "glut.h"
#include "latdat.h"

// Trạng thái gật gù: 0 = đứng, 1 = đổ trước, 2 = đổ sau
static int latDatState = 0;

// Chuyển đổi trạng thái
void toggleLatDatState() {
    latDatState = (latDatState + 1) % 3;
}

// Hàm vẽ 1 con lật đật
void drawLatDat(float x, float y, float z, float scale, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Góc gật gù dựa trên trạng thái
    float angle = 0.0f;
    if (latDatState == 1) angle = 20.0f;     // đổ trước
    else if (latDatState == 2) angle = -20.0f; // đổ sau

    glRotatef(angle, 1, 0, 0); // quay theo trục X
    glScalef(scale, scale, scale);

    // Thân
    glColor3f(r, g, b);
    glutSolidSphere(0.4, 30, 30);

    // Đầu
    glTranslatef(0.0, 0.5, 0.0);
    glColor3f(1.0, 0.8, 0.6); // màu da
    glutSolidSphere(0.2, 30, 30);

    // Mắt
    glPushMatrix();
    glTranslatef(-0.06, 0.05, 0.18);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.025, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.06, 0.05, 0.18);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.025, 10, 10);
    glPopMatrix();

    glPopMatrix();
}

// Vẽ toàn bộ 5 con lật đật
void drawAllLatDat() {
    drawLatDat(-3.5f, 0.4f, -4.0f, 0.5f, 1.0f, 0.2f, 0.2f); // đỏ
    drawLatDat(-2.3f, 0.4f, -4.0f, 0.6f, 0.2f, 0.6f, 1.0f); // xanh dương
    drawLatDat(-1.0f, 0.4f, -4.0f, 0.7f, 0.2f, 1.0f, 0.3f); // xanh lá
    drawLatDat(0.5f, 0.4f, -4.0f, 0.8f, 1.0f, 1.0f, 0.2f); // vàng
    drawLatDat(2.0f, 0.4f, -4.0f, 1.0f, 1.0f, 0.4f, 1.0f); // tím
}