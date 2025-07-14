# 🧸 Hướng Dẫn Cài Đặt và Chạy Chương Trình: Phòng Đồ Chơi 3D

## 1. Yêu Cầu Hệ Thống
- Hệ điều hành: **Windows 10** hoặc cao hơn  
- **Visual Studio 2019/2022** (bản có hỗ trợ C++)  
- Các thành phần cần cài đặt:
  - ✅ Desktop development with C++
  - ✅ GLUT (thư viện đồ họa OpenGL)
  - ✅ Thư viện `stb_image.h` (đã kèm trong project)
  - 
---
## 2. Cấu Trúc Thư Mục
PhongDoChoi3D/
├── ADMIN/ # (Tuỳ chọn) Giao diện hoặc điều khiển
├── css/ # Giao diện (nếu có tích hợp HTML/WebView)
├── x64/Debug/ # Thư mục build tự động (nên bỏ qua Git)
├── .vs/ # File cấu hình Visual Studio (nên .gitignore)

├── Code Sources/
│ ├── main.cpp # File chính khởi chạy chương trình
│ ├── Car.h / Car.cpp # Đối tượng xe đồ chơi
│ ├── bong.h / bong.cpp # Quả bóng rổ
│ ├── gau.h / gau.cpp # Gấu bông
│ ├── tham.h / thamcpp.cpp # Tấm thảm
│ ├── khunganh.h / khunganh.cpp # Tranh treo tường
│ ├── dieuhoa.h / dieuhoa.cpp # Điều hòa
│ ├── cua.h / cua.cpp # Cửa phòng
│ ├── tructhang.h / tructhang.cpp # Trực thăng mini
│ ├── xe.h / xe.cpp # Mô hình xe
│ └── stb_image.h # Thư viện đọc ảnh texture

├── Assets/
│ ├── a2.jpg # Ảnh nền (ví dụ: tranh sao đêm)
│ └── a3.jpg # Ảnh texture khác

├── BTL.sln # File solution mở bằng Visual Studio
├── BTL.vcxproj # File cấu hình project
├── BTL.vcxproj.filters
└── README.md # Tài liệu mô tả dự án

## 3. Cài Đặt
### 3.1 Cài Visual Studio
- Tải tại: [https://visualstudio.microsoft.com](https://visualstudio.microsoft.com)
- Trong lúc cài, **chọn thêm workload**:  
  ✅ _Desktop development with C++_

### 3.2 Cài GLUT và Cấu Hình Thư Viện
- Các file GLUT đã bao gồm sẵn:
  - `glut32.dll`, `glut.h`, `glut32.lib`, `glut.lib`
- Trong Visual Studio:
  - Include directories: trỏ đến folder chứa `glut.h`
  - Library directories: trỏ đến folder chứa `*.lib`
  - Đảm bảo chọn cấu hình `x64` nếu dùng bản thư viện 64-bit

---
## 4. Chạy Chương Trình
1. Mở `BTL.sln` bằng **Visual Studio**  
2. Chọn cấu hình **x64-Debug**  
3. Nhấn **Ctrl + F5** để chạy  
4. Giao diện hiển thị mô hình phòng đồ chơi 3D với các vật thể như:
   - Tranh treo tường
   - Gấu bông
   - Bóng rổ
   - Xe đồ chơi
   - Trực thăng
   - Thảm...

---

## 5. Lưu Ý
- Nếu **bị lỗi không build được**:
  - Kiểm tra lại đường dẫn đến `glut32.lib`, `glut.h` đã đúng chưa
  - Kiểm tra cấu hình đang là `x64` nếu dùng thư viện `x64`
- Nếu **ảnh không hiển thị**:
  - Đảm bảo `.jpg` nằm đúng vị trí
  - Kiểm tra đường dẫn trong hàm `stbi_load()`
---
🎉 **Chúc bạn trải nghiệm vui vẻ với không gian đồ chơi 3D!**
