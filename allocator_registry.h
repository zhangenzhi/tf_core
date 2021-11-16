#ifndef TF_CORE_ALLOCATOR_REGISTRY
#define TF_CORE_ALLOCATOR_REGISTRY

#include <string>
#include <vector>

#include "allocator.h"

namespace tfcore{
class AllocatorFactory{
    public:
        virtual ~AllocatorFactory(){}
        virtual bool NumaEnabled() {return false;}

        virtual Allocator* CreateAllocator() = 0;
        virtual SubAllocator* CreateSubAllocator(int numa_node) = 0;
};


}


#endif