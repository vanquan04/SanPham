#include "tructhang.h"

void drawBox(float sx, float sy, float sz) {
    glPushMatrix();
    glScalef(sx, sy, sz);
    glutSolidCube(1.0);
    glPopMatrix();
}

void paintColor(float r, float g, float b) {
    glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
}

void CacBoPhanTrucThang(float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rz) {
    glPushMatrix();
    glTranslatef(Tx, Ty, Tz);
    glRotatef(Rz, 0, 0, 1);
    drawBox(Sx, Sy, Sz);
    glPopMatrix();
}

void CanhQuatMB(float Sx, float Sy, float Sz, float Ry) {
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    glRotatef(Ry, 0, 1, 0);
    drawBox(Sx, Sy, Sz);
    glPopMatrix();
}

void drawTrucThang(float x, float y, float z, bool xemMau) {
    glPushMatrix();

    if (xemMau)
        glTranslatef(-0.13, -0.45, -0.1);
    else
        glTranslatef(x, y, z);

    glScalef(0.5, 0.5, 0.5);

    // ========== Thân máy bay ==========
    paintColor(105, 178, 236);
    CacBoPhanTrucThang(0, 0, 0, 1, 0.5, 0.5, 0);
    CacBoPhanTrucThang(-0.5, 0, 0, 0.3536, 0.3536, 0.5, 45);

    // ========== Thân phụ ==========
    paintColor(158, 216, 245);
    CacBoPhanTrucThang(0, -0.1, 0.3, 0.75, 0.05, 0.1, 0);
    CacBoPhanTrucThang(0, -0.1, -0.3, 0.75, 0.05, 0.1, 0);

    // ========== Cửa sổ ==========
    paintColor(0, 178, 24);
    CacBoPhanTrucThang(-0.25, 0.06, 0.25, 0.22, 0.3, 0.01, 0);
    CacBoPhanTrucThang(-0.25, 0.06, -0.25, 0.22, 0.3, 0.01, 0);
    CacBoPhanTrucThang(0.1, 0.06, 0.25, 0.22, 0.3, 0.01, 0);
    CacBoPhanTrucThang(0.1, 0.06, -0.25, 0.22, 0.3, 0.01, 0);
    CacBoPhanTrucThang(-0.63, 0.13, 0, 0.01, 0.2, 0.38, -45);

    // ========== Trụ và đuôi ==========
    paintColor(45, 150, 236);
    CacBoPhanTrucThang(0, 0.25, 0, 0.5, 0.25, 0.25, 0);
    CacBoPhanTrucThang(0, 0.4, 0, 0.07, 0.2, 0.07, 0);

    paintColor(105, 178, 236);
    CacBoPhanTrucThang(1, -0.05, 0, 1, 0.15, 0.1, 0);
    CacBoPhanTrucThang(1.2, -0.07, 0, 0.15, 0.01, 0.5, 0);
    CacBoPhanTrucThang(1.5, 0.07, 0, 0.4, 0.15, 0.05, 70);
    CacBoPhanTrucThang(1.5, -0.125, 0, 0.25, 0.15, 0.05, -70);
    CacBoPhanTrucThang(1.55, 0.16, 0.05, 0.02, 0.02, 0.1, 0);

    // ========== Chân càng ==========
    paintColor(86, 212, 110);
    CacBoPhanTrucThang(0.2, -0.3, 0.15, 0.05, 0.3, 0.05, 0);
    CacBoPhanTrucThang(-0.2, -0.3, 0.15, 0.05, 0.3, 0.05, 0);
    CacBoPhanTrucThang(0, -0.45, 0.15, 0.7, 0.05, 0.05, 0);
    CacBoPhanTrucThang(0.2, -0.3, -0.15, 0.05, 0.3, 0.05, 0);
    CacBoPhanTrucThang(-0.2, -0.3, -0.15, 0.05, 0.3, 0.05, 0);
    CacBoPhanTrucThang(0, -0.45, -0.15, 0.7, 0.05, 0.05, 0);

    // ========== Cánh quạt chính ==========
    paintColor(145, 152, 160);
    CanhQuatMB(2, 0.02, 0.05, g_rotorAngle);
    CanhQuatMB(2, 0.02, 0.05, g_rotorAngle + 90);

    // ========== Cánh quạt đuôi (xoay) ==========
    glPushMatrix();
    glTranslatef(1.55, 0.16, -0.4);
    glRotatef(90, 1, 0, 0);
    CanhQuatMB(2, 0.02, 0.125, g_rotorAngle);
    CanhQuatMB(2, 0.02, 0.15, g_rotorAngle + 90);
    glPopMatrix();

    glPopMatrix(); // Kết thúc model máy bay
}
