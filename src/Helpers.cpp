#include <WString.h>

#include "../lib/NTPClient/NTPClient.h"

String zfill(String val, int len) {
    while (val.length() < len) {
        val = "0" + val;
    }
    return val;
}

String zfill(int val, int len) {
    String str_val(val);
    return zfill(str_val, len);
}


String getFormattedTime(NTPClient &timeClient) {
    return zfill(timeClient.getHours(), 2) + ":" + zfill(timeClient.getMinutes(), 2) + ":" + zfill(timeClient.getSeconds(), 2);
}

String getFormattedDate(NTPClient &timeClient) {
    return zfill(timeClient.getDate(), 2) + "." + zfill(timeClient.getMonth(), 2) + "." + String(timeClient.getYear());
}
