#ifndef LOG_H
#define LOG_H

#include<string>
#include<stdint.h>
#include<memory>

#include <list>

namespace sylar {
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent>ptr;
    LogEvent();
private:
    const char*m_filr=nullptr;
    int32_t m_line=0;
    uint32_t m_threadId =0;
    uint32_t m_fiberId=0;
    uint64_t m_time=0;
    std::string m_content;
};
class LogLevel{
public:
    enum Level{
        DEBUG=1,
        INFO=2,
        WARN=3,
        ERROR=4,
        FATAL=5,
    };
};
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    std::string format(LogFormatter::ptr event);
private:
};

//日志输出地
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){};
private:
    LogLevel::Level m_level;
};

//日志器
class Logger{
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name="root");
    void log(LogLevel::Level level,LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addApppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel()const{return m_level;}
    void setLevel(LogLevel::Level val){}
    std::list<LogAppender::ptr> m_appenders;
private:
    LogLevel::Level m_level;
    std::string m_name;

};
class StdoutLogAppender:public LogAppender{
};
class FileLogAppender:public LogAppender{

};
}

#endif // LOG_H
