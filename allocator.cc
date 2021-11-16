#include "allocator.h"

#include <atomic>

#include "stringprintf.h"

namespace tfcore{

    std::string AllocatorStats::DebugString() const {
        return strings::Printf(
        "InUse:            %20lld\n"
        "MaxInUse:         %20lld\n"
        "NumAllocs:        %20lld\n"
        "MaxAllocSize:     %20lld\n"
        "Reserved:         %20lld\n"
        "PeakReserved:     %20lld\n"
        "LargestFreeBlock: %20lld\n",
        static_cast<long long>(this->bytes_in_use),
        static_cast<long long>(this->peak_bytes_in_use),
        static_cast<long long>(this->num_allocs),
        static_cast<long long>(this->largest_alloc_size),
        static_cast<long long>(this->bytes_reserved),
        static_cast<long long>(this->peak_bytes_reserved),
        static_cast<long long>(this->largest_free_block_bytes));
    }

    // Not clear
    constexpr size_t Allocator::kAllocatorAlignment;

    Allocator::~Allocator() {}

    static bool cpu_allocator_collect_full_stats = false;

    void EnableCPUAllocatorFullStats() { cpu_allocator_collect_full_stats = true; }
    bool CPUAllocatorFullStatsEnabled() { return cpu_allocator_collect_full_stats; }

    std::string AllocatorAttributes::DebugString() const {
        std::string host = std::to_string(on_host());
        std::string s = "AllocatorAttributes(on_host=" + host;
        return s;
}
}