#ifndef EX03_ADVCPP_CONTROLLER_H
#define EX03_ADVCPP_CONTROLLER_H


#include <fstream>
#include "Model.h"
#include "FileNotFound.h"

class Controller {
private:
    // Helper functions
    void helper(const std::string &str, std::string &s1, std::string &s2, std::string &s3, string &s4, string &s5);
    void read_file(const std::string &file_name);

public:
    Controller() = default;

    // Method to run the controller and start the simulation
    void run(int argc, char* argv[]);
};


#endif //EX03_ADVCPP_CONTROLLER_H
