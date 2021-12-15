#ifndef TF_CORE_BFC_ALLOCATOR_H_
#define TF_CORE_BFC_ALLOCATOR_H_

#include <array>
#include <deque>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <thread>
#include <set>

#include "allocator.h"
#include "macros.h"
#include "types.h"

namespace tfcore{
    class BFCAllocator : public Allocator{
        public:
            BFCAllocator(SubAllocator* sub_allocator, size_t total_memory,
                bool allow_growth, const std::string& name,
                bool garbage_collection = false);
            ~BFCAllocator() override;

            std::string Name() override { return name_; }

            void* AllocateRaw(size_t alignment, size_t num_bytes) override {
                return AllocateRaw(alignment, num_bytes, AllocationAttributes());
            }

            void* AllocateRaw(size_t alignment, size_t num_bytes,
                                const AllocationAttributes& allocation_attr) override;

        private:
            struct Bin;

            void* AllocateRawInternal(size_t alignment, size_t num_bytes,
                                        bool dump_log_on_failure,
                                        uint64 freed_before_count);

            void* AllocateRawInternalWithRetry(
                size_t alignment, size_t num_bytes,
                const AllocationAttributes& allocation_attr);

            void DeallocateRawInternal(void* ptr);

            bool MergeTimestampedChunks(size_t required_bytes)
                TF_EXCLUSIVE_LOCKS_REQUIRED(lock_);

            int64_t LargestFreeChunk() TF_EXCLUSIVE_LOCKS_REQUIRED(lock_);

            void AddTraceMe(std::string traceme_name, const void* ptr)
                TF_EXCLUSIVE_LOCKS_REQUIRED(lock_);

            // Overloaded AddTraceMe function with chunk information.
            void AddTraceMe(std::string traceme_name, const void* chunk_ptr,
                  int64_t req_bytes, int64_t alloc_bytes)
                TF_EXCLUSIVE_LOCKS_REQUIRED(lock_);

            typedef size_t ChunkHandle;
            static constexpr ChunkHandle kInvalidChunkHandle = SIZE_MAX;

            typedef int BinNum;
            static constexpr int kInvalidBinNum = -1;
            // The following means that the largest bin'd chunk size is 256 << 21 = 512MB.
            static constexpr int kNumBins = 21;

            struct Chunk {
                size_t size = 0;
                size_t requested_size = 0;
                int64_t allocation_id = -1;
                void* ptr = nullptr;

                ChunkHandle prev = kInvalidChunkHandle;
                ChunkHandle next = kInvalidChunkHandle;
                BinNum bin_num = kInvalidBinNum;

                uint64 freed_at_count = 0;
                bool in_use() const { return allocation_id != -1; }
            };

            struct Bin {
                size_t bin_size = 0;
                class ChunkComparator {
                    public:
                        explicit ChunkComparator(BFCAllocator* allocator) : allocator_(allocator) {}
                        // Sort first by size and then use pointer address as a tie breaker.
                        bool operator()(const ChunkHandle ha,
                                        const ChunkHandle hb) const {
                            const Chunk* a = allocator_->ChunkFromHandle(ha);
                            const Chunk* b = allocator_->ChunkFromHandle(hb);
                            if (a->size != b->size) {
                            return a->size < b->size;
                            }
                            return a->ptr < b->ptr;
                        }
                    private:
                        BFCAllocator* allocator_;  // The parent allocator
                };
                typedef std::set<ChunkHandle, ChunkComparator> FreeChunkSet;
                // List of free chunks within the bin, sorted by chunk size.
                // Chunk * not owned.
                FreeChunkSet free_chunks;
                Bin(BFCAllocator* allocator, size_t bs)
                    : bin_size(bs), free_chunks(ChunkComparator(allocator)) {}
            };
            
            static constexpr size_t kMinAllocationBits = 8;
            static constexpr size_t kMinAllocationSize = 1 << kMinAllocationBits;

            class AllocationRegion {
                public:
                    AllocationRegion(void* ptr, size_t memory_size)
                        : ptr_(ptr), 
                          memory_size_(memory_size),
                          end_ptr_(static_cast<void*>(static_cast<char*>(ptr_) + memory_size_)){
                        const size_t n_handles =
                            (memory_size + kAllocatorAlignment -1) / kMinAllocationSize;
                    }

                private:
                    void* ptr_ = nullptr;
                    size_t memory_size_ = 0;
                    void* end_ptr_ = nullptr;
                    std::vector<ChunkHandle> handles_;
            };

            class RegionManager {
                public:
                    RegionManager(){}
                    ~RegionManager(){}

                private:
                    std::vector<AllocationRegion> regions_;
            };

            static size_t RoundedBytes(size_t bytes);

            bool Extend(size_t alignment, size_t rounded_bytes);
            bool DeallocateFreeRegions();

            void* FindChunkPtr(BinNum bin_num, size_t rounded_size, size_t num_bytes,
                               uint64 free_before);
            void* SplitChunk(ChunkHandle h, size_t num_bytes);

            Chunk* ChunkFromHandle(ChunkHandle h);
            std::vector<Chunk> chunks_;
            const Chunk* ChunkFromHandle(ChunkHandle h) const
                TF_EXCLUSIVE_LOCKS_REQUIRED(lock_);

            std::string name_;
            bool garbage_collection_;
            size_t next_allocation_id_;

            const bool coalesce_regions_;
            std::unique_ptr<SubAllocator> sub_allocator_;
             ChunkHandle free_chunks_list_ TF_GUARDED_BY(lock_);
    };
}

#endif