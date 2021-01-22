#include <Arduino.h>
#include <WString.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

#include "../lib/NTPClient/NTPClient.h"
#include <../lib/esp8266-oled-ssd1306/src/SSD1306Wire.h>

#include <Secrets.h>
#include <MarsTimeClient.h>


SSD1306Wire display(0x3c, SCL, SDA);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0, 86400);  // Update once a day
MarsTimeClient marsTimeClient;
char buffer[64];


void connectToWiFi() {
    char *indicator[4] = {"\\", "|", "/", "--"};
    int i = 0;

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        display.clear();
        display.drawString(0, 0, "Connecting to WiFi   " + String(indicator[i]));
        display.display();
        delay(100);

        i++;
        if (i == 4) i = 0;
    }
}

String getIP()
{
    IPAddress localIP = WiFi.localIP();
    return String(localIP[0]) + "." + String(localIP[1]) + "." + String(localIP[2]) + "." +  String(localIP[3]);
}


void setup() {
    display.init();
    display.setContrast(255);
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);

    WiFi.softAPdisconnect(true);
    connectToWiFi();

    timeClient.begin();
    timeClient.update();
    timeClient.update();
    timeClient.update();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        display.clear();

        marsTimeClient.update(timeClient.getEpochTime());

        display.drawHorizontalLine(0, 0, 128);
        display.drawHorizontalLine(0, 63, 128);
        display.drawVerticalLine(0, 0, 64);
        display.drawVerticalLine(127, 0, 64);

//        display.drawString(0, 0, WiFi.SSID() + ": " + WiFi.RSSI() + "dBm");
//        display.drawString(0, 0, getIP());

        display.drawStringf(2, 5,  buffer, "UTC: %02d:%02d:%02d %02d.%02d.%i",
                            timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds(),
                            timeClient.getDay(), timeClient.getMonth(), timeClient.getYear());
        display.drawStringf(2, 15, buffer, "MSD: %.8f",
                            marsTimeClient.getMSD());
        display.drawStringf(2, 25, buffer, "         Year %i, Sol %i",
                            marsTimeClient.getSolYear(), marsTimeClient.getSolDay());
        display.drawStringf(2, 35, buffer, "MTC: %02d:%02d:%02d",
                            marsTimeClient.getSolHour(), marsTimeClient.getSolMinute(), marsTimeClient.getSolSecond());
        display.drawStringf(2, 45, buffer, "MMT: %02d:%02d:%02d",
                            marsTimeClient.getHour(), marsTimeClient.getMinute(), marsTimeClient.getSecond());  // Martian solar day is 24 hrs, 39 min, 35 sec

        display.display();
        delay(10);
    }
    else {
        connectToWiFi();
    }
}