#include "MarsTimeClient.h"
#include "math.h"


MarsTimeClient::MarsTimeClient() = default;

void MarsTimeClient::update(unsigned long epochTime) {
    this->_epochTime = double(epochTime);
//    this->_msd = ((this->_epochTime - 947116800 + LEAP_SECONDS) / 86400 / 1.027491252) + 44796.0 - 0.00096;
    this->_msd = (this->_epochTime + LEAP_SECONDS) / 88775.244147 + 34127.2954262;  // Mars Sol Date

    this->_solYear = this->_msd / MARS_YEAR;
    this->_solDay = modf(this->_solYear, &this->_solYear) * MARS_YEAR;

    double _;
    this->_solHour = modf(this->_msd, &_) * 24;
    this->_solMinute = modf(this->_solHour, &this->_solHour) * 60;
    this->_solSecond = modf(this->_solMinute, &this->_solMinute) * 60;

    this->_hour = modf(this->_msd, &_) * 24.659790040800004;  // 24.659790040800004;
    this->_minute = modf(this->_hour, &this->_hour) * 60;
    this->_second = modf(this->_minute, &this->_minute) * 60;
}

double MarsTimeClient::getMSD() {
    return this->_msd;
}

int MarsTimeClient::getSolYear() {
    return int(this->_solYear);
}

int MarsTimeClient::getSolDay() {
    return int(this->_solDay);
}

int MarsTimeClient::getSolHour() {
    return int(this->_solHour);
}

int MarsTimeClient::getSolMinute() {
    return int(this->_solMinute);
}

int MarsTimeClient::getSolSecond() {
    return int(this->_solSecond);
}

int MarsTimeClient::getHour() {
    return int(this->_hour);
}

int MarsTimeClient::getMinute() {
    return int(this->_minute);
}

int MarsTimeClient::getSecond() {
    return int(this->_second);
}
