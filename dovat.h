#ifndef DOVAT_H
#define DOVAT_H

// Khai báo các hàm vẽ đồ vật
void drawWallClock();           // Vẽ đồng hồ treo tường
void drawFlowerPot();           // Vẽ chậu hoa
void drawCornerFan();           // Vẽ quạt góc phòng
void drawToyShelf();            // Vẽ kệ tủ đồ chơi
void drawAllDoVat();            // Vẽ tất cả đồ vật

// Khai báo các hàm cập nhật
void updateDoVat();             // Cập nhật tất cả đồ vật
void updateClock();             // Cập nhật đồng hồ
void updateFan();               // Cập nhật quạt

// Khai báo hàm điều khiển
void toggleFan();               // Bật/tắt quạt

// Khai báo biến extern để có thể truy cập từ file khác
extern float clockAngleHour;    // Góc kim giờ
extern float clockAngleMinute;  // Góc kim phút  
extern float clockAngleSecond;  // Góc kim giây
extern float clockTime;         // Thời gian ảo

extern float fanAngle;          // Góc quay cánh quạt
extern bool fanRunning;         // Trạng thái quạt

#endif // DOVAT_H