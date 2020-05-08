int i = 0, j = 0;

void listen() {
  int valor, lerPacote, pacote[5];
  
  lerPacote = udp.parsePacket();

  if (lerPacote > 0) {
    req = "";
    while (udp.available() > 0) {
      char z = udp.read();
      req += z;
      pacote[j] = atoi(&z);
      j++;
    }
    
    switch (req.length()) {
      case 1: valor = pacote[0];
        break;
      case 2: valor = pacote[0] * 10 +  pacote[1];
        break;
      case 3: valor =  pacote[0] * 100 +  pacote[1] * 10 +  pacote[2];
        break;
      default: valor = 0; break;
    }
    
    if (valor == 999) {
      i = 0;
      valor = -1;
      Serial.println();
    }
    
    j = 0;
    BMS_byte[i] = valor;
    
      Serial.print(BMS_byte[i]);
      Serial.print(" ");
    
    i++;

  }

  if (i >= 58) {
    Serial.println();
    PickDataBMS = true;
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
  
    i = 0;
  }
}
