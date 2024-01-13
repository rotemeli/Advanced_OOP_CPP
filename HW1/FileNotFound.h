#ifndef EX01_ADVCPP_FILENOTFOUND_H
#define EX01_ADVCPP_FILENOTFOUND_H

#include <iostream>

class FileNotFound : public std::runtime_error {
public:
    explicit FileNotFound(const std::string &str) : std::runtime_error(str) {};
};


#endif //EX01_ADVCPP_FILENOTFOUND_H
