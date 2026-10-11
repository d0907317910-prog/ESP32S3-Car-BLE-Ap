#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// 請先核對你的 ESP32-S3 開發板腳位與繼電器模組接線，再修改以下 GPIO。
// 不要將車輛高電壓直接接到 ESP32；GPIO 只能接合適的低壓控制輸入。
static const int RELAY_PINS[4] = {4, 5, 6, 7};
// 多數繼電器模組為低電位觸發；若你的模組是高電位觸發，改成 false。
static const bool RELAY_ACTIVE_LOW = true;

// 要更改真正的藍牙廣播名稱，修改下一行後重新燒錄 ESP32-S3。
static const char *DEVICE_NAME = "ESP32-S3-Car";
static const char *SERVICE_UUID = "12345678-1234-5678-1234-56789abcdef0";
static const char *CHARACTERISTIC_UUID = "12345678-1234-5678-1234-56789abcdef1";

BLECharacteristic *controlCharacteristic = nullptr;

void setRelay(uint8_t index, bool on) {
  if (index >= 4) return;
  const uint8_t level = (on ^ RELAY_ACTIVE_LOW) ? HIGH : LOW;
  digitalWrite(RELAY_PINS[index], level);
  Serial.printf("R%u:%u\n", index + 1, on ? 1 : 0);
}

class ControlCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *characteristic) override {
    std::string value = characteristic->getValue();
    if (value.length() != 4 || value[0] != 'R' || value[2] != ':') {
      Serial.println("Ignored invalid command");
      return;
    }
    if (value[1] < '1' || value[1] > '4' || (value[3] != '0' && value[3] != '1')) {
      Serial.println("Ignored invalid command");
      return;
    }
    const uint8_t index = static_cast<uint8_t>(value[1] - '1');
    const bool on = value[3] == '1';
    setRelay(index, on);
  }
};

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < 4; ++i) {
    pinMode(RELAY_PINS[i], OUTPUT);
    // 上電先設定為關閉狀態，降低啟動時誤動作風險。
    digitalWrite(RELAY_PINS[i], RELAY_ACTIVE_LOW ? HIGH : LOW);
  }

  BLEDevice::init(DEVICE_NAME);
  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(SERVICE_UUID);
  controlCharacteristic = service->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
  );
  controlCharacteristic->setCallbacks(new ControlCallbacks());
  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->setScanResponse(true);
  BLEDevice::startAdvertising();
  Serial.println("Ec電驅 BLE controller ready: ESP32-S3-Car");
}

void loop() {
  delay(20);
}
