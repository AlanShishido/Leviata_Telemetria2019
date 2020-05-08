
#include <WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define RXD 16
#define TXD 17

WiFiUDP udp;
int x, i = 0; //x é aquisição UDP e i indice

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD, TXD);
  Serial.println("Serial COM Conected");
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(6, 0);
  lcd.print("Leviata");
  lcd.setCursor(0, 3);
  lcd.print("Iniciando...");
  
}

void loop() { 
  connect();
    while (Serial2.available()) {
    BMS_decode();
  }
}

void connect()
{
   if (WiFi.status() != WL_CONNECTED)
   {
      WiFi.begin("Levita", "poraque123");
      delay(1000);
   }
}
