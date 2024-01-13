#ifndef EX01_ADVCPP_INVALIDINDEX_H
#define EX01_ADVCPP_INVALIDINDEX_H

#include <iostream>

class InvalidIndex : public std::invalid_argument {
public:
    explicit InvalidIndex(const std::string &str) : std::invalid_argument(str) {};
};


#endif //EX01_ADVCPP_INVALIDINDEX_H
