#include <stdio.h>
#include "timestamp.h"
using namespace xxbc;
using namespace std;

int main(int argc, char* argv[])
{
    Timestamp t1;
    Timestamp t2 = Timestamp::Now();
    Timestamp t3 = AddSeconds(t2, 60*60);
    Timestamp t4 = NextHourTime(t2);
    Timestamp t5 = NextDayTime(t2);
    printf("t1: %s\n", t1.Format().c_str());
    printf("t2: %s\n", t2.Format().c_str());
    printf("t3: %s\n", t3.Format().c_str());
    printf("t4: %s\n", t4.Format().c_str());
    printf("t5: %s\n", t5.Format().c_str());
    printf("t3-t2: %d\n", DiffSeconds(t2, t3));
    printf("t2==t3: %d\n", t2 == t3);
    printf("t2<t3: %d\n", t2 < t3);
    printf("t2.hour: %d\n", t2.Hour());
    printf("t2.minute: %d\n", t2.Minute());
    printf("t2.second: %d\n", t2.Second());
}

