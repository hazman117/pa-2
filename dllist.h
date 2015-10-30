#ifndef __Dllist_h__
#define __Dllist_h__

#include <cstdint>

// this class represents each memory block ... it can be used for representing a
// node in a doubly linked list.
// You wiil have to give 'friend' access to the class that implements the doubly
// linked list, so the pointers can be accessed (adjusted) from outside the class.
class MemBlock {


    private:
        uint32_t address;
        uint32_t size;

        MemBlock *nxt;
        MemBlock *prv;

    public:
        MemBlock(uint32_t a, uint32_t s);
        ~MemBlock();

        void shrink_by(uint32_t s);
        uint32_t get_addr();
        uint32_t get_size();

    friend class DLList;

};

class DLList {

    private:
        MemBlock *head;
        MemBlock *tail;

    public:
        DLList();
        ~DLList();

        void push_back(uint32_t a, uint32_t s);
        void insert(uint32_t a, uint32_t s);
        void display();
        MemBlock *find_first_by_size(uint32_t b);
		MemBlock *find_best_by_size(uint32_t b);
        void remove(MemBlock *p);
        MemBlock *find_by_address(uint32_t a);
		int DLList::get_amt();
		int DLList::get_add(int b);
};

#endif