<?php
include('connect.php');
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $ten_sp = $_POST['ten_sp'];
    $gia_sp = $_POST['gia_sp'];
    $giacu_sp = $_POST['giacu_sp'];
    $mota_ngan_sp = $_POST['mota_ngan_sp'];
    $mota_chitiet_sp = $_POST['mota_chitiet_sp'];
    $soluong_sp = $_POST['soluong_sp'];
    $link_image = $_POST['link_image'];
    
    $sql = "INSERT INTO sanpham (ten_sp, gia_sp, giacu_sp, mota_ngan_sp, mota_chitiet_sp, soluong_sp, link_image) 
            VALUES ('$ten_sp', '$gia_sp', '$giacu_sp', '$mota_ngan_sp', '$mota_chitiet_sp', '$soluong_sp', '$link_image')";
    
    if ($conn->query($sql) === TRUE) {
        echo "<script>alert('Thêm sản phẩm thành công!'); window.location.href='danhsach.php';</script>";
    } else {
        echo "Lỗi: " . $conn->error;
    }
}
$conn->close();
?>

<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Thêm Sản Phẩm</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            padding: 20px;
        }
        .container {
            max-width: 500px;
            background: #fff;
            padding: 20px;
            margin: auto;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
        }
        h2 {
            text-align: center;
            color: #333;
        }
        label {
            font-weight: bold;
        }
        input, textarea {
            width: 100%;
            padding: 10px;
            margin: 5px 0;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        .btn {
            width: 100%;
            padding: 10px;
            background: #007BFF;
            color: white;
            border: none;
            cursor: pointer;
            border-radius: 5px;
            transition: 0.3s;
            text-align: center;
            display: inline-block;
            margin-top: 10px;
        }
        .btn:hover {
            background: #007BFF;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>Thêm Sản Phẩm</h2>
        <form method="POST">
            <label>Tên Sản Phẩm:</label>
            <input type="text" name="ten_sp" required>
            
            <label>Giá Sản Phẩm:</label>
            <input type="number" name="gia_sp" required>
            
            <label>Giá Cũ:</label>
            <input type="number" name="giacu_sp">
            
            <label>Mô Tả Ngắn:</label>
            <textarea name="mota_ngan_sp" required></textarea>
            
            <label>Mô Tả Chi Tiết:</label>
            <textarea name="mota_chitiet_sp" required></textarea>
            
            <label>Số Lượng:</label>
            <input type="number" name="soluong_sp" required>
            
            <label>Link Ảnh:</label>
            <input type="text" name="link_image" required>
            
            <button type="submit" class="btn">Thêm Mới</button>
            <button type="button" class="btn" onclick="window.location.href='admin.php'">Quay lại</button>
        </form>
    </div>
</body>
</html>
