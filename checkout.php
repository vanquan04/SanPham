<?php
session_start();

// Check if cart is empty
if (!isset($_SESSION['cart']) || empty($_SESSION['cart'])) {
    header('Location: cart.php');
    exit;
}

// Calculate cart totals
$total_items = 0;
$total_price = 0;
foreach ($_SESSION['cart'] as $item) {
    $total_items += $item['quantity'];
    $total_price += $item['price'] * $item['quantity'];
}

// Flag to show success message
$show_success = false;

// Handle form submission
if (isset($_POST['place_order'])) {
    // Here you would normally process the order, save to database, etc.
    
    // Clear the cart after successful order
    $_SESSION['cart'] = [];
    
    // Set flag to show success message
    $show_success = true;
}

// Handle redirect after closing the popup
if (isset($_POST['confirm_order'])) {
    header('Location: index.php');
    exit;
}
?>

<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Thanh toán - realphoneA</title>
    <link rel="stylesheet" href="css/index.css">
    <style>
        .checkout-container {
            max-width: 1200px;
            margin: 20px auto;
            padding: 20px;
            background-color: #fff;
            border-radius: 5px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            display: flex;
            flex-wrap: wrap;
            gap: 20px;
        }
        
        .checkout-title {
            font-size: 24px;
            margin-bottom: 20px;
            color: #d70018;
            width: 100%;
        }
        
        .checkout-form {
            flex: 1;
            min-width: 300px;
        }
        
        .order-summary {
            flex: 1;
            min-width: 300px;
            background-color: #f9f9f9;
            padding: 20px;
            border-radius: 5px;
        }
        
        .form-group {
            margin-bottom: 15px;
        }
        
        .form-group label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
        }
        
        .form-group input, .form-group select, .form-group textarea {
            width: 100%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 3px;
        }
        
        .form-group textarea {
            height: 100px;
        }
        
        .order-items {
            margin-top: 20px;
        }
        
        .order-item {
            display: flex;
            justify-content: space-between;
            padding: 10px 0;
            border-bottom: 1px solid #eee;
        }
        
        .order-total {
            margin-top: 20px;
            font-size: 18px;
            font-weight: bold;
            text-align: right;
        }
        
        .place-order-btn {
            background-color: #d70018;
            color: white;
            border: none;
            padding: 15px;
            width: 100%;
            font-size: 16px;
            border-radius: 3px;
            cursor: pointer;
            margin-top: 20px;
        }
        
        .payment-methods {
            margin-top: 20px;
        }
        
        .payment-method {
            margin-bottom: 10px;
        }
        
        /* Modal styles */
        .modal-overlay {
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            background-color: rgba(0, 0, 0, 0.7);
            display: flex;
            justify-content: center;
            align-items: center;
            z-index: 1000;
        }
        
        .modal-content {
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            max-width: 500px;
            text-align: center;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
            animation: glow 1.5s infinite alternate;
        }
        
        @keyframes glow {
            from {
                box-shadow: 0 0 10px -10px #d70018;
            }
            to {
                box-shadow: 0 0 20px 10px #d70018;
            }
        }
        
        .modal-title {
            font-size: 24px;
            color: #d70018;
            margin-bottom: 20px;
        }
        
        .modal-message {
            font-size: 18px;
            margin-bottom: 30px;
        }
        
        .modal-button {
            background-color: #d70018;
            color: white;
            border: none;
            padding: 12px 25px;
            font-size: 16px;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s;
        }
        
        .modal-button:hover {
            background-color: #ff1f3d;
        }
    </style>
