#ifndef TF_CORE_ALLOCATOR_H_
#define TF_CORE_ALLOCATOR_H_

#include <stdlib.h>
#include <functional>
#include <limits>

#include "types.h"
#include "macros.h"

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

    DISALLOW_COPY_AND_ASSIGN(AllocationAttributes);
};

struct AllocatorStats {
    int64_t num_allocs;
    int64_t bytes_in_use;
    int64_t peak_bytes_in_use;
    int64_t largest_alloc_size;
};

}


#endif