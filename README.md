# Ec電驅 完整專案

本 ZIP 包含：
- `web/index.html`：手機版 BLE 網頁介面
- `web/manifest.json`、`web/sw.js`：PWA 基礎檔案
- `firmware/EcDrive_ESP32S3.ino`：ESP32-S3 四路繼電器 + ANT BMS BLE 讀取整合範例

## 重要限制
這是可供你接著燒錄與測試的完整專案骨架，不代表已在你的特定 ESP32-S3、Arduino-ESP32 core 版本及 ANT BMS 上實機驗證。
ANT BMS 的 186-byte 封包欄位與倍率尚未確認，因此韌體刻意以 `valid:false` 傳送 HEX，不會假裝顯示已驗證的電壓、電流或 SOC。
整合 BLE Server + BLE Client 的同時運作可能因開發板、核心版本與 BMS 連線狀態而有差異；如編譯失敗，請把完整錯誤訊息提供給我，不能只看最後的 `exit status 1`。

## 網頁部署到 GitHub Pages
1. 解壓縮 ZIP。
2. 在 GitHub 建立一個 repository，例如 `EcDrive`.
3. 將 `web` 資料夾內的 `index.html`、`manifest.json`、`sw.js` 放到 repository 根目錄（不要把整個 `web` 資料夾再套一層）。
4. Repository → Settings → Pages。
5. Build and deployment 選 `Deploy from a branch`，Branch 選 `main`、資料夾選 `/(root)`，儲存。
6. 等待部署完成後，用 Android Chrome 開啟 GitHub Pages 的 HTTPS 網址。
7. 點「搜尋並連線 ESP32-S3」，從裝置選擇視窗選 ESP32。

## ESP32-S3 燒錄
1. 開啟 Arduino IDE，安裝 ESP32 by Espressif Systems 開發板套件。
2. 選對應的 ESP32-S3 board 與 COM port。
3. 開啟 `firmware/EcDrive_ESP32S3.ino`，編譯並燒錄。
4. 開啟序列監控視窗，鮑率 115200。
5. 先在低壓、無負載的測試環境確認四路繼電器的高低電位與啟動狀態。

## UUID 與協定
- ESP32 Service: `12345678-1234-5678-1234-56789abcdef0`
- Relay characteristic: `12345678-1234-5678-1234-56789abcdef1`
- Battery notify characteristic: `12345678-1234-5678-1234-56789abcdef2`
- ANT BMS Service: `FFE0`
- ANT BMS Characteristic: `FFE1`
- Relay write commands: `R1:1`, `R1:0` … `R4:1`, `R4:0`

## 186-byte BMS payload
韌體會將收到的資料以 JSON 傳到電池 characteristic，例如：
`{"valid":false,"status":"原始 BMS 封包；欄位/倍率未驗證","length":186,"hex":"7E A1 ..."}`

注意：BLE notification 單次資料長度通常有限；完整 HEX JSON 可能超出 MTU，因而被截斷或無法傳送。若發生這種情況，需要改成分段傳送（例如序號 + 分段 HEX）或先只傳短狀態摘要。這份初版程式尚未加入分段協定。
網頁目前會顯示收到的原始通知 bytes/HEX；若 JSON 被截斷，除錯區仍會顯示可收到的內容，但不會解析成已驗證數值。

## 安全
你的車用電池最高可能達 110 V。不要把高壓直接接到 ESP32、USB 或低壓模組。繼電器觸點、線材、保險絲、隔離電源與外殼都必須符合實際電壓/電流與環境要求；請先在低壓無負載條件下測試。
