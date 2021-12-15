#include "pool_allocator.h"

namespace tfcore{

void* BasicCPUAllocator::Alloc(size_t alignment, size_t num_bytes,
              size_t* bytes_received){
    void* ptr = nullptr;
    if num_bytes > 0 {
        ptr = malloc(num_bytes) 
    }
    else{
        std::cout<<"Required mem less than 0."<<std::endl;
    }

    return ptr;
}

void BasicCPUAllocator::Free(void* ptr, size_t num_bytes){
    if (num_bytes > 0) {
        free(ptr);
    }
    else{
        std::cout<<"Required mem less than 0."<<std::endl;
    }
}

} //tfcore 