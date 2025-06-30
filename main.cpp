#include "glut.h"
#include <math.h>
#include <stdio.h>
#include "ketu.h"
#include "cua.h"
#include "gau.h"
#include "tructhang.h"
#include "bong.h"
#include "tham.h"
#include "dovat.h"
#include "banghe.h"
#include "latdat.h"
#include "anh.h"
#include "khunganh.h"
#include "xe.h"
#include "Car.h"
#include "dieuhoa.h"
#include "thungrac.h"

AirConditioner myAC;
thungrac mythungrac;
// Khai báo global
Car myCar;

GLuint photoTexture;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* ----------  Biến cửa sổ  ---------- */
float windowAngle = 0.0f;
bool windowOpening = false;

//Biến cho cánh máy bay quay
float g_rotorAngle = 0.0f;     // Góc quay hiện tại
bool g_spinRotor = false;      // Cờ bật tắt quay


/* ----------  Camera & Chuyển động  ---------- */
float cameraX = 0.0f, cameraY = 2.5f, cameraZ = 5.0f;
float yaw = -90.0f;                 // xoay ngang
float pitch = 0.0f;                 // xoay dọc
float dirX, dirY, dirZ;             // hướng nhìn
const float moveSpeed = 0.5f;
const float turnSpeed = 1.0f;
const float upDownSpeed = 0.5f;

// Biến trạng thái phím
bool keyStates[256] = { false };
bool specialKeyStates[256] = { false };

/* ----------  Ánh sáng  ---------- */
const float lightX = 0.0f, lightY = 4.8f, lightZ = 0.0f;
const float windowLightX = 0.0f, windowLightY = 2.5f, windowLightZ = 4.9f;
const float monitorLightX = 4.7f, monitorLightY = 1.8f, monitorLightZ = -2.0f;
bool lightOn = true;
bool windowLightOn = true;
bool monitorLightOn = true;

float ambientLevel = 0.2f; // Mức ánh sáng môi trường có thể điều chỉnh

/* ----------  Hàm tiện ích  ---------- */
void updateDirection() {
    dirX = cosf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
    dirY = sinf(pitch * M_PI / 180.0f);
    dirZ = sinf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
}

/* ----------  Khởi tạo  ---------- */
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);

    // Load texture cho khung ảnh
    photoTexture = loadTexture("a3.jpg"); // Thay "photo.jpg" bằng tên file ảnh của bạn
    if (photoTexture == 0) {
        printf("⚠️ Cảnh báo: Không thể load texture khung ảnh\n");
    }

    updateDirection();
}

