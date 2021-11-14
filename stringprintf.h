#ifndef TF_CORE_STRINGPRINTF
#define TF_CORE_STRINGPRINTF

#include <string>
#include <stdarg.h>

#include "macros.h"
#include "types.h"

namespace tfcore{
namespace strings{
// Return a C++ string
extern std::string Printf(const char* format, ...)
    // Tell the compiler to do printf format string checking.
    PRINTF_ATTRIBUTE(1, 2);

// Append result to a supplied string
extern void Appendf(std::string* dst, const char* format, ...)
    // Tell the compiler to do printf format string checking.
    PRINTF_ATTRIBUTE(2, 3);

// Lower-level routine that takes a va_list and appends to a specified
// string.  All other routines are just convenience wrappers around it.
extern void Appendv(std::string* dst, const char* format, va_list ap);


} //namespcae strings
} //namespace tfcore

#endif