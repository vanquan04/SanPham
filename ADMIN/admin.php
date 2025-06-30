<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Admin Dashboard</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="bg-gray-100">
    <div class="flex h-screen">
        <!-- Sidebar -->
        <div class="w-64 bg-blue-900 text-white p-5">
            <h2 class="text-2xl font-bold">Admin Panel</h2>
            <ul class="mt-5 space-y-3">
                <li class="p-2 bg-blue-700 rounded">🏠 Trang chủ</li>
                <li class="p-2 hover:bg-blue-700 rounded cursor-pointer">📦 Sản phẩm</li>
                <li class="p-2 hover:bg-blue-700 rounded cursor-pointer">📝 Bài viết</li>
                <li class="p-2 hover:bg-blue-700 rounded cursor-pointer">📊 Đơn hàng</li>
                <li class="p-2 hover:bg-blue-700 rounded cursor-pointer">👤 Thành viên</li>
            </ul>
        </div>
        
        <!-- Main Content -->
        <div class="flex-1 p-6">
            <h1 class="text-3xl font-semibold">Tổng quan</h1>
            
            <!-- Dashboard Cards -->
            <div class="grid grid-cols-4 gap-6 mt-6">
                <div class="bg-yellow-400 p-4 rounded shadow-md text-white">
                    <h2 class="text-2xl font-bold">363</h2>
                    <p>Sản phẩm</p>
                    <button class="mt-2 bg-white text-yellow-600 px-4 py-1 rounded" onclick="fetchProducts()">Xem</button>
                </div>
                <div class="bg-green-500 p-4 rounded shadow-md text-white">
                    <h2 class="text-2xl font-bold">12</h2>
                    <p>Danh mục sản phẩm</p>
                </div>
                <div class="bg-blue-500 p-4 rounded shadow-md text-white">
                    <h2 class="text-2xl font-bold">5</h2>
                    <p>Bài viết</p>
                </div>
                <div class="bg-red-500 p-4 rounded shadow-md text-white">
                    <h2 class="text-2xl font-bold">2</h2>
                    <p>Danh mục bài viết</p>
                </div>
            </div>

            <!-- Tìm kiếm & Thêm sản phẩm -->
            <div class="mt-6 flex justify-between items-center">
                <form method="GET" action="timkiem.php" class="w-1/3">
                    <button type="submit" class="bg-green-600 text-white px-4 py-2 rounded mt-2">🔍 Tìm kiếm</button>
                </form>
                <button class="bg-blue-600 text-white px-4 py-2 rounded" onclick="window.location.href='Themmoi.php'">+ Thêm sản phẩm</button>
            </div>

            <!-- Danh sách sản phẩm -->
            <div id="product-list" class="mt-6 hidden">
                <h2 class="text-2xl font-bold mb-4">Danh sách sản phẩm</h2>
                <?php
                include 'Hienthi.php';
                ?>
            </div>
        </div>
    </div>

    <script>
        function fetchProducts() {
            document.getElementById('product-list').classList.toggle('hidden');
        }
    </script>
</body>
</html>