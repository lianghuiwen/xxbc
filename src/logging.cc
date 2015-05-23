#include "logging.h"
#include <time.h>
#include <string.h>

namespace xxbc {

Logger* Logger::g_logger_;

const char* const LogLevelName[] = 
{
  "DEBUG",
  "INFO ",
  "WARN ",
  "ERROR",
  "FATAL",
};

Logger::Logger() : fp_(NULL), mutex_(), level_(INFO)
{
}

Logger::~Logger() 
{
    if (fp_) {
        fclose(fp_);
        fp_ = NULL;
    }
}

void Logger::SetFile(const char* filename)
{
    MutexLockGuard lock(mutex_);
    FILE* newfp = fopen(filename, "ae");
    if (newfp) {
        if (fp_) fclose(fp_);
        fp_ = newfp;
    }
}

void Logger::Write(char* buf, uint32_t size) 
{
    // lock
    MutexLockGuard lock(mutex_);
    if (fp_) {
        fwrite(buf, size, 1, fp_);
    }
    fwrite(buf, size, 1, stderr);
}

LogMessage::LogMessage(LogLevel lv) : len_(0), buffer_() 
{
    // current time
    time_t tt = time(NULL);
    tm* tm_time = localtime(&tt);

    // format: [timestamp][level]: 
    int len = snprintf(buffer_, kLogBufferSize, "[%4d-%02d-%02d %02d:%02d:%02d][%s]", 
        tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
        tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec, 
        LogLevelName[lv]);
    len_ += len;
}

LogMessage::LogMessage(const char* file, int line, LogLevel lv) : len_(0), buffer_() 
{
    // current time
    time_t tt = time(NULL);
    tm* tm_time = localtime(&tt);

    // format: [timestamp][level](file, line): 
    int len = snprintf(buffer_, kLogBufferSize, "[%4d-%02d-%02d %02d:%02d:%02d][%s](%s,%d)", 
        tm_time->tm_year + 1900, tm_time->tm_mon + 1, tm_time->tm_mday,
        tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec, 
        LogLevelName[lv], file, line);
    len_ += len;
}

LogMessage::~LogMessage() 
{
    if (len_ > kLogBufferSize - 2) {
        len_ = kLogBufferSize - 2;
    }
    buffer_[len_++] = '\n';
    buffer_[len_++] = '\0';
    Logger::Instance().Write(buffer_, len_);
}

LogMessage& LogMessage::operator<<(char v) 
{
    if (len_ < kLogBufferSize) {
        buffer_[len_++] = v;
    }
    return *this;
}

LogMessage& LogMessage::operator<<(const char* v) 
{
    if (len_ < kLogBufferSize) {
        int len = snprintf(buffer_ + len_, kLogBufferSize - len_, "%s", v);
        if (len > 0) len_ += len;
    }
    return *this;
}

LogMessage& LogMessage::operator<<(const std::string& v) 
{
    if (len_ < kLogBufferSize) {
        int len = snprintf(buffer_ + len_, kLogBufferSize - len_, "%s", v.c_str());
        if (len > 0) len_ += len;
    }
    return *this;
}

LogMessage& LogMessage::operator<<(int32_t v) 
{
    if (len_ < kLogBufferSize) {
        int len = snprintf(buffer_ + len_, kLogBufferSize - len_, "%d", v);
        if (len > 0) len_ += len;
    }
    return *this;
}

LogMessage& LogMessage::operator<<(uint32_t v) 
{
    if (len_ < kLogBufferSize) {
        int len = snprintf(buffer_ + len_, kLogBufferSize - len_, "%d", v);
        if (len > 0) len_ += len;
    }
    return *this;
}

LogMessage& LogMessage::operator<<(double v) 
{
    if (len_ < kLogBufferSize) {
        int len = snprintf(buffer_ + len_, kLogBufferSize - len_, "%.6f", v);
        if (len > 0) len_ += len;
    }
    return *this;
}

} // namespace xxbc
