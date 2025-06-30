#include "glut.h"
#include "anh.h"

extern GLuint photoTexture; // Khai báo dùng biến ngoài

void drawPictureFrame() {
    glPushMatrix();
    glTranslatef(0.1f, 3.2f, -4.8f); // Đặt vị trí
    glRotatef(-180.0f, 0, 1, 0);        // Hướng vào trong phòng

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, photoTexture);
    glColor3f(1.0, 1.0, 1.0); // Không làm sai màu ảnh

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-3.5f, -1.5f, 0.0f);  // Tăng kích thước từ -0.5 -> -1.0 (chiều rộng)
    glTexCoord2f(1, 0); glVertex3f(3.5f, -1.5f, 0.0f);   // và từ -0.5 -> -0.8 (chiều cao)
    glTexCoord2f(1, 1); glVertex3f(3.5f, 1.5f, 0.0f);
    glTexCoord2f(0, 1); glVertex3f(-3.5f, 1.5f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Viền khung gỗ (cũng tăng kích thước theo)
    glColor3f(0.4f, 0.2f, 0.05f);
    glLineWidth(8.0f); // Tăng độ dày viền cho phù hợp với ảnh lớn hơn
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0f, -0.8f, 0.01f);
    glVertex3f(1.0f, -0.8f, 0.01f);
    glVertex3f(1.0f, 0.8f, 0.01f);
    glVertex3f(-1.0f, 0.8f, 0.01f);
    glEnd();

    glPopMatrix();
}
 