#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

/*
#include <TinyGPS++.h>
#include <Thread.h>

TinyGPSPlus gps;

Thread Ciclo1;
Thread Ciclo2;

float Lat, Lon;
*/
#define SCK 5   // GPIO5  SCK
#define MISO 19 // GPIO19 MISO
#define MOSI 27 // GPIO27 MOSI
#define SS 18   // GPIO18 CS
#define RST 14  // GPIO14 RESET
#define DI00 26 // GPIO26 IRQ(Interrupt Request)

#define BAND 915E6 //Frequência do radio - exemplo : 433E6, 868E6, 915E6

#define PABOOST true

const String GETDATA = "getdata";
const String SETDATA = "setdata=";
/*
void dadosGPSapp() {
  Lat = gps.location.lat();
  Lon = gps.location.lng();
  
  Serial.print("Latitude : ");
  Serial.println(gps.location.lat(), 6);
  Serial.print("Longitude : ");
  Serial.println(gps.location.lng(), 6);
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());
  Serial.print("Velocity  : ");
  Serial.print(gps.speed.kmph());
  Serial.println("M");
  Serial.print("Time      : ");
  Serial.println(gps.time.value());
  //Serial.print("Distance  : ");
  //Serial.print((unsigned long)TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), LAT, LON));
  //Serial.println("  (metros)");
  Serial.print("COURSE DEG  : ");
  Serial.println(gps.course.deg(), 1);
  Serial.println("**********************");
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(("No GPS data received: check wiring"));
  }

}
*/


void setupLoRa() {
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI00);

  if (!LoRa.begin(BAND)) {

    while (1);
  }

  LoRa.enableCrc();
  LoRa.receive();
}

void setup() {
  Serial.begin(115200);
  //Serial1.begin(9600,SERIAL_8N1, 12, 15);   //17-TX 18-RX
  delay(1000);
  /*
  Ciclo1.setInterval (2000);
  Ciclo1.onRun (dadosGPSapp);
  
  Ciclo2.setInterval (10);
  Ciclo2.onRun (receive);
  */
  setupLoRa();

}

void loop() {
  receive();
  
  /*
  if (Ciclo1.shouldRun()) {
    Ciclo1.run();
  }
  if( Ciclo2.shouldRun()){
    Ciclo2.run();
  }
  */
}

void receive() {
  int packetSize = LoRa.parsePacket();
  if (packetSize > SETDATA.length()) {
    String received = "";
    while (LoRa.available()) {
      received += (char) LoRa.read();
    }
    int index = received.indexOf(SETDATA);
    if (index >= 0) {
      
      /*
      String dados = received.substring(SETDATA.length());
      String message = dados +","+ String(Lat,6) +","+ String(Lon,6);
      */
      String message = received.substring(SETDATA.length());
      Serial.println (message);

      /*
      Serial.print (",");
      Serial.print (Lat, 6);
      Serial.print (",");
      Serial.println (Lon, 6);
      */
    }
  }
}

/*
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}
*/
