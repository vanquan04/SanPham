<?php
include('connect.php');
$sql = "SELECT * FROM sanpham";
$result = $conn->query($sql);
?>
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Danh Sách Sản Phẩm</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 20px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            background: #fff;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            overflow: hidden;
        }
        th, td {
            padding: 12px;
            text-align: center;
            border-bottom: 1px solid #ddd;
        }
        th {
            background-color: #007BFF;
            color: white;
            text-transform: uppercase;
        }
        tr:hover {
            background-color: #f1f1f1;
        }
        img {
            width: 80px;
            height: 80px;
            object-fit: cover;
            border-radius: 5px;
        }
        .delete-btn {
            display: inline-block;
            padding: 6px 12px;
            color: white;
            background-color: #dc3545;
            text-decoration: none;
            border-radius: 5px;
            transition: background 0.3s;
        }
        .delete-btn:hover {
            background-color: #c82333;
        }
    </style>
</head>
<body>
    <h2 style="text-align: center; color: #333;">Danh Sách Sản Phẩm</h2>
    <?php if ($result->num_rows > 0) { ?>
        <table>
            <tr>
                <th>Mã SP</th>
                <th>Tên SP</th>
                <th>Hình ảnh</th>
                <th>Giá SP</th>
                <th>Giá Cũ</th>
                <th>Mô tả Ngắn</th>
                <th>Mô tả Chi Tiết</th>
                <th>Ngày Cập Nhật</th>
                <th>Số Lượng</th>
                <th>Thao Tác</th>
            </tr>
            <?php while ($row = $result->fetch_assoc()) { ?>
                <tr>
                    <td><?= $row["ma_sp"] ?></td>
                    <td><?= $row["ten_sp"] ?></td>
                    <td><img src='<?= $row["link_image"] ?>' alt='Hình ảnh sản phẩm'></td>
                    <td><?= number_format($row["gia_sp"], 2) ?> VND</td>
                    <td><?= number_format($row["giacu_sp"], 2) ?> VND</td>
                    <td><?= $row["mota_ngan_sp"] ?></td>
                    <td><?= $row["mota_chitiet_sp"] ?></td>
                    <td><?= $row["ngaycapnhat_sp"] ?></td>
                    <td><?= $row["soluong_sp"] ?></td>
                    <td><a href='sua_sp.php?ma_sp=<?= $row["ma_sp"] ?>'>Sửa</a> | 
                    <a href='xoa_sp.php?ma_sp=<?= $row["ma_sp"] ?>' onclick='return confirm("Bạn có chắc chắn muốn xóa sản phẩm này không?")'>Xóa</a></td>
                </tr>
            <?php } ?>
        </table>
    <?php } else { ?>
        <p style="text-align: center; color: red;">Không có sản phẩm nào.</p>
    <?php } ?>
</body>
</html>
<?php $conn->close(); ?>