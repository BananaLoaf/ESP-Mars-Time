#ifndef ESP_MARS_TIME_MARSTIMECLIENT_H
#define ESP_MARS_TIME_MARSTIMECLIENT_H

#endif //ESP_MARS_TIME_MARSTIMECLIENT_H

#define LEAP_SECONDS 37.0
#define MARS_YEAR 668.5991  // In sols

class MarsTimeClient {
    private:
        double _epochTime = 0;
        double _msd = 0.0;

        double _solYear = 0.0;
        double _solDay = 0.0;

        double _solHour = 0.0;
        double _solMinute = 0.0;
        double _solSecond = 0.0;

        double _hour = 0.0;
        double _minute = 0.0;
        double _second = 0.0;
    public:
        MarsTimeClient()  = default;

        void update(unsigned long epochTime);
        double getMSD();
        int getSolYear();
        int getSolDay();

        int getSolHour();
        int getSolMinute();
        int getSolSecond();

        int getHour();
        int getMinute();
        int getSecond();
};