/* ----------  Cập nhật nguồn sáng  ---------- */
void updateLight() {
    // Cài đặt ánh sáng môi trường toàn cục
    GLfloat globalAmbient[] = { ambientLevel, ambientLevel, ambientLevel, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // Nguồn sáng chính từ đèn trần (GL_LIGHT0) - ĐÃ GIẢM ĐỘ SÁNG
    GLfloat light0_position[] = { lightX, lightY, lightZ, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    if (lightOn) {
        // Giảm ambient từ 0.3f xuống 0.15f
        GLfloat ambient0[] = { 0.15f, 0.15f, 0.15f, 1.0f };
        // Giảm diffuse từ 1.0f xuống 0.6f (giảm 40%)
        GLfloat diffuse0[] = { 0.6f, 0.6f, 0.54f, 1.0f };
        // Giảm specular từ 1.0f xuống 0.5f
        GLfloat specular0[] = { 0.5f, 0.5f, 0.45f, 1.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

        // Tăng attenuation để ánh sáng yếu hơn theo khoảng cách
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.6f);    // Tăng từ 0.4f
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);     // Tăng từ 0.03f
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.008f); // Tăng từ 0.005f

        glEnable(GL_LIGHT0);
    }
    else {
        GLfloat zero0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT, zero0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, zero0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, zero0);
        glDisable(GL_LIGHT0);
    }

    // Nguồn sáng từ cửa sổ (GL_LIGHT1) - hoạt động khi cửa sổ mở và windowLightOn = true
    GLfloat light1_position[] = { windowLightX, windowLightY, windowLightZ, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    if (windowLightOn && windowOpening && windowAngle > 10.0f) {
        float windowIntensity = windowAngle / 90.0f; // Cường độ tùy theo góc mở
        GLfloat ambient1[] = { 0.1f * windowIntensity, 0.1f * windowIntensity, 0.15f * windowIntensity, 1.0f };
        GLfloat diffuse1[] = { 0.8f * windowIntensity, 0.8f * windowIntensity, 1.0f * windowIntensity, 1.0f };
        GLfloat specular1[] = { 0.6f * windowIntensity, 0.6f * windowIntensity, 0.8f * windowIntensity, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.3f);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.08f);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.015f);
        glEnable(GL_LIGHT1);
    }
    else {
        GLfloat zero1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT, zero1);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, zero1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, zero1);
        glDisable(GL_LIGHT1);
    }

    // Nguồn sáng màn hình (GL_LIGHT2)
   /* GLfloat light2_position[] = { monitorLightX, monitorLightY, monitorLightZ, 1.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    if (monitorLightOn) {
        GLfloat ambient2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat diffuse2[] = { 0.9f, 0.6f, 0.6f, 1.0f };
        GLfloat specular2[] = { 0.7f, 0.4f, 0.4f, 1.0f };
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
        glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.4f);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.08f);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.01f);
        glEnable(GL_LIGHT2);
    }
    else {
        GLfloat zero2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT2, GL_AMBIENT, zero2);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, zero2);
        glLightfv(GL_LIGHT2, GL_SPECULAR, zero2);
        glDisable(GL_LIGHT2);
    }*/
}

