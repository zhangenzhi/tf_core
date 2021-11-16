#include "logging.h"

namespace tf_core{

LogMessage::LogMessage(const char* fname, int line, int severity)
    : fname_(fname), line_(line), severity_(severity) {}

LogMessage& LogMessage::AtLocation(const char* fname, int line) {
  fname_ = fname;
  line_ = line;
  return *this;
}

LogMessage::~LogMessage() {
  // Read the min log level once during the first call to logging.
  // static int64_t min_log_level = MinLogLevelFromEnv();
  // if (severity_ >= min_log_level) {
  //   GenerateLogMessage();
  // }
}

// void LogMessage::GenerateLogMessage() {
//   TFLogSinks::Instance().Send(TFLogEntry(severity_, fname_, line_, str()));
// }

// int64_t LogMessage::MaxVLogLevel() {
//   static int64_t max_vlog_level = MaxVLogLevelFromEnv();
//   return max_vlog_level;
// }

// bool LogMessage::VmoduleActivated(const char* fname, int level) {
//   if (level <= MaxVLogLevel()) {
//     return true;
//   }
//   static VmoduleMap* vmodules = VmodulesMapFromEnv();
//   if (TF_PREDICT_TRUE(vmodules == nullptr)) {
//     return false;
//   }
//   const char* last_slash = strrchr(fname, '/');
//   const char* module_start = last_slash == nullptr ? fname : last_slash + 1;
//   const char* dot_after = strchr(module_start, '.');
//   const char* module_limit =
//       dot_after == nullptr ? strchr(fname, '\0') : dot_after;
//   StringData module(module_start, module_limit - module_start);
//   auto it = vmodules->find(module);
//   return it != vmodules->end() && it->second >= level;
// }

LogMessageFatal::LogMessageFatal(const char* file, int line)
    : LogMessage(file, line, FATAL) {}
    
LogMessageFatal::~LogMessageFatal() {
  // abort() ensures we don't return (we promised we would not via
  // ATTRIBUTE_NORETURN).
  GenerateLogMessage();
  abort();
}

}