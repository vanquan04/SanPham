#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glut.h"
#include <cstdio>

// Hàm tải ảnh thành texture OpenGL
GLuint loadTexture(const char* filename) {
    int width, height, channels;
    // Tải ảnh từ file
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        printf("❌ Không thể load ảnh: %s\n", filename);
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);                    // Tạo texture ID
    glBindTexture(GL_TEXTURE_2D, textureID);         // Gắn texture vào GL_TEXTURE_2D

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    // Gửi dữ liệu ảnh lên GPU
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
        format, GL_UNSIGNED_BYTE, data);

    // Thiết lập bộ lọc
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data); // Giải phóng bộ nhớ
    return textureID;
}
