//
// 注意snprintf在不同平台下的不同实现
// 独立线程缓存多个slot时间戳，参考nginx
//

#ifndef XXBC_LOGGING_H_
#define XXBC_LOGGING_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include "mutexlock.h"

#define LOG_SET_FILE(filename)  Logger::Instance().SetFile(filename)
#define LOG_SET_LEVEL(level)    Logger::Instance().SetLevel(level)
#define LOG(level)  if (level >= Logger::Instance().Level()) LogMessage(level)

namespace xxbc {

const int kLogBufferSize = 1024;

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger {
public:
    // 获取实例
    static Logger& Instance() {
        if (g_logger_ == NULL) {
            g_logger_ = new Logger();
        }
        return *g_logger_;
    }
    // 返回日志级别
    LogLevel Level() {
        return level_;
    }
    // 设置日志级别
    void SetLevel(LogLevel lv) {
        level_ = lv;
    }
    // 设置日志文件
    void SetFile(const char* filename);
    // 写日志
    void Write(char* buf, uint32_t size);

protected:
    Logger();
    ~Logger();

    // No copying allowed
    Logger(const Logger&);
    void operator=(const Logger&);

private:
    FILE* fp_;
    Mutex mutex_;
    LogLevel level_;
    static Logger* g_logger_;
};


class LogMessage {
public:
    LogMessage(LogLevel lv);
    LogMessage(const char* file, int line, LogLevel lv);
    ~LogMessage();

    LogMessage& operator<<(char v);
    LogMessage& operator<<(const char* v);
    LogMessage& operator<<(const std::string& v);
    LogMessage& operator<<(int32_t v);
    LogMessage& operator<<(uint32_t v);
    LogMessage& operator<<(double v);

private:
    int len_;
    char buffer_[kLogBufferSize];
};

} // namespace xxbc

#endif
