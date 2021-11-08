
#define LOG(severity) _LOG_##severity

#define CHECK(condition) \
    if (PREDICT_FALSE(!(condition))) \
    LOG(FATAL) << "Check failed: " #condition " "