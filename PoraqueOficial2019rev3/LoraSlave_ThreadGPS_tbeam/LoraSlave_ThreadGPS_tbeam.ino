/*
  Slave era utilizado na com 3, ele que recebe os dados do BMS e envia via Lora
*/

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h> //Biblioteca do UDP.
#include <Thread.h>
#include <TinyGPS++.h>

Thread Estado1;

TinyGPSPlus gps;

bool PickDataBMS = false;

WiFiUDP udp;

String req;

#define LED 14

int BMS_byte[58];
int celula, estado_de_carga, temperatura_celula, temperatura_minima, temperatura_maxima;
float tensao_total, corrente_entrada, corrente_saida, tensao_celula, tensao_minima, tensao_maxima;
float latitude, longitude, velocidade;

#define SCK 5   // GPIO5  SCK
#define MISO 19 // GPIO19 MISO
#define MOSI 27 // GPIO27 MOSI
#define SS 18   // GPIO18 CS
#define RST 23  // GPIO14 RESET
#define DI00 26 // GPIO26 IRQ(Interrupt Request)

#define BAND 915E6

const String GETDATA = "getdata";
const String SETDATA = "setdata=";

void setupLoRa() {
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI00);

  if (!LoRa.begin(BAND)) {
    while (1);
  }

  LoRa.enableCrc();
  LoRa.receive();
}
/*
int indicepacket = 0, tempo = 0; //so na funcionalidade da função testOffline
#define INTERVALO 2000
void TestOffline() {
  if ((millis() - tempo) >= INTERVALO) {
    LoRa.beginPacket();
    LoRa.print(SETDATA);
    LoRa.print(random(0, 60));
    //LoRa.print(tensao_total);
    LoRa.print(",");
    LoRa.print(random(0, 100));
    //LoRa.print(corrente_entrada);
    LoRa.print(",");
    LoRa.print(random(0, 100));
    //LoRa.print(corrente_saida);
    LoRa.print(",");
    LoRa.print(random(0, 5));
    //LoRa.print(tensao_minima);
    LoRa.print(",");
    LoRa.print(random(0, 5));
    //LoRa.print(tensao_maxima);
    LoRa.print(",");
    LoRa.print(random(0, 100));
    //LoRa.print(estado_de_carga);
    LoRa.print(",");
    LoRa.print(random(0, 12));
    //LoRa.print(celula);
    LoRa.print(",");
    LoRa.print(random(0, 5));
    //LoRa.print(tensao_celula);
    LoRa.print(",");
    LoRa.print(velocidade,2);
    LoRa.print(",");
    LoRa.print(latitude, 6);
    LoRa.print(",");
    LoRa.print(longitude, 6);
    LoRa.endPacket();

    Serial.println("LoRa enviado");
    tempo = millis();
  }
}
*/

void setup() {
  Serial.begin(115200);

  setupLoRa();

  Estado1.setInterval(1000);
  Estado1.onRun(DadosGPS);

  Serial1.begin(9600, SERIAL_8N1, 12, 15);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 1);

  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("Levita", "poraque123");
  delay(2000);

  udp.begin(555);
}

void loop() {
  if (!PickDataBMS) {
    //while (!PickDataBMS) {
    listen();
  }
  else if (PickDataBMS) {
    LoRa.beginPacket();
    LoRa.print(SETDATA);
    LoRa.print(tensao_total);
    LoRa.print(",");
    LoRa.print(corrente_entrada);
    LoRa.print(",");
    LoRa.print(corrente_saida);
    LoRa.print(",");
    LoRa.print(tensao_minima);
    LoRa.print(",");
    LoRa.print(tensao_maxima);
    LoRa.print(",");
    LoRa.print(estado_de_carga);
    LoRa.print(",");
    LoRa.print(celula);
    LoRa.print(",");
    LoRa.print(tensao_celula);
    LoRa.print(",");
    LoRa.print(velocidade,2);
    LoRa.print(",");
    LoRa.print(latitude, 6);
    LoRa.print(",");
    LoRa.print(longitude, 6);
    LoRa.endPacket();
    PickDataBMS = false;
  }
  
  if (Estado1.shouldRun()) {
    Estado1.run();
  }

  //TestOffline();
}
