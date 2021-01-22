#ifndef ESP_MARS_TIME_HELPERS_H
#define ESP_MARS_TIME_HELPERS_H

#endif //ESP_MARS_TIME_HELPERS_H

#include <WString.h>

#include "../lib/NTPClient/NTPClient.h"

String zfill(String val, int len);
String zfill(int val, int len);

String getFormattedDate(NTPClient &timeClient);
String getFormattedTime(NTPClient &timeClient);
