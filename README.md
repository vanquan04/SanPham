🧸 Hướng Dẫn Cài Đặt và Chạy Chương Trình: Phòng Đồ Chơi 3D
1. 💻 Yêu Cầu Hệ Thống
Hệ điều hành: Windows 10 hoặc cao hơn

Visual Studio 2019/2022 (bản có hỗ trợ C++)

Đã cài đặt:

Visual Studio C++ Desktop Development

GLUT (thư viện đồ họa OpenGL)

Thư viện stb_image (kèm trong dự án)

2. 🗂 Cấu Trúc Thư Mục
bash
Sao chép
Chỉnh sửa
PhongDoChoi3D/
│── 📁ADMIN/              # (Tuỳ chọn) Thư mục giao diện hoặc điều khiển
│── 📁css/                # Giao diện (nếu có tích hợp HTML, WebView)
│── 📁x64/Debug/          # Thư mục build tự động (nên bỏ qua Git)
│── 📁.vs/                # File cấu hình VS (nên .gitignore)

│── 📁Code Sources:
│   ├── main.cpp          # File chính khởi chạy chương trình
│   ├── Car.h / .cpp      # Đối tượng xe đồ chơi
│   ├── bong.h / .cpp     # Quả bóng rổ
│   ├── gau.h / .cpp      # Gấu bông
│   ├── tham.h / thamcpp.cpp # Tấm thảm
│   ├── khunganh.h / .cpp # Tranh treo tường
│   ├── dieuhoa.h / .cpp  # Điều hòa
│   ├── cua.h / .cpp      # Cửa phòng
│   ├── tructhang.h/.cpp  # Trực thăng mini
│   ├── xe.h / xe.cpp     # Mô hình xe
│   ├── stb_image.h       # Thư viện đọc ảnh

│── 📁Assets:
│   ├── a2.jpg            # Ảnh nền (ví dụ: tranh sao đêm)
│   ├── a3.jpg            # Ảnh khác (nếu có)

│── 📄BTL.sln             # File solution Visual Studio
│── 📄BTL.vcxproj         # File cấu hình project
│── 📄BTL.vcxproj.filters
│── 📄README.md           # Tài liệu mô tả
3. ⚙️ Cài Đặt
3.1 Cài Visual Studio
Tải Visual Studio tại visualstudio.microsoft.com

Cài đặt thêm: Desktop development with C++

3.2 Cài GLUT và cấu hình thư viện
Thư viện GLUT đã bao gồm trong project:

glut32.dll, glut.h, glut32.lib, glut.lib

Đảm bảo Visual Studio nhận đúng đường dẫn thư viện nếu build lỗi:

Include directory: trỏ đến folder chứa glut.h

Library directory: trỏ đến folder chứa .lib

4. ▶️ Chạy Chương Trình
Mở BTL.sln bằng Visual Studio

Chọn cấu hình x64-Debug

Bấm Ctrl + F5 để chạy

Giao diện hiển thị phòng đồ chơi 3D với các đối tượng: tranh, bóng, gấu, trực thăng, xe, thảm...

5. 📝 Lưu Ý
Nếu build bị lỗi thư viện:

Kiểm tra lại glut.lib, glut32.dll có được cấu hình đúng không

Đảm bảo chọn đúng x64 nếu bạn build thư viện x64

Nếu ảnh không hiện:

Kiểm tra file .jpg có nằm cùng thư mục không

Kiểm tra đường dẫn trong stb_image load ảnh

Chúc bạn trải nghiệm vui vẻ với thế giới đồ chơi 3D! 🧸🚁🏀

