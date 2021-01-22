#include <Arduino.h>
#include <WString.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

#include "../lib/NTPClient/NTPClient.h"
#include <../lib/esp8266-oled-ssd1306/src/SSD1306Wire.h>

#include <Secrets.h>
#include <Helpers.h>
#include <MarsTimeClient.h>


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0, 86400);  // Update once a day
MarsTimeClient marsTimeClient;

SSD1306Wire display(0x3c, SCL, SDA);


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
    Serial.begin(115200);

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
        String marsDate = "Year " + String(marsTimeClient.getSolYear()) + ", Sol " + String(marsTimeClient.getSolDay());
        String marsSolTime = zfill(marsTimeClient.getSolHour(), 2) + ":" +
                             zfill(marsTimeClient.getSolMinute(), 2) + ":" +
                             zfill(marsTimeClient.getSolSecond(), 2);
        String marsMetricTime = zfill(marsTimeClient.getHour(), 2) + ":" +
                                zfill(marsTimeClient.getMinute(), 2) + ":" +
                                zfill(marsTimeClient.getSecond(), 2);

        display.drawHorizontalLine(0, 0, 128);
        display.drawHorizontalLine(0, 63, 128);
        display.drawVerticalLine(0, 0, 64);
        display.drawVerticalLine(127, 0, 64);

//        display.drawString(0, 0, WiFi.SSID() + ": " + WiFi.RSSI() + "dBm");
//        display.drawString(0, 0, getIP());

        display.drawString(2, 5, "UTC: " + getFormattedTime(timeClient) + " " + getFormattedDate(timeClient));
        display.drawString(2, 15, "MSD: " + String(marsTimeClient.getMSD(), 5));
        display.drawString(2, 25, "         " + marsDate);
        display.drawString(2, 35, "MTC: " + marsSolTime);
        display.drawString(2, 45, "MMT: " + marsMetricTime);  // Martian solar day is 24 hrs, 39 min, 35 sec

        display.display();
        delay(10);
    }
    else {
        connectToWiFi();
    }
}