#include "cua.h"

// H�m v? m?t c�ng cua
void drawClaw(bool isLeft) {
    float dir = isLeft ? -1.0f : 1.0f;

    // C�nh tay n?i t? th�n ch�n c�ng
    glPushMatrix();
    glTranslatef(dir * 0.35f, 0.05f, 0.2f);
    glRotatef(dir * 30, 0, 0, 1);
    glScalef(0.25f, 0.08f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Ph?n c�ng ch�nh (h�nh kh?i l?n)
    glPushMatrix();
    glTranslatef(dir * 0.55f, 0.1f, 0.2f);
    glRotatef(dir * 20, 0, 0, 1);
    glScalef(0.25f, 0.08f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // M?i k?p tr�n
    glPushMatrix();
    glTranslatef(dir * 0.65f, 0.16f, 0.2f);
    glRotatef(dir * 25, 0, 0, 1);
    glScalef(0.15f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // M?i k?p d??i
    glPushMatrix();
    glTranslatef(dir * 0.65f, 0.04f, 0.2f);
    glRotatef(dir * -25, 0, 0, 1);
    glScalef(0.15f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// H�m v? con cua
void drawToyCrab(float x, float y, float z, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);

    // Th�n cua
    glColor3f(1.0f, 0.4f, 0.2f);
    glPushMatrix();
    glScalef(1.2f, 0.6f, 0.8f);
    glutSolidSphere(0.3f, 20, 16);
    glPopMatrix();

    // C�ng cua
    glColor3f(1.0f, 0.3f, 0.1f);
    drawClaw(true);  // b�n tr�i
    drawClaw(false); // b�n ph?i

    // Ch�n cua - 6 ch�n m?i b�n
    glColor3f(0.8f, 0.3f, 0.1f);
    for (int i = 0; i < 3; i++) {
        float legZ = -0.2f + i * 0.2f;

        // Ch�n tr�i
        glPushMatrix();
        glTranslatef(-0.35f, -0.25f, legZ);
        glRotatef(30, 0, 0, 1);
        glScalef(0.3f, 0.05f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Ch�n ph?i
        glPushMatrix();
        glTranslatef(0.35f, -0.25f, legZ);
        glRotatef(-30, 0, 0, 1);
        glScalef(0.3f, 0.05f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // M?t cua
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.15f, 0.2f, 0.25f);
    glutSolidSphere(0.05f, 8, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15f, 0.2f, 0.25f);
    glutSolidSphere(0.05f, 8, 6);
    glPopMatrix();

    glPopMatrix();
}
