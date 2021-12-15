#include "bfc_allocator.h"
#include "allocator.h"
#include <string>

namespace tfcore{

    BFCAllocator::BFCAllocator(SubAllocator* sub_allocator, size_t total_memory,
                           bool allow_growth, const std::string& name,
                           bool garbage_collection)
    : garbage_collection_(garbage_collection),
      coalesce_regions_(sub_allocator->SupportsCoalescing()),
      sub_allocator_(sub_allocator),
      name_(name),
      free_chunks_list_(kInvalidChunkHandle),
      next_allocation_id_(1){}
    
    BFCAllocator::Chunk* BFCAllocator::ChunkFromHandle(ChunkHandle h) {
      return &(chunks_[h]);
    }
}