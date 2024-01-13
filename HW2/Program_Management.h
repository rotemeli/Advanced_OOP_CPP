#ifndef EX02_ADVCPP_PROGRAM_MANAGEMENT_H
#define EX02_ADVCPP_PROGRAM_MANAGEMENT_H

#include <chrono>
#include <iomanip>
#include "DirectedGraph.h"
#include "FileNotFound.h"

class Program_Management {
private:
    std::vector<std::string> file_names;
    std::shared_ptr<DirectedGraph> time_graph;
    std::shared_ptr<DirectedGraph> container_graph;
    std::string output_file;

    // Help functions
    void helper(const std::string &str, std::string &s1, std::string &s2, std::string &s3, std::string &s4);
    bool check_file(const std::string &file);

    // Time calculator
    std::chrono::system_clock::time_point convertStrToTime(const std::string &dateTimeStr);
    int calcDiffInMinutes(const std::string &startTimeStr, const std::string &endTimeStr);
    int check_balance(const std::string &port_name, const std::string &date);

public:
    Program_Management();

     // Read from a file
    void read_file(const std::string &infile);

    // Write into a file
    void write(const std::string &outfile);

    // Run the program
    void init();
};


#endif //EX02_ADVCPP_PROGRAM_MANAGEMENT_H
