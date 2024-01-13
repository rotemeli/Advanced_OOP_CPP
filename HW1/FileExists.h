#ifndef EX01_ADVCPP_FILEEXISTS_H
#define EX01_ADVCPP_FILEEXISTS_H

#include <iostream>

class FileExists : public std::invalid_argument {
public:
    explicit FileExists(const std::string &str) : std::invalid_argument(str) {};
};


#endif //EX01_ADVCPP_FILEEXISTS_H