/* ----------  Vẽ bóng đèn  ---------- */
void drawLightBulb() {
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(lightX, lightY, lightZ);

    // Vẽ đèn trần hình vuông
    if (lightOn)
        glColor3f(1.0f, 1.0f, 0.6f);  // Màu vàng sáng khi bật
    else
        glColor3f(0.4f, 0.4f, 0.4f);  // Màu xám tối khi tắt

    // Thân đèn trần (hình hộp chữ nhật mỏng)
    glPushMatrix();
    glScalef(0.8f, 0.1f, 0.8f);  // Rộng 0.8, cao 0.1, dài 0.8
    glutSolidCube(1.0);
    glPopMatrix();

    // Viền đèn (khung bao quanh)
    glColor3f(0.8f, 0.8f, 0.8f);  // Màu bạc cho viền

    // Viền trên
    glPushMatrix();
    glTranslatef(0, 0.06f, 0.4f);
    glScalef(0.85f, 0.02f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Viền dưới
    glPushMatrix();
    glTranslatef(0, 0.06f, -0.4f);
    glScalef(0.85f, 0.02f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Viền trái
    glPushMatrix();
    glTranslatef(-0.4f, 0.06f, 0);
    glScalef(0.05f, 0.02f, 0.85f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Viền phải
    glPushMatrix();
    glTranslatef(0.4f, 0.06f, 0);
    glScalef(0.05f, 0.02f, 0.85f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Thêm hiệu ứng ánh sáng khi đèn bật
    if (lightOn) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 0.8f, 0.3f);  // Màu vàng trong suốt

        // Hào quang xung quanh đèn
        glPushMatrix();
        glTranslatef(0, -0.02f, 0);
        glScalef(1.0f, 0.05f, 1.0f);
        glutSolidCube(1.0);
        glPopMatrix();

        glDisable(GL_BLEND);
    }

    glPopMatrix();
    glPopAttrib();
}

/* ----------  Vẽ cửa sổ  ---------- */
void drawWindow() {
    float winWidth = 2.8f, winHeight = 2.3f;
    float winY = 2.5f;
    float winX = 0.0f, winZ = 4.95f;

    glPushMatrix();
    glTranslatef(winX, winY, winZ);

    // Khung cửa sổ
    glColor3f(0.4f, 0.2f, 0.1f); // Màu nâu gỗ

    // Khung trên
    glPushMatrix();
    glTranslatef(0, winHeight / 2, 0);
    glScalef(winWidth + 0.2f, 0.1f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Khung dưới
    glPushMatrix();
    glTranslatef(0, -winHeight / 2, 0);
    glScalef(winWidth + 0.2f, 0.1f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Khung trái
    glPushMatrix();
    glTranslatef(-winWidth / 2 - 0.05f, 0, 0);
    glScalef(0.1f, winHeight, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Khung phải
    glPushMatrix();
    glTranslatef(winWidth / 2 + 0.05f, 0, 0);
    glScalef(0.1f, winHeight, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kính cửa sổ (trong suốt xanh nhạt)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.7f, 0.9f, 1.0f, 0.3f);

    glPushMatrix();
    glRotatef(windowAngle, 0, 1, 0); // Xoay cửa sổ
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(-winWidth / 2, -winHeight / 2, 0);
    glVertex3f(winWidth / 2, -winHeight / 2, 0);
    glVertex3f(winWidth / 2, winHeight / 2, 0);
    glVertex3f(-winWidth / 2, winHeight / 2, 0);
    glEnd();
    glPopMatrix();

    glDisable(GL_BLEND);
    glPopMatrix();
}
//Hàm quay máy bay
void update() {
    if (g_spinRotor) {
        g_rotorAngle += 5.0f;
        if (g_rotorAngle >= 360.0f)
            g_rotorAngle -= 360.0f;
        glutPostRedisplay();
    }

    // Cập nhật vị trí gấu nếu đang di chuyển
    if (isMoving) {
        updateBearPosition();
        glutPostRedisplay();
    }

    updateDoVat(); // Cập nhật đồng hồ và quạt
}

/* ----------  Cập nhật vị trí camera  ---------- */
void updateCamera() {
    float dirXxz = cosf(yaw * M_PI / 180.0f);
    float dirZxz = sinf(yaw * M_PI / 180.0f);
    if (keyStates['w'] || keyStates['W']) {
        cameraX += dirXxz * moveSpeed;
        cameraZ += dirZxz * moveSpeed;
    }
    if (keyStates['s'] || keyStates['S']) {
        cameraX -= dirXxz * moveSpeed;
        cameraZ -= dirZxz * moveSpeed;
    }
    if (keyStates['d'] || keyStates['D']) {
        cameraX -= dirZxz * moveSpeed;
        cameraZ += dirXxz * moveSpeed;
    }
    if (keyStates['a'] || keyStates['A']) {
        cameraX += dirZxz * moveSpeed;
        cameraZ -= dirXxz * moveSpeed;
    }

    // Di chuyển lên/xuống (Q/E)
    if (keyStates['q'] || keyStates['Q'])
        cameraY += upDownSpeed;
    if (keyStates['e'] || keyStates['E'])
        cameraY -= upDownSpeed;

    // Giới hạn camera
    if (cameraY < 0.5f) cameraY = 0.5f;
    if (cameraY > 4.5f) cameraY = 4.5f;
    if (cameraX < -4.5f) cameraX = -4.5f;
    if (cameraX > 4.5f) cameraX = 4.5f;
    if (cameraZ < -4.5f) cameraZ = -4.5f;
    if (cameraZ > 4.5f) cameraZ = 4.5f;

    // Cập nhật góc cửa sổ
    if (windowOpening && windowAngle < 90.0f)
        windowAngle += 1.0f;
    if (!windowOpening && windowAngle > 0.0f)
        windowAngle -= 1.0f;

    // Xoay camera bằng phím mũi tên
    if (specialKeyStates[GLUT_KEY_LEFT])
        yaw -= turnSpeed;
    if (specialKeyStates[GLUT_KEY_RIGHT])
        yaw += turnSpeed;
    if (specialKeyStates[GLUT_KEY_UP]) {
        pitch += turnSpeed;
        if (pitch > 89) pitch = 89;
    }
    if (specialKeyStates[GLUT_KEY_DOWN]) {
        pitch -= turnSpeed;
        if (pitch < -89) pitch = -89;
    }

    updateDirection();
}

/* ----------  Xử lý phím nhấn  ---------- */
void keyboard(unsigned char key, int x, int y) {
    keyStates[key] = true;
    if (key == '1' || key == '2' || key == '3' || key == '4') {
        updateXeCanCauTransform(key);
    }
    // Điều khiển đèn
    if (key == 'l' || key == 'L')
        lightOn = !lightOn;
    if (key == 'o' || key == 'O')
        windowOpening = !windowOpening;
    if (key == 'm' || key == 'M')
        monitorLightOn = !monitorLightOn;
    if (key == 'n' || key == 'N')
        windowLightOn = !windowLightOn;
    if (key == 'i' || key == 'I')
        isStanding = !isStanding; // chuyển đổi giữa đứng và ngồi
    if (key == 'k' || key == 'K')
        g_spinRotor = !g_spinRotor; // Bật/tắt quay
    if (key == 'f' || key == 'F')
        toggleFan(); // Bật/tắt quạt
    if (key == 'z' || key == 'Z')
        toggleLatDatState(); // Bật/tắt trạng thái lật đật
    if (key == 'y' || key == 'Y')// Bật/tắt điều hòa
         if (myAC.getState()) myAC.turnOff();
         else myAC.turnOn();
    // Điều khiển ánh sáng môi trường
    if (key == '+' || key == '=') {
        ambientLevel += 0.05f;
        if (ambientLevel > 1.0f) ambientLevel = 1.0f;
        printf("Ambient light level: %.2f\n", ambientLevel);
    }
    if (key == '-' || key == '_') {
        ambientLevel -= 0.05f;
        if (ambientLevel < 0.0f) ambientLevel = 0.0f;
        printf("Ambient light level: %.2f\n", ambientLevel);
    }

    glutPostRedisplay();
}

void drawDoor() {
    const float doorWidth = 1.5f;
    const float doorHeight = 3.0f;
    const float doorThickness = 0.05f; // Độ dày cửa

    glPushMatrix();

    // Đặt vị trí trên tường trái và xoay để cửa hướng vào trong phòng
    glTranslatef(-4.8f, 0.0f, -2.5f);
    glRotatef(90.0f, 0, 1, 0); // Xoay cửa để đối mặt vào phòng

    glTranslatef(-0.1f, 0.0f, 0.0f); // Di chuyển trục quay đến bản lề (nếu cần dùng để xoay)

    glColor3f(0.55f, 0.27f, 0.07f); // Màu gỗ nâu


    // Mặt trước
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, doorHeight, 0.0f);
    glVertex3f(doorWidth, doorHeight, 0.0f);
    glVertex3f(doorWidth, 0.0f, 0.0f);
    glEnd();

    // Mặt sau
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(doorWidth, 0.0f, -doorThickness);
    glVertex3f(doorWidth, doorHeight, -doorThickness);
    glVertex3f(0.0f, doorHeight, -doorThickness);
    glVertex3f(0.0f, 0.0f, -doorThickness);
    glEnd();

    // Mặt trái
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(0.0f, 0.0f, -doorThickness);
    glVertex3f(0.0f, doorHeight, -doorThickness);
    glVertex3f(0.0f, doorHeight, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // Mặt phải
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(doorWidth, 0.0f, 0.0f);
    glVertex3f(doorWidth, doorHeight, 0.0f);
    glVertex3f(doorWidth, doorHeight, -doorThickness);
    glVertex3f(doorWidth, 0.0f, -doorThickness);
    glEnd();

    // Mặt trên
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(0.0f, doorHeight, 0.0f);
    glVertex3f(0.0f, doorHeight, -doorThickness);
    glVertex3f(doorWidth, doorHeight, -doorThickness);
    glVertex3f(doorWidth, doorHeight, 0.0f);
    glEnd();

    // Mặt dưới
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(doorWidth, 0.0f, 0.0f);
    glVertex3f(doorWidth, 0.0f, -doorThickness);
    glVertex3f(0.0f, 0.0f, -doorThickness);
    glEnd();

    // Vẽ tay nắm cửa (nằm trên mặt trước)
    glPushMatrix();
    glTranslatef(1.f, 1.2f, 0.05f); // Xê dịch tay nắm theo độ dày cửa
    glColor3f(1.0f, 0.84f, 0.0f);    // Vàng kim loại
    glutSolidSphere(0.07f, 20, 20);
    glPopMatrix();

    glPopMatrix();
}


/* ----------  Vẽ phòng  ---------- */
void drawRoom(void) {
    updateCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,
        cameraX + dirX, cameraY + dirY, cameraZ + dirZ,
        0.0, 1.0, 0.0);
    updateLight();

    /* --- Sàn --- */
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-5, 0, -5); glVertex3f(-5, 0, 5);
    glVertex3f(5, 0, 5);   glVertex3f(5, 0, -5);
    glEnd();

    /* --- Trần --- */
    glColor3f(0.7, 0.9, 0.9);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(-5, 5, -5); glVertex3f(-5, 5, 5);
    glVertex3f(5, 5, 5);   glVertex3f(5, 5, -5);
    glEnd();

    /* --- Tường trái --- */
    glColor3f(1.0, 1.0, 0.9);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(-5, 0, -5); glVertex3f(-5, 5, -5);
    glVertex3f(-5, 5, 5);  glVertex3f(-5, 0, 5);
    glEnd();
	drawDoor(); // Vẽ cửa ở tường trái

    /* --- Tường phải --- */
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(5, 0, -5);  glVertex3f(5, 5, -5);
    glVertex3f(5, 5, 5);   glVertex3f(5, 0, 5);
    glEnd();

    /* --- Tường sau --- */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-5, 0, -5); glVertex3f(-5, 5, -5);
    glVertex3f(5, 5, -5);  glVertex3f(5, 0, -5);
    glEnd();

    /* --- Tường trước (có cửa sổ) --- */
    glColor3f(1.0, 0.95, 0.9);

    // Lấy thông số từ drawWindow()
    float winWidth = 2.8f, winHeight = 2.3f;
    float winY = 2.5f;
    float winX = 0.0f, winZ = 4.95f;
    float winLeft = -winWidth / 2;   
    float winRight = winWidth / 2;   
    float winBottom = winY - winHeight / 2;  
    float winTop = winY + winHeight / 2;     

    // Phần trái của tường
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(-5, 0, 5);
    glVertex3f(-5, 5, 5);
    glVertex3f(winLeft, 5, 5);
    glVertex3f(winLeft, 0, 5);
    glEnd();

    // Phần phải của tường
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(winRight, 0, 5);
    glVertex3f(winRight, 5, 5);
    glVertex3f(5, 5, 5);
    glVertex3f(5, 0, 5);
    glEnd();

    // Phần trên cửa sổ
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(winLeft, winTop, 5);
    glVertex3f(winLeft, 5, 5);
    glVertex3f(winRight, 5, 5);
    glVertex3f(winRight, winTop, 5);
    glEnd();

    // Phần dưới cửa sổ
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(winLeft, 0, 5);
    glVertex3f(winLeft, winBottom, 5);
    glVertex3f(winRight, winBottom, 5);
    glVertex3f(winRight, 0, 5);
    glEnd();

	
    // Vẽ các đối tượng
    drawLightBulb();
    drawWindow();
    drawXeMayXuc();
    drawPictureFrame();
    // Vẽ kệ hình chữ S
    drawSShapedShelf();
	// Vẽ gấu bông
    drawToyBear(4.2f, 0.5f, -4.4f, 2.0f);
	//Vẽ trực thăng
    drawTrucThang(-3.1f, 0.68f, 3.25f, false);
	//Vẽ quả bóng
    setBallPosition(2.0f, 0.4f, -2.0f); // Set trước
    drawBall(); // Gọi trong drawRoom hoặc display
    drawBanGheSofa();
	drawTham();
    drawAllDoVat();
    drawAllLatDat();
    //myCar.draw();

    // Vẽ điều hòa
    glPushMatrix();
    glTranslatef(0.0f, 4.5f, 4.9f);  
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    myAC.setSize(2.0f, 0.5f, 0.5f);
    myAC.setBodyColor(1.0f, 1.0f, 1.0f);
    myAC.setVentColor(0.3f, 0.3f, 0.3f);
    myAC.draw();
    glPopMatrix();


    glPushMatrix();
    mythungrac.setPosition(4.5f, 0.0f, 1.0f); 
    mythungrac.setScale(2.0f, 1.3f, 2.0f); 
    mythungrac.setRotation(0.0f, 0.0f, 0.0f); 
    mythungrac.setBodyColor(0.5f, 0.5f, 0.5f); 
    mythungrac.setLidColor(0.0f, 0.0f, 0.0f); 
    mythungrac.draw();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}



// Hàm chuyển đổi tọa độ chuột sang tọa độ thế giới 3D
void screenToWorld(int x, int y, float* worldX, float* worldY, float* worldZ) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    *worldX = (float)posX;
    *worldY = (float)posY;
    *worldZ = (float)posZ;
}

// Hàm xử lý click chuột cho gấu bông
void mouseClickBear(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Phương pháp đơn giản hơn: kiểm tra khu vực gấu bằng ray casting
        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        // Tạo ray từ camera qua điểm click
        GLdouble rayStart[3], rayEnd[3];
        GLfloat winX = (float)x;
        GLfloat winY = (float)viewport[3] - (float)y;

        gluUnProject(winX, winY, 0.0, modelview, projection, viewport,
            &rayStart[0], &rayStart[1], &rayStart[2]);
        gluUnProject(winX, winY, 1.0, modelview, projection, viewport,
            &rayEnd[0], &rayEnd[1], &rayEnd[2]);

        // Kiểm tra xem ray có đi qua vị trí gấu không
        float bearWorldX = bearX;
        float bearWorldY = bearY;
        float bearWorldZ = bearZ;

        // Tính khoảng cách từ điểm gấu đến ray
        float dx = bearWorldX - rayStart[0];
        float dy = bearWorldY - rayStart[1];
        float dz = bearWorldZ - rayStart[2];

        float rayDx = rayEnd[0] - rayStart[0];
        float rayDy = rayEnd[1] - rayStart[1];
        float rayDz = rayEnd[2] - rayStart[2];

        // Normalize ray direction
        float rayLength = sqrt(rayDx * rayDx + rayDy * rayDy + rayDz * rayDz);
        rayDx /= rayLength;
        rayDy /= rayLength;
        rayDz /= rayLength;

        // Tính projection của vector từ ray start đến gấu lên ray direction
        float t = dx * rayDx + dy * rayDy + dz * rayDz;

        // Tìm điểm gần nhất trên ray
        float closestX = rayStart[0] + t * rayDx;
        float closestY = rayStart[1] + t * rayDy;
        float closestZ = rayStart[2] + t * rayDz;

        // Tính khoảng cách từ gấu đến điểm gần nhất
        float distX = bearWorldX - closestX;
        float distY = bearWorldY - closestY;
        float distZ = bearWorldZ - closestZ;
        float distance = sqrt(distX * distX + distY * distY + distZ * distZ);

        // Nếu khoảng cách nhỏ hơn bán kính gấu (scaled), coi như click trúng
        if (distance < 0.6f && t > 0) { // 0.6f là bán kính tương đối của gấu
            printf("Clicked on bear! Moving to carpet...\n");
            moveBearToCarpet();
        }
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    specialKeyStates[key] = true;
    glutPostRedisplay();
}

void specialKeysUp(int key, int x, int y) {
    specialKeyStates[key] = false;
    glutPostRedisplay();
}

void idle() {
    glutPostRedisplay();
}

/* ----------  Phối cảnh  ---------- */
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Phong do choi");
    init();
    glutDisplayFunc(drawRoom);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);       
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutIdleFunc(idle);
    glutIdleFunc(update);
    glutMouseFunc(mouseClickBear);
    glutMainLoop();
    return 0;
}