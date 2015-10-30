#ifndef __memmanager_h__
#define __memmanager_h__

#include <string>

#include "dllist.h"

// This class implements the memory manager. The main function interacts
// with the manager through the public members of this class
class MemManager {

    private:
        //  HERE IS WHAT YOU NEED TO CHANGE
        // insted of using a singly linked lists you will declare two doubly linked
        // lists
        // you will create a separate class for its implementation including
        // methods to add, remove and traverse its nodes
        DLList free_list;
        DLList used_list;

    public:
        // constructor: requires an integer with the size of memory available
        MemManager(uint32_t m);
        // destructor
        ~MemManager();

        // coalesce free blocks of memory
        void coalesce();

        // display a list of free blocks
        void display();

        // allocates a memory block using the first fit (aff) or best fit (abf) strategy
        bool alloc_memory(uint32_t b, uint32_t &address, const std::string algo);
        bool alloc_first_fit(uint32_t b, uint32_t &address);
        bool alloc_best_fit(uint32_t b, uint32_t &address);

        // frees a memory block
        bool free_memory(uint32_t address);

};

#endif