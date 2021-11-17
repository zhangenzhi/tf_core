#ifndef TF_CORE_ALLOCATOR_REGISTRY
#define TF_CORE_ALLOCATOR_REGISTRY

#include <string>
#include <vector>

// #include "mutex.h"
#include "macros.h"
#include "allocator.h"

namespace tfcore{
class AllocatorFactory{
    public:
        virtual ~AllocatorFactory(){}
        virtual bool NumaEnabled() {return false;}

        virtual Allocator* CreateAllocator() = 0;
        virtual SubAllocator* CreateSubAllocator(int numa_node) = 0;
};

class ProcessStateInterface {
    public:
        virtual ~ProcessStateInterface() {}
        virtual Allocator* GetCPUAllocator(int numa_node) = 0;
};

class AllocatorFactoryRegistry {
    public:
        AllocatorFactoryRegistry() {}
        ~AllocatorFactoryRegistry() {}

        void Register(const char* source_file, int source_line, const std::string& name,
            int priority, AllocatorFactory* factory);
        
        Allocator* GetAllocator();
        SubAllocator* GetSubAllocator(int numa_node);

        // Returns the singleton value.
        static AllocatorFactoryRegistry* singleton();

        ProcessStateInterface* process_state() const { return process_state_; }

    protected:
        friend class ProcessState;
        ProcessStateInterface* process_state_ = nullptr;
    
    private:
        bool mu_=false;
        bool first_alloc_made_ = false;
        struct FactoryEntry {
            const char* source_file;
            int source_line;
            std::string name;
            int priority;
            std::unique_ptr<AllocatorFactory> factory;
            std::unique_ptr<Allocator> allocator;
            // Index 0 corresponds to kNUMANoAffinity, other indices are (numa_node +
            // 1).
            std::vector<std::unique_ptr<SubAllocator>> sub_allocators;
        };
        std::vector<FactoryEntry> factories_ TF_GUARDED_BY(mu_);

        // Returns any FactoryEntry registered under 'name' and 'priority',
        // or 'nullptr' if none found.
        const FactoryEntry* FindEntry(const std::string& name, int priority) const
            TF_EXCLUSIVE_LOCKS_REQUIRED(mu_);

        DISALLOW_COPY_AND_ASSIGN(AllocatorFactoryRegistry);
};

class AllocatorFactoryRegistration {
 public:
  AllocatorFactoryRegistration(const char* file, int line, const std::string& name,
                               int priority, AllocatorFactory* factory) {
    AllocatorFactoryRegistry::singleton()->Register(file, line, name, priority,
                                                    factory);
  }
};

#define REGISTER_MEM_ALLOCATOR(name, priority, factory)                     \
  REGISTER_MEM_ALLOCATOR_UNIQ_HELPER(__COUNTER__, __FILE__, __LINE__, name, \
                                     priority, factory)

#define REGISTER_MEM_ALLOCATOR_UNIQ_HELPER(ctr, file, line, name, priority, \
                                           factory)                         \
  REGISTER_MEM_ALLOCATOR_UNIQ(ctr, file, line, name, priority, factory)

#define REGISTER_MEM_ALLOCATOR_UNIQ(ctr, file, line, name, priority, factory) \
  static AllocatorFactoryRegistration allocator_factory_reg_##ctr(            \
      file, line, name, priority, new factory)

}


#endif