</head>
<body>
    <?php if($show_success): ?>
    <!-- Success Modal -->
    <div class="modal-overlay">
        <div class="modal-content">
            <div class="modal-title">Thành công!</div>
            <div class="modal-message">Đặt hàng thành công! Cảm ơn bạn đã sử dụng dịch vụ của chúng tôi.</div>
            <form method="post">
                <button type="submit" name="confirm_order" class="modal-button">Tiếp tục</button>
            </form>
        </div>
    </div>
    <?php endif; ?>
    
    <!-- Top Banner -->
    <div class="top-banner">
        🔴 Quà 'SHE' MÊ - Sale cực đỉnh. Chọn quà ngay!
    </div>
    
    <!-- Sub Header -->
    <div class="sub-header">
        <div class="sub-header-item">
            <img src="https://cdn-icons-png.flaticon.com/128/831/831378.png" alt="App Icon">
            Tải App Smember - Tích điểm & nhận ưu đãi
        </div>
        <div class="sub-header-item">
            <img src="https://cdn-icons-png.flaticon.com/128/5991/5991056.png" alt="Used Product Icon">
            Thu cũ Giá ngon - Lên đời tiết kiệm
        </div>
        <div class="sub-header-item">
            <img src="https://cdn-icons-png.flaticon.com/128/16459/16459555.png" alt="Authentic Icon">
            Sản phẩm Chính hãng - Xuất VAT đầy đủ
        </div>
    </div>
    
    <!-- Main Header -->
    <div class="header">
        <div class="logo"><a href="index.php" style="color: white; text-decoration: none;">realphoneA</a></div>
        <button class="menu-button">
            <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <line x1="3" y1="12" x2="21" y2="12"></line>
                <line x1="3" y1="6" x2="21" y2="6"></line>
                <line x1="3" y1="18" x2="21" y2="18"></line>
            </svg>
            Danh mục
        </button>
        
        <div class="search-box">
            <input type="text" placeholder="Bạn cần tìm gì?">
        </div>
        <div class="header-icons">
            <div class="icon-button">
                <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="white" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <path d="M5 17H4a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h16a2 2 0 0 1 2 2v10a2 2 0 0 1-2 2h-1"></path>
                    <polygon points="12 15 17 21 7 21 12 15"></polygon>
                </svg>
                Tra cứu<br>đơn hàng
            </div>
            <div class="icon-button">
                <a href="cart.php" style="text-decoration: none; color: white;">
                    <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="white" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                        <circle cx="9" cy="21" r="1"></circle>
                        <circle cx="20" cy="21" r="1"></circle>
                        <path d="M1 1h4l2.68 13.39a2 2 0 0 0 2 1.61h9.72a2 2 0 0 0 2-1.61L23 6H6"></path>
                    </svg>
                    Giỏ<br>hàng
                    <span class="cart-counter" style="position: absolute; top: -5px; right: -5px; background-color: yellow; color: black; border-radius: 50%; width: 20px; height: 20px; display: flex; align-items: center; justify-content: center; font-size: 12px;"><?php echo $total_items; ?></span>
                </a>
            </div>
            <div class="icon-button">
                <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="white" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                    <path d="M20 21v-2a4 4 0 0 0-4-4H8a4 4 0 0 0-4 4v2"></path>
                    <circle cx="12" cy="7" r="4"></circle>
                </svg>
                <?php
                if(isset($_SESSION['user'])) {
                    echo '<span>' . $_SESSION['user']['fullname'] . '</span>';
                    echo '<a href="logout.php" style="display:block; color:white; font-size:12px; text-decoration:none;">Đăng xuất</a>';
                } else {
                    echo '<a href="login.php" style="display:block; color:white; font-size:12px; text-decoration:none;">Đăng nhập</a>';
                }
                ?>
            </div>
        </div>
    </div>
    
    <!-- Checkout Container -->
    <div class="checkout-container">
        <h1 class="checkout-title">Thanh toán</h1>
        
        <div class="checkout-form">
            <h2>Thông tin giao hàng</h2>
            <form method="post" action="checkout.php">
                <div class="form-group">
                    <label for="fullname">Họ và tên</label>
                    <input type="text" id="fullname" name="fullname" required>
                </div>
                
                <div class="form-group">
                    <label for="phone">Số điện thoại</label>
                    <input type="tel" id="phone" name="phone" required>
                </div>
                
                <div class="form-group">
                    <label for="email">Email</label>
                    <input type="email" id="email" name="email" required>
                </div>
                
                <div class="form-group">
                    <label for="address">Địa chỉ</label>
                    <textarea id="address" name="address" required></textarea>
                </div>
                
                <div class="form-group">
                    <label for="city">Tỉnh/Thành phố</label>
                    <select id="city" name="city" required>
                        <option value="">Chọn tỉnh/thành phố</option>
                        <option value="hn">Hà Nội</option>
                        <option value="hcm">TP. Hồ Chí Minh</option>
                        <option value="dn">Đà Nẵng</option>
                        <!-- Add more cities as needed -->
                    </select>
                </div>
                
                <div class="payment-methods">
                    <h2>Phương thức thanh toán</h2>
                    <div class="payment-method">
                        <input type="radio" id="cod" name="payment_method" value="cod" checked>
                        <label for="cod">Thanh toán khi nhận hàng (COD)</label>
                    </div>
                    <div class="payment-method">
                        <input type="radio" id="bank_transfer" name="payment_method" value="bank_transfer">
                        <label for="bank_transfer">Chuyển khoản ngân hàng</label>
                    </div>
                    <div class="payment-method">
                        <input type="radio" id="momo" name="payment_method" value="momo">
                        <label for="momo">Thanh toán qua Momo</label>
                    </div>
                    <div class="payment-method">
                        <input type="radio" id="vnpay" name="payment_method" value="vn_pay">
                        <label for="vnpay">Thanh toán qua VNPay</label>
                    </div>
                </div>
                <style>
                    .payment-methods {
                        margin-top: 20px;
                        padding: 20px;
                        background-color: #f9f9f9;
                        border-radius: 5px;
                        border: 1px solid #ddd;
                    }
                    
                    .payment-method {
                        margin-bottom: 10px;
                    }
                    
                    .payment-method input {
                        margin-right: 10px;
                    }
                    
                    .payment-method label {
                        font-weight: normal;
                    }
                </style>

                <button type="submit" name="place_order" class="place-order-btn">Đặt hàng</button>
            </form>
        </div>

        <div class="order-summary">
            <h2>Đơn hàng</h2>
            <div class="order-items">
                <?php foreach ($_SESSION['cart'] as $item): ?>
                    <div class="order-item">
                        <div><?php echo $item['name']; ?> x <?php echo $item['quantity']; ?></div>
                        <div><?php echo number_format($item['price'] * $item['quantity']); ?>đ</div>
                    </div>
                <?php endforeach; ?>
            </div>
            <div class="order-total">
                Tổng cộng: <?php echo number_format($total_price); ?>đ
            </div>
        </div>
    </div>

      <!-- Footer -->
      <div class="footer">
        <div class="footer-grid">
            <div class="footer-section">
                <h3>Tổng đài hỗ trợ miễn phí</h3>
                <ul class="footer-links">
                    <li>Mua hàng - bảo hành 1800.2097 (7h30 - 22h00)</li>
                    <li>Khiếu nại 1800.2063 (8h00 - 21h30)</li>
                </ul>
                <h3>Phương thức thanh toán</h3>
                <div class="payment-methods">
                    <div class="payment-method"><img src="https://cdn2.cellphones.com.vn/x35,webp/media/wysiwyg/apple-pay-og.png" alt="Apple Pay"></div>
                    <div class="payment-method"><img src="https://cdn2.cellphones.com.vn/x35,webp/media/logo/payment/vnpay-logo.png" alt="VNPAY"></div>
                    <div class="payment-method"><img src="https://cdn2.cellphones.com.vn/x/media/wysiwyg/momo_1.png" alt="Momo"></div>
                    <div class="payment-method"><img src="https://cdn2.cellphones.com.vn/x35,webp/media/logo/payment/onepay-logo.png" alt="OnePay"></div>
                    <div class="payment-method"><img src="https://cdn2.cellphones.com.vn/x35,webp/media/logo/payment/zalopay-logo.png" alt="ZaloPay"></div>
                </div>
            </div>
            <div class="footer-section">
                <h3>Thông tin và chính sách</h3>
                <ul class="footer-links">
                    <li>Mua hàng và thanh toán Online</li>
                    <li>Mua hàng trả góp Online</li>
                    <li>Mua hàng trả góp bằng thẻ tín dụng</li>
                    <li>Chính sách giao hàng</li>
                    <li>Tra điểm Smember</li>
                    <li>Xem ưu đãi Smember</li>
                </ul>
            </div>
            <div class="footer-section">
                <h3>Dịch vụ và thông tin khác</h3>
                <ul class="footer-links">
                    <li>Khách hàng doanh nghiệp (B2B)</li>
                    <li>Ưu đãi thanh toán</li>
                    <li>Quy chế hoạt động</li>
                    <li>Chính sách bảo mật thông tin cá nhân</li>
                    <li>Chính sách bảo hành</li>
                    <li>Liên hệ hợp tác kinh doanh</li>
                    <li>Tuyển dụng</li>
                </ul>
            </div>
            <div class="footer-section">
                <h3>Đăng ký nhận thông tin khuyến mại</h3>
                <p>*Voucher sẽ được gửi sau 24h, chỉ áp dụng cho khách hàng mới</p>
                <input type="email" placeholder="Nhập email của bạn" style="padding: 10px; margin-bottom: 10px; width: 100%; border: 1px solid #ccc; border-radius: 5px;">
                <input type="text" placeholder="Nhập số điện thoại của bạn" style="padding: 10px; margin-bottom: 10px; width: 100%; border: 1px solid #ccc; border-radius: 5px;">
                <div style="margin-bottom: 10px;">
                    <input type="checkbox" id="agree-terms" style="margin-right: 5px;">
                    <label for="agree-terms">Tôi đồng ý với <a href="#" >điều khoản</a></label>
                    
                </div>
                <button style="padding: 10px 20px; background-color: #ff0000; color: #fff; border: none; border-radius: 5px; cursor: pointer;">Đăng ký</button>
            </div>
        </div>
    </div>
</body>
</html>