#ifndef TF_CORE_LOGGING_H_
#define TF_CORE_LOGGING_H_

#include <sstream>

#include "macros.h"
#include "types.h"

#undef ERROR

namespace tf_core{

const int INFO = 0;            // base_logging::INFO;
const int WARNING = 1;         // base_logging::WARNING;
const int ERROR = 2;           // base_logging::ERROR;
const int FATAL = 3;           // base_logging::FATAL;
const int NUM_SEVERITIES = 4;  // base_logging::NUM_SEVERITIES;

class LogMessage : public std::basic_ostringstream<char> {
    public:
        LogMessage(const char* fname, int line, int severity);
        ~LogMessage() override;

        LogMessage& AtLocation(const char* fname, int line);

        static int64_t MaxVLogLevel();
        static bool VmoduleActivated(const char* fname, int level);

    protected:
        void GenerateLogMessage();

    private:
        const char* fname_;
        int line_;
        int severity_;
};

class LogMessageFatal : public LogMessage {
 public:
  LogMessageFatal(const char* file, int line) TF_ATTRIBUTE_COLD;
  TF_ATTRIBUTE_NORETURN ~LogMessageFatal() override;
};


#define _LOG_FATAL ::tf_core::LogMessageFatal(__FILE__, __LINE__)


#define LOG(severity) _LOG_##severity

#define CHECK(condition) \
    if (PREDICT_FALSE(!(condition))) \
    LOG(FATAL) << "Check failed: " #condition " "

}

#endif