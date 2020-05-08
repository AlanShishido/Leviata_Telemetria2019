static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

void DadosGPS() {
  /*
  Serial.print("Latitude  : ");
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
  //  Serial.print((unsigned long)TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(),LAT,LON));
  //Serial.println("  (metros)");
  Serial.print("COURSE DEG  : ");
  Serial.println(gps.course.deg(), 1);
  Serial.println("**********************");
  */
  latitude = gps.location.lat();
  longitude = gps.location.lng();
  velocidade = gps.speed.kmph();
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}
