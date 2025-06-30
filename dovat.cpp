#include "glut.h"
#include <math.h>
#include <stdio.h>
#include "dovat.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Biến toàn cục cho đồng hồ
float clockAngleHour = 0.0f;    // Kim giờ
float clockAngleMinute = 0.0f;  // Kim phút
float clockAngleSecond = 0.0f;  // Kim giây
float clockTime = 0.0f;         // Thời gian ảo

// Biến toàn cục cho quạt
float fanAngle = 0.0f;          // Góc quay của cánh quạt
bool fanRunning = false;        // Trạng thái quạt

// Hàm cập nhật thời gian đồng hồ
void updateClock() {
    clockTime += 0.001f; // Tăng thời gian ảo

    // Cập nhật góc quay các kim
    clockAngleSecond = fmod(clockTime * 6.0f, 360.0f);           // Kim giây quay nhanh
    clockAngleMinute = fmod(clockTime * 0.1f, 360.0f);          // Kim phút quay chậm hơn
    clockAngleHour = fmod(clockTime * 0.00833f, 360.0f);        // Kim giờ quay chậm nhất
}

// Hàm cập nhật quạt
void updateFan() {
    if (fanRunning) {
        fanAngle += 8.0f; // Tốc độ quay quạt
        if (fanAngle >= 360.0f) {
            fanAngle -= 360.0f;
        }
    }
}

