<?php
include('connect.php');
if (isset($_GET['ma_sp'])) {
    $ma_sp = $_GET['ma_sp'];
    $sql = "SELECT * FROM sanpham WHERE ma_sp='$ma_sp'";
    $result = $conn->query($sql);
    $row = $result->fetch_assoc();
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $ten_sp = $_POST['ten_sp'];
    $gia_sp = $_POST['gia_sp'];
    $giacu_sp = $_POST['giacu_sp'];
    $mota_ngan_sp = $_POST['mota_ngan_sp'];
    $mota_chitiet_sp = $_POST['mota_chitiet_sp'];
    $soluong_sp = $_POST['soluong_sp'];
    $link_image = $_POST['link_image'];
    
    $sql_update = "UPDATE sanpham SET ten_sp='$ten_sp', gia_sp='$gia_sp', giacu_sp='$giacu_sp', mota_ngan_sp='$mota_ngan_sp', mota_chitiet_sp='$mota_chitiet_sp', soluong_sp='$soluong_sp', link_image='$link_image' WHERE ma_sp='$ma_sp'";
    
    if ($conn->query($sql_update) === TRUE) {
        echo "<script>alert('Cập nhật thành công!'); window.location.href='danhsach.php';</script>";
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
    <title>Sửa Sản Phẩm</title>
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
            background: #0056b3;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>Sửa Sản Phẩm</h2>
        <form method="POST">
            <label>Tên Sản Phẩm:</label>
            <input type="text" name="ten_sp" value="<?= $row['ten_sp'] ?>" required>
            
            <label>Giá Sản Phẩm:</label>
            <input type="number" name="gia_sp" value="<?= $row['gia_sp'] ?>" required>
            
            <label>Giá Cũ:</label>
            <input type="number" name="giacu_sp" value="<?= $row['giacu_sp'] ?>">
            
            <label>Mô Tả Ngắn:</label>
            <textarea name="mota_ngan_sp" required><?= $row['mota_ngan_sp'] ?></textarea>
            
            <label>Mô Tả Chi Tiết:</label>
            <textarea name="mota_chitiet_sp" required><?= $row['mota_chitiet_sp'] ?></textarea>
            
            <label>Số Lượng:</label>
            <input type="number" name="soluong_sp" value="<?= $row['soluong_sp'] ?>" required>
            
            <label>Link Ảnh:</label>
            <input type="text" name="link_image" value="<?= $row['link_image'] ?>" required>
            
            <button type="submit" class="btn">Cập Nhật</button>
            <button type="button" class="btn" onclick="window.location.href='admin.php'">Quay lại</button>
        </form>
    </div>
</body>
</html>
