//
// Brian Hazard
//
// Didn't finish converting in time to figure out coalesce. I did do some work there though
//
// This file contains the driver program.  You are not required to modify it
// but feel free to make changes.
//
// I expect you to understand exactly how this program works.  Go through the
// code step-by-step.
//
// Possible commands:
// aff <bytes> <var>  (allocate <bytes> bytes using first fit and assign to <var>)
// abf <bytes> <var>  (allocate <bytes> bytes using best fit and assign to <var>)
// f <var>  (free memory assigned to <var>)
// c  (coalesce memory blocks -- BONUS POINTS)
// d  (display the status of free and used memory blocks)
// q  (quit the program)
//
#include "memmanager.h"

#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

// function will split a string 'line' into a array of 'words'
// 'words' is an output argument (vector of strings)
void tokenizer(const std::string line, std::vector<std::string> *words) {
    std::string word;
    // convert the string 'line' into a stream
    std::istringstream iss(line);
    while (iss.good()) {
        // get next token
        iss >> word;
        // add token to the end of array
        words->push_back(word);
    }
}

// the main program is assuming that all input comes from stdin
// and contains no errors
int main() {
    // create a string 'line'
    std::string line;
    // create the memory manager with a single block of 1000 bytes
    MemManager manager(1000);
    // create a table to keep track of 'variable names' and their 'addresses'
    std::unordered_map<std::string, uint32_t> addr_table;

    // read and process all lines from stdin (standard input)
    while (1) {
        // get next line from stdin
        std::getline(std::cin, line);
        // tokenize line into words
        std::vector<std::string> words;
        tokenizer(line, &words);

        // break the loop (quit) when the command is 'q'
        if (! words[0].compare("q")) {
            break;
        }
        // process a request for coalescing
        else if (! words[0].compare("c")) {
            manager.coalesce();
        }
        // process a request for displaying the lists of free and used blocks
        else if (! words[0].compare("d")) {
            manager.display();
        }
        // process a request for allocating a memory block (aff or abf)
        else if (words.size() == 3 && (! words[0].compare("aff") || ! words[0].compare("abf"))) {
            // parse the requested number of bytes
            uint32_t n_bytes = std::stol(words[1], nullptr, 10);
            // check whether this variable already exists in the address table
            if (addr_table.find(words[2]) != addr_table.end()) {
                std::cout << "failed -- variable already allocated" << std::endl;
            } else {
                uint32_t address;
                // calls the allocation function and check the result
                if (manager.alloc_memory(n_bytes, address, words[0])) {
                    // success
                    // saves address in addr_table and prints message
                    addr_table[words[2]] = address;
                    std::cout << "ok @ " << address << std::endl;
                }
                else {
                    // fail
                    std::cout << "failed -- not enough memory" << std::endl;
                }
            }
        }
        // process a request for freeing a block of memory
        else if (words.size() == 2 && ! words[0].compare("f")) {
            // look for this variable in the address table
            if (addr_table.find(words[1]) != addr_table.end()) {
                // variable found -- call free_memory
                manager.free_memory(addr_table[words[1]]);
                // remove entry from table
                addr_table.erase(words[1]);
                std::cout << "ok" << std::endl;
            } else {
                // variable not found -- nothing to free
                std::cout << "failed -- variable doesn't exist" << std::endl;
            }
        }
        else {
            std::cout << "wrong command" << std::endl;
        }
    }

    return 0;
}