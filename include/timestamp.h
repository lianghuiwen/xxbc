#ifndef XXBC_TIMESTAMP_H_
#define XXBC_TIMESTAMP_H_

#include <stdint.h>
#include <string>

namespace xxbc {

class Timestamp 
{
public:
    Timestamp() : secondsSinceEpoch_(0) {}
    explicit Timestamp(int64_t seconds) : secondsSinceEpoch_(seconds) {}
    
    int64_t SecondsSinceEpoch() const {
        return secondsSinceEpoch_;
    }
    int Hour() const {
        return ((secondsSinceEpoch_ / 3600) + 8) % 24;
    }
    int Minute() const {
        return (secondsSinceEpoch_ / 60) % 60;
    }
    int Second() const {
        return secondsSinceEpoch_ % 60;
    }
    void YearMonDay(int& year, int& mon, int& day) const;
    void HourMinSec(int& hour, int& min, int& sec) const;
    std::string Format() const;
    static Timestamp Now();

private:
    int64_t secondsSinceEpoch_;
};

inline bool operator<(Timestamp lhs, Timestamp rhs)
{
    return lhs.SecondsSinceEpoch() < rhs.SecondsSinceEpoch();
}

inline bool operator>(Timestamp lhs, Timestamp rhs)
{
    return lhs.SecondsSinceEpoch() > rhs.SecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs)
{
    return lhs.SecondsSinceEpoch() == rhs.SecondsSinceEpoch();
}

inline int64_t DiffSeconds(Timestamp lhs, Timestamp rhs)
{
    return rhs.SecondsSinceEpoch() - lhs.SecondsSinceEpoch();
}

inline Timestamp AddSeconds(Timestamp timestamp, int seconds)
{
    return Timestamp(timestamp.SecondsSinceEpoch() + seconds);
}

inline Timestamp NextHourTime(Timestamp timestamp)
{
    int seconds = timestamp.SecondsSinceEpoch() % 3600;
    return Timestamp(timestamp.SecondsSinceEpoch() + 3600 - seconds);
}

inline Timestamp NextDayTime(Timestamp timestamp)
{
    int seconds = (timestamp.SecondsSinceEpoch() + 28800) % 86400;
    return Timestamp(timestamp.SecondsSinceEpoch() + 86400 - seconds);
}

} // namespace xxbc

#endif
