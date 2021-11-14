#ifndef TF_CORE_ALLOCATOR_H_
#define TF_CORE_ALLOCATOR_H_

#include <vector>
#include <stdlib.h>
#include <functional>
#include <limits>

#include "types.h"
#include "macros.h"
#include "logging.h"

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

    // absl::optional<int64_t> bytes_limit;

    int64_t bytes_reserved;
    int64_t peak_bytes_reserved;

    // absl::optional<int64_t> bytes_reservable_limit;

    int64_t largest_free_block_bytes;

    AllocatorStats()
        : num_allocs(0),
          bytes_in_use(0),
          peak_bytes_in_use(0),
          largest_alloc_size(0),
          bytes_reserved(0),
          peak_bytes_reserved(0),
          largest_free_block_bytes(0) {}

    std::string DebugString() const;
};

// class Allocator {
//     public:
//         static constexpr size_t kAllocatorAlignment = 64;

//         virtual std::string Name() = 0;

//         virtual ~Allocator();

//         virtual void* AllocateRaw(size_t alignment, size_t num_bytes) = 0;

//         virtual void* AllocateRaw(size_t alignment, size_t num_bytes,
//                                   const AllocationAttributes& allocation_attr) {
//             return AllocateRaw(alignment,num_bytes);
//         }

//         virtual void DeallocateRaw(void* ptr) = 0;
//         virtual bool TracksAllocationSizes() const {return false;}
//         virtual bool AllocatesOpaqueHandle() const { return false; }

//         virtual size_t RequestedSize(const void* ptr) const {
//             CHECK(false) << "allocator doesn't track sizes.";
//             return size_t(0);
//         }

//         virtual size_t AllocatedSize(const void* ptr) const {    
//             return RequestedSize(ptr);
//         }

//         virtual int64_t AllocationId(const void* ptr) const { return 0; }

//         virtual size_t AllocatedSizeSlow(const void* ptr) const {
//             if (TracksAllocationSizes()) {
//                 return AllocatedSize(ptr);
//             }
//             return 0;
//         }

//         virtual void SetSafeFrontier(uint64 count) {}
//         virtual void SetStreamAndPreallocateMemory(void* stream) {}
// };

// class AllocatorWrapper : public Allocator{
//     public:
//         explicit AllocatorWrapper(Allocator* wrapped) : wrapped_(wrapped) {}

//         ~AllocatorWrapper() override {}

//         Allocator* wrapped() const { return wrapped_; }

//         std::string Name() override { return wrapped_->Name(); }

//         void* AllocateRaw(size_t alignment, size_t num_bytes) override {
//             return wrapped_->AllocateRaw(alignment, num_bytes);
//         }
//         void* AllocateRaw(size_t alignment, size_t num_bytes,
//                           const AllocationAttributes& allocation_attr) override {
//             return wrapped_->AllocateRaw(alignment, num_bytes, allocation_attr);
//         }

//         void DeallocateRaw(void* ptr) override { wrapped_->DeallocateRaw(ptr); }    

//         bool TracksAllocationSizes() const override {
//             return wrapped_->TracksAllocationSizes();
//         }

//         bool AllocatesOpaqueHandle() const override {
//             return wrapped_->AllocatesOpaqueHandle();
//         }

//         size_t RequestedSize(const void* ptr) const override {
//             return wrapped_->RequestedSize(ptr);
//         }

//         size_t AllocatedSize(const void* ptr) const override {
//             return wrapped_->AllocatedSize(ptr);
//         }

//         int64_t AllocationId(const void* ptr) const override {
//             return wrapped_->AllocationId(ptr);
//         }

//         size_t AllocatedSizeSlow(const void* ptr) const override {
//             return wrapped_->AllocatedSizeSlow(ptr);
//         }

//     private:
//         Allocator* const wrapped_;
// };

// struct AllocatorAttributes {
//     void set_on_host(bool v) { value |= (static_cast<int>(v));}
//     bool on_host() const { return value & 0x1; }
//     void set_nic_compatible(bool v) { value |= (static_cast<int>(v) << 1); }
//     bool nic_compatible() const { return value & (0x1 << 1); }
//     void set_gpu_compatible(bool v) { value |= (static_cast<int>(v) << 2); }
//     bool gpu_compatible() const { return value & (0x1 << 2); }
//     void Merge(AllocatorAttributes other){
//         value |= other.value;
//         if (scope_id != other.scope_id){
//             CHECK(scope_id == 0 || other.scope_id == 0)
//                 <<"At least one scope_id should be zero to merge "
//                   "AllocatorAttributes but found this.scope_id="
//                 << scope_id << " and other.scope_id=" << other.scope_id;
//             scope_id = scope_id == 0 ? other.scope_id : scope_id;
//         }
//     }

//     bool IsEqualOrLessRestrictiveThan(const AllocatorAttributes& other) const{
//         return (value | other.value) == other.value;
//     }

//     uint32 value = 0;
//     int32 scope_id = 0;
//     std::string DebugString() const;

// };

// Allocator* cpu_allocator_base();

// Allocator* cpu_allocator(int numa_node = 0);

// // Enables AllocatorStats in the default CPU allocator implementation.  By
// // default, it's disabled.
// void EnableCPUAllocatorStats();
// // Disables AllocatorStats in the default CPU allocator implementation.  By
// // default, it's disabled.
// void DisableCPUAllocatorStats();
// bool CPUAllocatorStatsEnabled();

// // Enables full statistics collection in the default CPU allocator
// // implementation.  By default, it's disabled.
// void EnableCPUAllocatorFullStats();
// bool CPUAllocatorFullStatsEnabled();

// // An object that does the underlying suballoc/free of memory for a higher-level
// // allocator.  The expectation is that the higher-level allocator is doing some
// // kind of cache or pool management so that it will call SubAllocator::Alloc and
// // Free relatively infrequently, compared to the number of times its own
// // AllocateRaw and Free methods are called.
// class SubAllocator {
//     public:
//         typedef std::function<void(void*, int index, size_t)> Visitor;

//         SubAllocator(const std::vector<Visitor>& alloc_visitors,
//                      const std::vector<Visitor>& free_visitors);
        
//         virtual ~SubAllocator() {}

//         virtual void* Alloc(size_t alignment, size_t num_bytes,
//                             size_t* bytes_received) = 0;
//         virtual void Free(void* ptr, size_t num_bytes) = 0;

//         virtual bool SupportCoalescing() const = 0;

//     protected:
//         void VisitAlloc(void* ptr, int index, size_t num_bytes);
//         void VisitFree(void* ptr, int index, size_t num_bytes);

//         const std::vector<Visitor> alloc_visitors_;
//         const std::vector<Visitor> free_visitors_;
// };
}
#endif