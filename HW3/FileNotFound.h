#ifndef EX02_ADVCPP_FILENOTFOUND_H
#define EX02_ADVCPP_FILENOTFOUND_H


#include <iostream>

class FileNotFound : public std::invalid_argument {
public:
    explicit FileNotFound(const std::string &str) : std::invalid_argument(str) {};
};


#endif //EX02_ADVCPP_FILENOTFOUND_H
