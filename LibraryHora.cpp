#include "LibraryHora.h"

LibraryHora::LibraryHora() : display(0x3c, 5, 4), ntp(udp) {}

void LibraryHora::setup(const char* ssid, const char* password) {
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(2);


}

void LibraryHora::update(const char* ntpServer, long utcOffset) {
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");

  ntp.begin();
  ntp.setUpdateInterval(60000);
  ntp.setTimeOffset(utcOffset);
  ntp.setPoolServerName(ntpServer);
  ntp.update();
}

void LibraryHora::drawTime() {
  String hora = ntp.getFormattedTime();

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);
  display.drawString(63, 26, hora);
  display.display();
}
