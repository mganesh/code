/*
 * =====================================================================================
 *
 *       Filename:  test.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/03/12 19:51:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ganesh Muniyandi (gm), ganesh.muniyandi@gmail.com
 *        Company:  Open Source
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <stdio.h>
    
static const int count = 3000000;
static const char * const string = "This is a string.";
    
void show_time(void (*f)(), char const *capti) { 
    clock_t start = clock();
    f();
    clock_t ticks = clock()-start;
    std::cerr << std::setw(30) << capti 
              << ": " 
              << (double)ticks/CLOCKS_PER_SEC << "\n";
}
    
    void use_printf() {
                for (int i=0; i<count; i++)
                                printf("%s\n", string);
                    }
    
    void use_puts() {
                for (int i=0; i<count; i++) 
                                puts(string);        
                    }
    
    void use_cout() { 
                for (int i=0; i<count; i++)
                                std::cout << string << "\n";
                    }
    
    void use_cout_unsync() { 
                std::cout.sync_with_stdio(false);
                        for (int i=0; i<count; i++)
                                        std::cout << string << "\n";
                                std::cout.sync_with_stdio(true);
                                    }
    
    void use_stringstream() { 
                std::stringstream temp;
                        for (int i=0; i<count; i++)
                                        temp << string << "\n";
                                std::cout << temp.str();
                                    }
    
    void use_endl() { 
                for (int i=0; i<count; i++)
                                std::cout << string << std::endl;
                    }
    
    void use_fill_n() { 
                std::fill_n(std::ostream_iterator<char const*>(std::cout, "\n"), count, string);
    }
    
    int main() { 
        show_time(use_printf, "Time using printf");
        show_time(use_puts, "Time using puts");
        show_time(use_cout, "Time using cout (synced)");
        show_time(use_cout_unsync, "Time using cout (un-synced)");
        show_time(use_stringstream, "Time using stringstream");
        show_time(use_endl, "Time using endl");
        show_time(use_fill_n, "Time using fill_n");
        return 0;
    }

