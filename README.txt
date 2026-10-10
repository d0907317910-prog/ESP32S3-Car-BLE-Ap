CAR CONTROL - ESP32-S3 四路 BLE 控制 PWA

檔案：
- index.html：手機控制介面與 BLE 指令
- manifest.json：PWA 安裝資訊
- sw.js：Service Worker 與離線快取
- icon-192.png、icon-512.png：安裝圖示

部署：
1. 將 ZIP 解壓縮。
2. 把上述 5 個檔案上傳到 GitHub repository 根目錄（與原本檔案同層）。
3. Commit changes，等待 GitHub Pages 更新。
4. 重新開啟網站，測試 Application > Manifest。

BLE 指令預期格式：
R1:1 / R1:0 到 R4:1 / R4:0
Service UUID: 12345678-1234-5678-1234-56789abcdef0
Characteristic UUID: 12345678-1234-5678-1234-56789abcdef1

注意：請先在桌面或安全的低壓測試環境驗證繼電器行為，不要直接連接車輛高壓或動力電路。
