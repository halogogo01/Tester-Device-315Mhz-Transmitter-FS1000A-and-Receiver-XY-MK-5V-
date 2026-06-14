#include <RH_ASK.h>
#include <SPI.h>

// RH_ASK(speed, rxPin, txPin)
// ESP32-C3 Super Mini: GPIO4 = RX data
RH_ASK driver(2000, 5, 99);  // 4 = RX pin, 99 = TX ไม่ใช้

const int LED_PIN = 2;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  if (!driver.init()) {
    Serial.println("RF init failed");
  } else {
    Serial.println("Receiver ready");
  }
}

void loop() {
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  
  if (driver.recv(buf, &buflen)) {
    buf[buflen] = '\0';  // null terminate
    String msg = String((char*)buf);
    Serial.print("Received: ");
    Serial.println(msg);
    
    if (msg == "TOGGLE") {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      Serial.println(ledState ? "LED ON" : "LED OFF");
    }
  }
}