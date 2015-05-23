#include "logging.h"
using namespace xxbc;

int main(int argc, char* argv[])
{
    LOG_SET_FILE("test.log");
    LOG_SET_LEVEL(DEBUG);
    LOG(INFO) << "info log." << 100;
    LOG(WARN) << "warn log." << -100;
    LOG(ERROR) << "error log." << 100.123;
    LOG(FATAL) << "fatal log." << 'F';
}

