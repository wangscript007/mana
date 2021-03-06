#ifndef __LOGGER_H_
#define __LOGGER_H_
#include "macros.h"
#include "udt.h"
#include "lock.h"
#include "singleton.h"
#include "ringbuffer.h"

struct _IO_FILE;
typedef struct _IO_FILE FILE;

NMS_BEGIN(klog)

enum LogLevel {
	LL_FATAL = 0,
	LL_ERROR = 1,
	LL_WARNING = 2,
	LL_NOTICE = 3,
	LL_INFO = 4,
	LL_DEBUG = 5,
	LL_MAX
};

class Logger : public kcommon::Singleton<klog::Logger> {
public:
	Logger() : _fp(0), _active(false), _limit(LL_MAX), _last_create_time(0), _thread_id(0) {}
	~Logger();

	int32 open(LogLevel limit, const char *prefix, const char *path="./log/");

	void close();

	void log(const char *file, const char *func, uint32 line, LogLevel lv, const char *fmt, ...);

private:
	Logger(const Logger &other) {}
	Logger& operator = (const Logger &rh) { return *this; }

private:
	void log_file_checking();

	void flush();

	static void* io_routine(void *arg);

private:
	FILE *_fp;
	volatile bool _active;
	LogLevel _limit;
	char _log_prefix[64];
	char _log_path[64];
	uint64 _last_create_time;
	uint64 _thread_id;
	kcommon::RingBuffer<char> _log_buffer;
};

NMS_END // end namespace klog

#define LOG_FATAL(FMT, ...) klog::Logger::instance()->log(__FILE__, __FUNCTION__, __LINE__, klog::LL_FATAL, FMT, ##__VA_ARGS__)
#define LOG_ERROR(FMT, ...) klog::Logger::instance()->log(__FILE__, __FUNCTION__, __LINE__, klog::LL_ERROR, FMT, ##__VA_ARGS__)
#define LOG_WARNING(FMT, ...) klog::Logger::instance()->log(__FILE__, __FUNCTION__, __LINE__, klog::LL_WARNING, FMT, ##__VA_ARGS__)
#define LOG_NOTICE(FMT, ...) klog::Logger::instance()->log(__FILE__, __FUNCTION__, __LINE__, klog::LL_NOTICE, FMT, ##__VA_ARGS__)
#define LOG_INFO(FMT, ...) klog::Logger::instance()->log(__FILE__, __FUNCTION__, __LINE__, klog::LL_INFO, FMT, ##__VA_ARGS__)
#define LOG_DEBUG(FMT, ...) klog::Logger::instance()->log(__FILE__, __FUNCTION__, __LINE__, klog::LL_DEBUG, FMT, ##__VA_ARGS__)

#endif // __LOGGER_H_

