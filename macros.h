#ifndef TF_CORE_MACROS_H_
#define TF_CORE_MACROS_H_

#define TF_ATTRIBUTE_NORETURN __attribute__((noreturn))
#define TF_ATTRIBUTE_NOINLINE __attribute__((noinline))
#define TF_ATTRIBUTE_COLD __attribute__((cold))


#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;         \
  void operator=(const TypeName&) = delete

#define PRINTF_ATTRIBUTE(string_index, first_to_check) \
  __attribute__((__format__(__printf__, string_index, first_to_check)))

#define PREDICT_FALSE(x) (x)
#define PREDICT_TRUE(x) (x)


#endif