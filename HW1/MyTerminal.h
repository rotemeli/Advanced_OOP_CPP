#ifndef EX01_ADVCPP_MYTERMINAL_H
#define EX01_ADVCPP_MYTERMINAL_H

#include <iostream>
#include <sstream>

#include "MyFile.h"
#include "MyFolder.h"

class MyTerminal {
private:
    /*
     * Help function
     */
    MyFile* helper(const std::string& fName, MyFolder* folder);

public:
    // constructor
    MyTerminal() = default;

    /*
     *Runs the program
     */
    void init();
};


#endif //EX01_ADVCPP_MYTERMINAL_H
