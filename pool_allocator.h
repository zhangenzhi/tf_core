#ifndef TF_CORE_POOL_ALLOCATOR_H_
#define TF_CORE_POOL_ALLOCATOR_H_

#include <stdlib.h>
#include <vector>
#include <string>

#include "allocator.h"

namespace tfcore{

struct PtrRecord {
    void* ptr;
    size_t num_bytes;
    PtrRecord* prev;
    PtrRecord* next;
};

class PoolAllocator: public Allocator{
    public:
        PoolAllocator(size_t pool_size_limit, bool auto_resize, 
                    SubAllocator* allocator,RoundUpInterface* size_rounder,
                    string name)
        ~PoolAllocator() override;
        string Name() override { return name_; }

        void* AllocateRaw(size_t alignment, size_t num_bytes) override;
        void DeallocateRaw(void* ptr) override;

        void* Get(size_t num_bytes);
        void Put(void* ptr, size_t num_bytes);
        void Clear();

    private:
        void RemoveFromList(PtrRecord* pr);
        void AddToList(PtrRecord* pr);
        void EvictOne();

        const string name_;

};

class BasicCPUAllocator : public SubAllocator{
    public:

        BasicCPUAllocator(int numa_node=0, const std::vector<Visitor>& alloc_visitors,
                        const std::vector<Visitor>& free_visitors)
        : SubAllocator(alloc_visitors, free_visitors), numa_node_(numa_node) {}

        ~BasicCPUAllocator() override {}

        void* Alloc(size_t alignment, size_t num_bytes,
            size_t* bytes_received) override;

        void Free(void* ptr, size_t num_bytes) override;

        bool SupportsCoalescing() const override { return false; }

    private:
        int numa_node_;
};

}// tfcore
#endif