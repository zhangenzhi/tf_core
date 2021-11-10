#ifndef TF_CORE_STRINGPRINTF
#define TF_CORE_STRINGPRINTF

#include <string>
#include "macros.h"
#include "types.h"

namespace tfcore{
namespace strings{
// Return a C++ string
extern std::string Printf(const char* format, ...)
    // Tell the compiler to do printf format string checking.
    TF_PRINTF_ATTRIBUTE(1, 2);
} //namespcae strings
} //namespace tfcore

#endif