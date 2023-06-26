#ifndef LibraryHora_h
#define LibraryHora_h

#include <Wire.h>
#include "SH1106Wire.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

class LibraryHora {
  private:
    SH1106Wire display;
    WiFiUDP udp;
    NTPClient ntp;

  public:
    LibraryHora();

    void setup(const char* ssid, const char* password);
    void update(const char* ntpServer, long utcOffset);
    void drawTime();
};

#endif
