#ifndef TF_CORE_MACROS_H_
#define TF_CORE_MACROS_H_

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;         \
  void operator=(const TypeName&) = delete

#endif