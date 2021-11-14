
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include "stringprintf.h"

namespace tfcore{
namespace strings{

std::string Printf(const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  std::string result;
  Appendv(&result, format, ap);
  va_end(ap);
  return result;
};

}
}