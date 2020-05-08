void BMS_decode() {

  int BMS_byte[58], celula, estado_de_carga, temperatura_celula, temperatura_minima, temperatura_maxima;
  float tensao_total, corrente_entrada, corrente_saida, tensao_celula, tensao_minima, tensao_maxima;
  if (Serial2.available()) {
    BMS_byte [i] = Serial2.read();
    x = BMS_byte [i];
    //if (i == 0) {
   //   x = 999;
    //}

    //if (i == 0 || 1 || 2 || 4 || 5 || 7 || 8 || 12 || 13 || 15 || 16 || 40) {
    send();
    //}

    Serial.print (x);
    Serial.print(" ");

    i++;
  }


  if (i >= 58) {
    Serial.println();
    tensao_total = (BMS_byte[1] * 256 + BMS_byte[2]) * 0.005;
    corrente_entrada = (BMS_byte[4] * 256 + BMS_byte[5]) * 0.125;
    corrente_saida = (BMS_byte[7] * 256 + BMS_byte[8]) * 0.125;
    tensao_minima = (BMS_byte[12] * 256 + BMS_byte[13]) * 0.005;
    tensao_maxima = (BMS_byte[15] * 256 + BMS_byte[16]) * 0.005;
    temperatura_minima = (BMS_byte[18] * 256 + BMS_byte[19]) - 276;
    temperatura_maxima = (BMS_byte[21] * 256 + BMS_byte[22]) - 276;
    celula = BMS_byte[24];
    tensao_celula = (BMS_byte[26] * 256 + BMS_byte[27]) * 0.005;
    temperatura_celula = (BMS_byte[28] * 256 + BMS_byte[29]) - 276;
    estado_de_carga = BMS_byte[40];

    
        Serial.print(tensao_total);
        Serial.print(",");
        Serial.print(corrente_entrada);
        Serial.print(",");
        Serial.print(corrente_saida);
        Serial.print(",");
        Serial.print(tensao_minima);
        Serial.print(",");
        Serial.print(tensao_maxima);
        Serial.print(",");
        Serial.print(estado_de_carga);
        Serial.println();
    

    if (tensao_total <= 60) {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("TELEMETRIA");

      lcd.setCursor(0, 1);
      lcd.print("Vt: ");
      lcd.setCursor(5, 1);
      lcd.print(tensao_total);

      lcd.setCursor(0, 2);
      lcd.print("Ii: ");
      lcd.setCursor(5, 2);
      lcd.print(corrente_entrada);

      lcd.setCursor(0, 3);
      lcd.print("Io: ");
      lcd.setCursor(5, 3);
      lcd.print(corrente_saida);

      lcd.setCursor(11, 1);
      lcd.print("V-: ");
      lcd.setCursor(16, 1);
      lcd.print(tensao_minima);

      lcd.setCursor(11, 2);
      lcd.print("V+: ");
      lcd.setCursor(16, 2);
      lcd.print(tensao_maxima);

      lcd.setCursor(12, 3);
      lcd.print("SOC:");
      lcd.setCursor(17, 3);
      lcd.print(estado_de_carga);
    }
    
    i = 0;
  }
}

void send() {
  if (WiFi.status() == WL_CONNECTED) {
    udp.beginPacket("192.168.4.1", 555);
    udp.print(x);
    udp.endPacket();

  }
  else {

  }
}
