CAR CONTROL - ESP32-S3 自訂繼電器名稱版

功能：
- 四路 BLE 繼電器控制
- 每一路可點「編輯」自訂名稱
- 名稱自動儲存在目前手機/瀏覽器
- 保留原 BLE Service/Characteristic UUID 與 R1:1、R1:0 到 R4 指令
- PWA manifest、service worker 與安裝按鈕

上傳方式：
1. 解壓縮 ZIP。
2. 將裡面所有檔案上傳到 GitHub Pages 使用的同一個資料夾（覆蓋舊檔）。
3. 等待 GitHub Pages 部署完成。
4. 手機 Chrome 開啟網站，重新整理；若顯示舊版本，清除網站資料或稍後再開。

注意：
- 本版本只改手機介面顯示名稱，不會更改 ESP32-S3 韌體。
- 藍牙 UUID 和指令需與現有 ESP32-S3 程式相同。
- 請先在低電壓、無負載環境測試；車輛電路請由合格成人/技術人員確認。
