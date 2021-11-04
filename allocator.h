#ifndef TF_CORE_ALLOCATOR_H_
#define TF_CORE_ALLOCATOR_H_

#include <stdlib.h>
#include <functional>
#include <limits>

#include "types.h"

namespace tfcore{

struct AllocationAttributes {

    AllocationAttributes() = default;

    AllocationAttributes(bool retry_on_failure, bool allocation_will_be_logged,
                         std::function<uint64()>* freed_by_func)
        : retry_on_failure(retry_on_failure),
          allocation_will_be_logged(allocation_will_be_logged),
          freed_by_func(freed_by_func) {}

    bool retry_on_failure = true;

    bool allocation_will_be_logged = false;

    std::function<uint64()>* freed_by_func = nullptr;

    TF_DISALLOW_COPY_AND_ASSIGN(AllocationAttributes);
};

}


#endif