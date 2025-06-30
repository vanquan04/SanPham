<?php
include('connect.php');
$keyword = '';
$result = null;
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $keyword = $_POST['keyword'];
    $sql = "SELECT * FROM sanpham WHERE ten_sp LIKE '%$keyword%'";
    $result = $conn->query($sql);
}
$conn->close();
?>

<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Tìm Kiếm Sản Phẩm</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            padding: 20px;
        }
        .container {
            max-width: 600px;
            background: #fff;
            padding: 20px;
            margin: auto;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            text-align: center;
        }
        h2 {
            color: #333;
        }
        input {
            width: 80%;
            padding: 10px;
            margin: 10px 0;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        .btn {
            padding: 10px 15px;
            background: #007BFF;
            color: white;
            border: none;
            cursor: pointer;
            border-radius: 5px;
            transition: 0.3s;
        }
        .btn:hover {
            background: #0056b3;
        }
        table {
            width: 100%;
            margin-top: 20px;
            border-collapse: collapse;
            background: #fff;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
        }
        th, td {
            padding: 10px;
            border-bottom: 1px solid #ddd;
            text-align: center;
        }
        th {
            background-color: #007BFF;
            color: white;
        }
        tr:hover {
            background-color: #f1f1f1;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>Tìm Kiếm Sản Phẩm</h2>
        <form method="POST">
            <input type="text" name="keyword" placeholder="Nhập tên sản phẩm..." value="<?= htmlspecialchars($keyword) ?>" required>
            <button type="submit" class="btn btn-primary">Tìm Kiếm</button>
            <button type="button" class="btn btn-secondary" onclick="window.location.href='admin.php'">Quay lại</button>
        </form>
        
        <?php if ($result && $result->num_rows > 0) { ?>
            <table>
                <tr>
                    <th>Mã SP</th>
                    <th>Tên SP</th>
                    <th>Giá</th>
                    <th>Hình Ảnh</th>
                </tr>
                <?php while ($row = $result->fetch_assoc()) { ?>
                    <tr>
                        <td><?= $row['ma_sp'] ?></td>
                        <td><?= $row['ten_sp'] ?></td>
                        <td><?= number_format($row['gia_sp'], 2) ?> VND</td>
                        <td><img src='<?= $row['link_image'] ?>' style='width: 80px; height: 80px; object-fit: cover;'></td>
                    </tr>
                <?php } ?>
            </table>
        <?php } elseif ($result) { ?>
            <p style="color: red;">Không tìm thấy sản phẩm nào!</p>
        <?php } ?>
    </div>
</body>
</html>