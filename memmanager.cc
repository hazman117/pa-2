#include "memmanager.h"

MemManager::MemManager(uint32_t m) {
    // makes an insertion into the 'free list'
    // this is the first memory block
    free_list.push_back(0,m);
}

MemManager::~MemManager() {
    // no need to explicitly destroy the lists because
    // their constructors will be automatically called
}

void MemManager::coalesce() {
  /*
	// if you implement this function you earn bonus points
	int pos, amount;
	int counter = 0;
	MemBlock *holder;

	amount = free_list.get_amt();
	while (counter < amount)
	{
		pos = free_list.get_add(counter);
		holder = free_list.find_by_address(pos);

		//Checking if we found a match
		if (holder->get_addr() == pos)
		{

			free_list.push_back(pos, holder->get_size());
		}
		else
		{
			counter = counter + 1;
		}

	}
	*/
}

void MemManager::display() {
    free_list.display();
    used_list.display();
}

bool MemManager::alloc_first_fit(uint32_t b, uint32_t &address) {
    // this function implements allocation using the first fit strategy
    // first we find the fist block that can store b bytes
    MemBlock *first_fit = free_list.find_first_by_size(b);
    if (first_fit) {
        // check if this is an exact fit or not
        if (first_fit->get_size() == b) {
            // exact fit: move memory block from the free list to the used list
            // calculate address for the new node 
            address = first_fit->get_addr();
            // insert new memory block into the used list
            used_list.push_back(address, first_fit->get_size());
            // remove memory block from the free list
            free_list.remove(first_fit);
        } else {
            // not an exact fit: decrease the amount of available bytes
            first_fit->shrink_by(b);
            // calculate address for the new node 
            address = first_fit->get_addr() + first_fit->get_size();
            // insert a new memory block into the used list
            used_list.push_back(address, b);
        }
        // return that allocation was OK
        return true;
    } else {
        // not enough memory in the free list
        return false;
    }
}


bool MemManager::alloc_best_fit(uint32_t b, uint32_t &address) {
	// this function implements allocation using the first fit strategy
	// first we find the fist block that can store b bytes
	MemBlock *best_fit = free_list.find_best_by_size(b);
	if (best_fit) {
		// check if this is an exact fit or not
		if (best_fit->get_size() == b) {
			// exact fit: move memory block from the free list to the used list
			// calculate address for the new node 
			address = best_fit->get_addr();
			// insert new memory block into the used list
			used_list.push_back(address, best_fit->get_size());
			// remove memory block from the free list
			free_list.remove(best_fit);
		}
		else {
			// not an exact fit: decrease the amount of available bytes
			best_fit->shrink_by(b);
			// calculate address for the new node 
			address = best_fit->get_addr() + best_fit->get_size();
			// insert a new memory block into the used list
			used_list.push_back(address, b);
		}
		// return that allocation was OK
		return true;
	}
	else {
		// not enough memory in the free list
		return false;
	}
}

bool MemManager::alloc_memory(uint32_t b, uint32_t &address, const std::string algo) {
    // this function only determines which algorithm to use for allocating a new blocks
    // then calls the proper function to handle the request
    if ( ! algo.compare("aff") ) {
        return alloc_first_fit(b, address);
    }
    if ( ! algo.compare("abf") ) {
        return alloc_best_fit(b, address);
    }
    // any other type different from 'aff' and 'abf' will not be processed
    return false;
}

bool MemManager::free_memory(uint32_t address) {
    // first we find the block with the same address
    MemBlock *block = used_list.find_by_address(address);
    if (block) { // if block has been found
        // insert a new node into the free list
        // this insertion is in ascending order of address
        free_list.insert(block->get_addr(), block->get_size());
        // remove node from used list
        used_list.remove(block);
        // return that free operation is ok
        return true;
    } else {
        // this address does not exist in the used list
        return false;
    }
}