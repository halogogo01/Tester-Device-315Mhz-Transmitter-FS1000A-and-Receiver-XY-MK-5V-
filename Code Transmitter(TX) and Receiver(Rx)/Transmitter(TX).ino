#include <RH_ASK.h>
#include <SPI.h>

// RH_ASK(speed, rxPin, txPin)
// ESP32-C3 Super Mini: GPIO4 = TX data
RH_ASK driver(2000, 99, 3);  // 99 = pin ไม่ใช้ (RX), 4 = TX pin

const int BUTTON_PIN = 1;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // ไม่ต้องใช้ตัวต้านทานภายนอก
  
  if (!driver.init()) {
    Serial.println("RF init failed");
  } else {
    Serial.println("Transmitter ready");
  }
}

void loop() {
  // กดปุ่ม = LOW (เพราะใช้ INPUT_PULLUP)
  if (digitalRead(BUTTON_PIN) == LOW) {
    const char *msg = "TOGGLE";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("Sent: TOGGLE");
    delay(300);  // debounce + ป้องกันส่งซ้ำเร็วเกินไป
  }
}