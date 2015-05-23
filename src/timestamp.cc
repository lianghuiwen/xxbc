#include "timestamp.h"
#include <sys/time.h>

namespace xxbc {

Timestamp Timestamp::Now() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return Timestamp(tv.tv_sec);
}

void Timestamp::YearMonDay(int& year, int& mon, int& day) const
{
    struct tm tm_time;
    localtime_r(&secondsSinceEpoch_, &tm_time);
    year = tm_time.tm_year + 1900;
    mon = tm_time.tm_mon + 1;
    day = tm_time.tm_mday;
}

void Timestamp::HourMinSec(int& hour, int& min, int& sec) const
{
    struct tm tm_time;
    localtime_r(&secondsSinceEpoch_, &tm_time);
    hour = tm_time.tm_hour;
    min = tm_time.tm_min;
    sec = tm_time.tm_sec;
}

std::string Timestamp::Format() const
{
    char buf[20] = {0};
    struct tm tm_time;
    //gmtime_r(&secondsSinceEpoch_, &tm_time);
    localtime_r(&secondsSinceEpoch_, &tm_time); // 时区
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d",
        tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
        tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  return buf;
}

} // namespace xxbc
