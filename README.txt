Ec電驅｜完整檢查版
====================

內容
- index.html：手機網頁介面
- manifest.json：PWA 安裝資訊
- sw.js：Service Worker 離線快取
- icon-192.png / icon-512.png：PWA 圖示
- firmware/EcDrive_ESP32S3/EcDrive_ESP32S3.ino：ESP32-S3 Arduino BLE 範例韌體

網頁功能
- BLE 連線／中斷連線
- 四路繼電器獨立控制
- 一鍵全開／全關（逐路傳送）
- 自訂繼電器名稱
- 自訂多組繼電器組合，組合可開啟或關閉所選路數
- 手機瀏覽器儲存名稱與組合
- PWA manifest 與 Service Worker 快取

BLE 設定（網頁與韌體必須一致）
- 裝置名稱：ESP32-S3-Car
- Service UUID：12345678-1234-5678-1234-56789abcdef0
- Characteristic UUID：12345678-1234-5678-1234-56789abcdef1
- 指令：R1:1 / R1:0 到 R4:1 / R4:0

GitHub Pages 部署
1. 將 ZIP 解壓縮。
2. 把 index.html、manifest.json、sw.js、兩個 PNG 圖示放在 GitHub 儲存庫根目錄（不要把它們放在額外的子資料夾裡）。
3. Commit/Push，並確認 GitHub Pages 部署完成。
4. 用 Android Chrome 開啟：
   https://d0907317910-prog.github.io/ESP32S3-Car-BLE-Ap/
5. 若舊版仍存在，先在 Chrome 網站設定清除該網站資料，再重新開啟。
6. Chrome 的安裝選項依瀏覽器版本與安裝條件而異；若沒有「安裝應用程式」，可先試「⋮」→「新增至主畫面」。

Arduino IDE
1. 安裝支援 ESP32 的 Arduino IDE 開發板套件。
2. 開啟 firmware/EcDrive_ESP32S3/EcDrive_ESP32S3.ino。
3. 依你的實際開發板核對 RELAY_PINS 的 GPIO 4、5、6、7 是否可用，再燒錄。
4. 確認繼電器模組是低電位觸發還是高電位觸發，必要時調整 RELAY_ACTIVE_LOW。
5. 網頁與韌體需使用相同 UUID、裝置名稱前綴及指令格式。

安全注意
- 此韌體是需依實際硬體核對的範例，尚未在你的實體 ESP32-S3、繼電器板及車輛上做硬體測試。
- GPIO 僅能連接適當的低壓控制輸入；不可將 36–110V 車輛電池或其他高電壓接到 ESP32 GPIO。
- 請先在無負載、限流的低壓測試環境驗證每一路開關方向與斷電狀態。車輛接線請交由合格技術人員確認。


【新版藍牙搜尋與名稱說明】
1. 網頁現在使用 acceptAllDevices:true，裝置選擇視窗不再只篩選名稱以 ESP 開頭的裝置。實際可看到哪些裝置仍由 Android、Chrome 與裝置廣播狀態決定。
2. 網頁的「手機介面顯示名稱」是本機備註，不會更改裝置真正的藍牙廣播名稱。
3. 要更改真正的藍牙名稱，請在 firmware/EcDrive_ESP32S3/EcDrive_ESP32S3.ino 修改 DEVICE_NAME，例如 "EcDrive-01"，再重新燒錄 ESP32-S3。
4. BLE 服務 UUID 與特徵 UUID 可在網頁設定。若要控制不同裝置，必須輸入該裝置實際使用的 UUID；任意藍牙裝置不一定有可寫入的控制特徵，也不一定使用 R1:1 等指令。
5. 本網頁以 BLE GATT 控制，不支援傳統藍牙 SPP/串列埠裝置。
6. 請先在低壓、無負載環境測試；接入車輛電路前請由合格人員確認。


本版本介面分為三個分頁：繼電器控制、控制組合、設定。藍牙 UUID 與手機介面顯示名稱、繼電器名稱都集中在「設定」。手機介面顯示名稱不會直接更改 BLE 裝置廣播名稱；ESP32-S3 真正名稱需修改韌體並重新燒錄。
