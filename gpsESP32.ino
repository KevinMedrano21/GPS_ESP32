#include <TinyGPS++.h>

#define GPS_BAUDRATE 9600
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  //GPIO16 (RX) y GPIO17 (TX) para Serial2, usar estos pines.
  Serial2.begin(GPS_BAUDRATE);
  Serial.println(F("ESP32 - Módulo GPS"));
}

void loop() {
  if (Serial2.available() > 0) {
    if (gps.encode (Serial2.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitud: "));
        Serial.println(gps.location.lat ());
        Serial.print(F("- longitud: "));
        Serial.println(gps.location.lng ());
        Serial.print(F("- altitud: "));
        if (gps.altitude.isValid()) Serial.println(gps.altitude.meters ());
        else Serial.println(F("INVÁLIDA"));
      } else {
        Serial.println(F("- ubicación: INVÁLIDA"));
      }
      Serial.print(F("- velocidad: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.kmph ());
        Serial.println(F(" km/h"));
      } else {
        Serial.println(F("INVÁLIDA"));
      }
      Serial.print(F("- fecha y hora del GPS: "));
      if (gps.date.isValid() && gps.time.isValid()) {
        Serial.print(gps.date.year());
        Serial.print(F("-"));
        Serial.print(gps.date.month());
        Serial.print(F("-"));
        Serial.print(gps.date.day());
        Serial.print(F(" "));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        Serial.println(gps.time.second());
      } else {
        Serial.println(F("INVÁLIDA"));
      }
      Serial.println();
    }
  }
  if (millis() > 5000 && gps.charsProcessed () < 10)
    Serial.println(F("No se reciben datos del GPS: revisa el cableado"));
}