// Hàm vẽ đồng hồ treo tường
void drawWallClock() {
    glPushMatrix();
    glTranslatef(-4.8f, 3.5f, 2.0f); // Vị trí trên tường trái
    glRotatef(90.0f, 0, 1, 0); // Xoay để hướng vào phòng

    // Vẽ khung đồng hồ (màu nâu gỗ)
    glColor3f(0.4f, 0.2f, 0.1f);
    glPushMatrix();
    glScalef(0.8f, 0.8f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Vẽ mặt đồng hồ (màu trắng)
    glColor3f(0.95f, 0.95f, 0.95f);
    glPushMatrix();
    glTranslatef(0, 0, 0.06f);
    glScalef(0.7f, 0.7f, 0.02f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Vẽ các số trên đồng hồ (12 chấm nhỏ)
    glColor3f(0.1f, 0.1f, 0.1f);
    for (int i = 0; i < 12; i++) {
        glPushMatrix();
        float angle = i * 30.0f * M_PI / 180.0f;
        float x = 0.28f * sin(angle);
        float y = 0.28f * cos(angle);
        glTranslatef(x, y, 0.08f);
        glutSolidSphere(0.02f, 8, 8);
        glPopMatrix();
    }

    // Tâm đồng hồ
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0, 0, 0.09f);
    glutSolidSphere(0.03f, 12, 12);
    glPopMatrix();

    // Kim giờ (ngắn, dày)
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 0, 0.1f);
    glRotatef(-clockAngleHour, 0, 0, 1);
    glTranslatef(0, 0.12f, 0);
    glScalef(0.02f, 0.24f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kim phút (dài hơn, mỏng hơn)
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 0, 0.1f);
    glRotatef(-clockAngleMinute, 0, 0, 1);
    glTranslatef(0, 0.18f, 0);
    glScalef(0.015f, 0.36f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kim giây (đỏ, rất mỏng)
    glColor3f(0.8f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 0, 0.11f);
    glRotatef(-clockAngleSecond, 0, 0, 1);
    glTranslatef(0, 0.22f, 0);
    glScalef(0.005f, 0.44f, 0.005f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

// Hàm vẽ kệ tủ đồ chơi
void drawToyShelf() {
    glPushMatrix();
    glTranslatef(4.5f, 0.0f, 2.0f); // Góc trái tường

    // Khung tủ chính (màu gỗ sáng)
    glColor3f(0.7f, 0.5f, 0.3f);

    // Mặt sau của tủ
    glPushMatrix();
    glTranslatef(0.25f, 1.0f, 0);
    glScalef(0.1f, 2.0f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Hai bên tủ
    glPushMatrix();
    glTranslatef(0, 1.0f, -0.55f);
    glScalef(0.6f, 2.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.0f, 0.55f);
    glScalef(0.6f, 2.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Các tầng kệ (4 tầng)
    glColor3f(0.6f, 0.4f, 0.2f);
    for (int i = 0; i <= 4; i++) {
        glPushMatrix();
        glTranslatef(0, i * 0.5f, 0);
        glScalef(0.6f, 0.05f, 1.2f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }


    // Tầng 1 (kệ ở y = 0.5): Xe hơi nhỏ
    glColor3f(0.8f, 0.2f, 0.2f); // Đỏ
    glPushMatrix();
    glTranslatef(-0.15f, 0.54f, -0.2f); // Sửa từ 0.3f thành 0.54f (0.5 + 0.025 + 0.04)
    glScalef(0.15f, 0.08f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Bánh xe
    glColor3f(0.1f, 0.1f, 0.1f);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        float x = (i < 2) ? -0.2f : -0.1f;
        float z = (i % 2 == 0) ? -0.32f : -0.08f;
        glTranslatef(x, 0.50f, z); // Sửa từ 0.26f thành 0.50f (để bánh xe chạm đất kệ)
        glutSolidTorus(0.02f, 0.04f, 8, 12);
        glPopMatrix();
    }

    // Tầng 1: Robot nhỏ
    glColor3f(0.4f, 0.4f, 0.8f); // Xanh dương
    glPushMatrix();
    glTranslatef(-0.15f, 0.60f, 0.2f); // Sửa từ 0.35f thành 0.60f (0.5 + 0.025 + 0.1)
    glScalef(0.12f, 0.2f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Đầu robot
    glColor3f(0.3f, 0.3f, 0.7f);
    glPushMatrix();
    glTranslatef(-0.15f, 0.75f, 0.2f); // Sửa từ 0.42f thành 0.75f
    glutSolidSphere(0.05f, 12, 12);
    glPopMatrix();

    // Tầng 2 (kệ ở y = 1.0): Khối lego
    glColor3f(0.2f, 0.8f, 0.2f); // Xanh lá
    glPushMatrix();
    glTranslatef(-0.15f, 1.10f, -0.25f); // Sửa từ 0.8f thành 1.10f (1.0 + 0.025 + 0.075)
    glScalef(0.2f, 0.15f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Chấm trên lego
    glColor3f(0.1f, 0.7f, 0.1f);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        float x = -0.15f + ((i % 2) - 0.5f) * 0.08f;
        float z = -0.25f + ((i / 2) - 0.5f) * 0.08f;
        glTranslatef(x, 1.175f, z); // Sửa từ 0.88f thành 1.175f
        glPopMatrix();
    }

    // Tầng 2: Bóng nhỏ
    glColor3f(0.9f, 0.7f, 0.1f); // Vàng
    glPushMatrix();
    glTranslatef(-0.15f, 1.095f, 0.0f); // Sửa từ 0.8f thành 1.095f (1.0 + 0.025 + 0.07)
    glutSolidSphere(0.07f, 16, 16);
    glPopMatrix();

    // Tầng 2: Rubik cube
    glColor3f(0.8f, 0.1f, 0.8f); // Tím
    glPushMatrix();
    glTranslatef(-0.15f, 1.085f, 0.25f); // Sửa từ 0.8f thành 1.085f (1.0 + 0.025 + 0.06)
    glScalef(0.12f, 0.12f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng 3 (kệ ở y = 1.5): Máy bay nhỏ
    glColor3f(0.1f, 0.6f, 0.8f); // Xanh da trời
    glPushMatrix();
    glTranslatef(-0.15f, 1.55f, -0.1f); // Sửa từ 1.3f thành 1.55f (1.5 + 0.025 + 0.025)

    // Thân máy bay
    glScalef(0.08f, 0.05f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Cánh máy bay
    glColor3f(0.0f, 0.5f, 0.7f);
    glPushMatrix();
    glTranslatef(-0.15f, 1.55f, -0.1f); // Sửa từ 1.3f thành 1.55f
    glScalef(0.25f, 0.02f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng 3: Tàu thuyền nhỏ
    glColor3f(0.6f, 0.3f, 0.1f); // Nâu
    glPushMatrix();
    glTranslatef(-0.15f, 1.565f, 0.2f); // Sửa từ 1.3f thành 1.565f (1.5 + 0.025 + 0.04)
    glScalef(0.2f, 0.08f, 0.12f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Cột buồm
    glColor3f(0.4f, 0.2f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.15f, 1.665f, 0.2f); // Sửa từ 1.42f thành 1.665f
    glScalef(0.01f, 0.2f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tầng 4 (kệ ở y = 2.0): Sách và đồ chơi nhỏ
    glColor3f(0.8f, 0.6f, 0.2f); // Cam
    glPushMatrix();
    glTranslatef(-0.15f, 2.115f, -0.3f); // Sửa từ 1.8f thành 2.115f (2.0 + 0.025 + 0.09)
    glScalef(0.15f, 0.18f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.2f, 0.4f, 0.8f); // Xanh
    glPushMatrix();
    glTranslatef(-0.15f, 2.115f, -0.2f); // Sửa từ 1.8f thành 2.115f
    glScalef(0.15f, 0.18f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.6f, 0.2f, 0.4f); // Hồng
    glPushMatrix();
    glTranslatef(-0.15f, 2.115f, -0.1f); // Sửa từ 1.8f thành 2.115f
    glScalef(0.15f, 0.18f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Búp bê nhỏ
    glColor3f(0.9f, 0.7f, 0.6f); // Màu da
    glPushMatrix();
    glTranslatef(-0.15f, 2.065f, 0.1f); // Sửa từ 1.85f thành 2.065f (2.0 + 0.025 + 0.04)
    glutSolidSphere(0.04f, 12, 12);
    glPopMatrix();

    // Thân búp bê
    glColor3f(0.8f, 0.2f, 0.6f); // Hồng
    glPushMatrix();
    glTranslatef(-0.15f, 2.085f, 0.1f); // Sửa từ 1.78f thành 2.085f (2.0 + 0.025 + 0.06)
    glScalef(0.06f, 0.12f, 0.06f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

// Hàm vẽ chậu hoa
void drawFlowerPot() {
    glPushMatrix();
    glTranslatef(-4.5f, 0.0f, 4.5f); // Di chuyển để tránh trùng với kệ

    // Vẽ chậu (màu đất nung)
    glColor3f(0.6f, 0.3f, 0.2f);
    glPushMatrix();
    glTranslatef(0, 0.3f, 0);
    glScalef(0.4f, 0.6f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Đất trong chậu (màu nâu đậm)
    glColor3f(0.3f, 0.2f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 0.55f, 0);
    glScalef(0.35f, 0.1f, 0.35f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Thân cây (màu xanh lá)
    glColor3f(0.2f, 0.6f, 0.2f);
    glPushMatrix();
    glTranslatef(0, 0.8f, 0);
    glScalef(0.05f, 0.4f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Lá cây (5 lá xanh)
    glColor3f(0.1f, 0.7f, 0.1f);
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        float angle = i * 72.0f;
        glTranslatef(0, 1.0f, 0);
        glRotatef(angle, 0, 1, 0);
        glTranslatef(0.15f, 0, 0);
        glRotatef(45.0f, 0, 0, 1);
        glScalef(0.25f, 0.1f, 0.02f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Hoa (3 bông hoa đỏ)
    glColor3f(0.9f, 0.2f, 0.2f);
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        float angle = i * 120.0f;
        glTranslatef(0, 1.2f, 0);
        glRotatef(angle, 0, 1, 0);
        glTranslatef(0.12f, 0, 0);
        glutSolidSphere(0.06f, 12, 12);
        glPopMatrix();
    }

    glPopMatrix();
}

// Hàm vẽ quạt góc phòng
void drawCornerFan() {
    glPushMatrix();
    glTranslatef(4.5f, 0.0f, 4.3f); // Góc phòng đối diện

    // Chân đế quạt (màu xám)
    glColor3f(0.4f, 0.4f, 0.4f);
    glPushMatrix();
    glTranslatef(0, 0.1f, 0);
    glScalef(0.6f, 0.2f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Trụ quạt
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0, 0.8f, 0);
    glScalef(0.08f, 1.4f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Đầu quạt (motor)
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0, 1.5f, 0);
    glutSolidSphere(0.15f, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.5f, 0);
    glRotatef(180.0f, 0, 1, 0); // Xoay mặt quạt ra phía phòng (trục Y)

    // Cục motor nhô ra
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0.1f, 0, 0); // Nhô ra phía trước
    glScalef(0.3f, 0.15f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Cánh quạt
    glColor3f(1.0f, 0.8f, 0.2f);
    glPushMatrix();
    glTranslatef(0.2f, 0, 0); // Dịch cánh quạt ra ngoài cục motor
    glRotatef(fanAngle, 1, 0, 0); // Quay quanh trục X (thổi ngang)

    // 3 cánh quạt
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 1, 0, 0);
        glTranslatef(0, 0.3f, 0);
        glScalef(0.02f, 0.6f, 0.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix();
    glPopMatrix();

    // Nút điều khiển trên thân quạt
    glColor3f(0.6f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0.06f, 1.0f, 0);
    glutSolidSphere(0.03f, 8, 8);
    glPopMatrix();

    glPopMatrix();
}

// Hàm cập nhật tất cả đồ vật
void updateDoVat() {
    updateClock();
    updateFan();
}

// Hàm vẽ tất cả đồ vật
void drawAllDoVat() {
    drawWallClock();
    drawFlowerPot();
    drawCornerFan();
    drawToyShelf();  // Thêm kệ đồ chơi
}

// Hàm bật/tắt quạt
void toggleFan() {
    fanRunning = !fanRunning;
}