#include "Program_Management.h"

#include <memory>
#include <sstream>

Program_Management::Program_Management() {
    time_graph = std::make_shared<DirectedGraph>();
    container_graph = std::make_shared<DirectedGraph>();
    output_file = "";
}

bool Program_Management::check_file(const std::string &file) {
    std::ifstream tmp(file);
    if(!tmp) {
        std::cerr << "ERROR opening/reading the specified file.\n";
        return false;
    }
    std::string line1;
    std::string port_name1, arrival_time1, container_quantity1, departure_time1;
    std::string port_name2, arrival_time2, container_quantity2, departure_time2;

    std::vector<std::string> vec;
    while (std::getline(tmp, line1)) {
        vec.push_back(line1);
    }

    int line = 0;
    double minutes;
    for (int i = 0; i < (int) vec.size() - 1; i++) {
        line++;
        helper(vec[i], port_name1, arrival_time1, container_quantity1, departure_time1);
        helper(vec[i+1], port_name2, arrival_time2, container_quantity2, departure_time2);
        if (i == 0) {
            minutes = calcDiffInMinutes(arrival_time1, arrival_time2);
        } else {
            minutes = calcDiffInMinutes(departure_time1, arrival_time2);
        }
        if(minutes < 0 || port_name1.length() > 16 || port_name2.length() > 16) {
            std::cerr << "Invalid input at line " << line << "." << std::endl;
            return false;
        }
    }
    tmp.close();
    return true;
}

void Program_Management::helper(const std::string &str, std::string &s1, std::string &s2, std::string &s3, std::string &s4) {
    std::stringstream ss;
    ss.str(str);
    std::string tmp;
    int count = 1;
    while (std::getline(ss, tmp, ',')) {
        switch (count) {
            case 1:
                s1 = tmp;
                count++;
                break;
            case 2:
                s2 = tmp;
                count++;
                break;
            case 3:
                s3 = tmp;
                count++;
                break;
            case 4:
                s4 = tmp;
                count++;
                break;
            default:
                count = 1;
                break;
        }
    }
}

void Program_Management::read_file(const std::string &infile) {
    std::ifstream file(infile, std::ios::in);
    if (!file) {
        std::string msg = "Invalid input in file " + infile + " at line " + std::to_string(__LINE__) + ".\n";
        throw FileNotFound(msg);
    }
    file_names.push_back(infile);

    std::string line1;
    std::string port_name1, arrival_time1, container_quantity1, departure_time1;
    std::string port_name2, arrival_time2, container_quantity2, departure_time2;

    std::vector<std::string> vec;
    while (std::getline(file, line1)) {
        vec.push_back(line1);
    }
    file.close();
    
    double minutes;
    for (int i = 0; i < (int) vec.size() - 1; i++) {
        helper(vec[i], port_name1, arrival_time1, container_quantity1, departure_time1);
        helper(vec[i+1], port_name2, arrival_time2, container_quantity2, departure_time2);
        container_graph->putEdge(port_name1, port_name2, std::stod(container_quantity2));
        if (i == 0) {
            minutes = calcDiffInMinutes(arrival_time1, arrival_time2);
        } else {
            minutes = calcDiffInMinutes(departure_time1, arrival_time2);
        }
        if(minutes < 0) {
            std::cerr << "Invalid input at line " << __LINE__ << "." << std::endl;
            return;
        }
        if (time_graph->containEdge(port_name1, port_name2)) {
            double avg_min = (minutes + time_graph->getWeight(port_name1, port_name2)) / 2;
            time_graph->putEdge(port_name1, port_name2, avg_min);
        } else {
            time_graph->putEdge(port_name1, port_name2, minutes);
        }
    }
}

void Program_Management::write(const std::string &outfile) {
    output_file = outfile;
}

void Program_Management::init() {
    std::stringstream ss;
    std::string op, fName, fullOp;

    while (true) {
        std::getline(std::cin, op);
        ss.clear();
        ss.str(op);
        fullOp = op;
        ss >> op;
        if (op == "load") {
            ss >> fName;
            if(!check_file(fName)) {
                continue;
            }
            read_file(fName);
            std::cout << "Update was successful." << std::endl;
        } else if (fullOp.find(",outbound") != std::string::npos) {
            std::string vertex = fullOp;
            vertex.erase(vertex.end() - 9, vertex.end());
            if(!time_graph->containVertex(vertex)) {
                std::cout << vertex << " does not exist in the database." << std::endl;
                continue;
            }
            std::vector<std::string> v = time_graph->get_neighbors(vertex);
            if (v.empty()) {
                std::cout << vertex << ": no outbound ports" << std::endl;
            } else {
                for (const std::string &s: v) {
                    std::cout << s << ',' << time_graph->getWeight(vertex, s) << std::endl;
                }
            }
        } else if (fullOp.find(",inbound") != std::string::npos) {
            std::string vertex = fullOp;
            vertex.erase(vertex.end() - 8, vertex.end());
            if(!time_graph->containVertex(vertex)) {
                std::cout << vertex << " does not exist in the database." << std::endl;
                continue;
            }
            std::vector<std::string> v = time_graph->get_connected(vertex);
            if (v.empty()) {
                std::cout << vertex << ": no inbound ports" << std::endl;
            } else {
                for (const std::string &s: v) {
                    std::cout << s << ',' << time_graph->getWeight(s, vertex) << std::endl;
                }
            }
        } else if (fullOp.find(",balance,") != std::string::npos) {
            std::string vertex;
            int i;
            for (i = 0; i < (int) fullOp.length(); i++) {
                if (fullOp[i] == ',') {
                    break;
                } else {
                    vertex.push_back(fullOp[i]);
                }
            }
            std::string date = fullOp;
            date.erase(date.begin(), date.begin() + i + 9);
            std::cout << check_balance(vertex, date) << std::endl;
        } else if (op == "print") {
            std::ofstream tmp(output_file, std::ios::out);
            tmp << "Format:\n<source> : <target>(edge weight)\n" << std::endl;
            tmp << "Container graph:\n\n";
            tmp.close();
            container_graph->print_graph(output_file);
            tmp.open(output_file, std::ios::out | std::ios::app);
            tmp << "\nTime graph:\n\n";
            tmp.close();
            time_graph->print_graph(output_file);
        } else if (op == "exit") {
            exit(0);
        } else {
            std::cout << "USAGE: \t‘load’ <file> *or*\n"
                         "\t\t<node>,'inbound' *or*\n"
                         "\t\t<node>,’outbound’ *or*\n"
                         "\t\t<node>,’balance’,dd/mm HH:mm *or*\n"
                         "\t\t‘print’ *or*\n"
                         "\t\t‘exit’ *to terminate*" << std::endl;
        }
    }
}

std::chrono::system_clock::time_point Program_Management::convertStrToTime(const std::string &dateTimeStr) {
    std::tm tm = {};
    std::istringstream iss(dateTimeStr);
    iss >> std::get_time(&tm, "%d/%m %H:%M");
    tm.tm_year = 2023 - 1900;
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return timePoint;
}

int Program_Management::calcDiffInMinutes(const std::string &startTimeStr, const std::string &endTimeStr) {
    std::chrono::system_clock::time_point startTime = convertStrToTime(startTimeStr);
    std::chrono::system_clock::time_point endTime = convertStrToTime(endTimeStr);

    std::chrono::duration<double> duration = endTime - startTime;
    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    return (int) minutes.count();
}

int Program_Management::check_balance(const std::string &port_name, const std::string &date) {
    std::string line;
    std::string port_name1, arrival_time1, container_quantity1, departure_time1;
    std::vector<std::string> vec;
    std::ifstream tmp;
    int balance;
    for(const std::string& fName : file_names) {
        vec.clear();
        tmp.clear();
        tmp.open(fName, std::ios::in);
        while (std::getline(tmp, line)) {
            vec.push_back(line);
        }
        tmp.close();

        balance = 0;
        bool flag = false;

        for(int i = 0; i < (int) vec.size(); i++) {
            helper(vec[i], port_name1, arrival_time1, container_quantity1, departure_time1);
            if(i == 0 && port_name1 == port_name) {
                if(calcDiffInMinutes(arrival_time1, date) < 0) {
                    return balance;
                } else {
                    flag = true;
                }
            }
            else if(flag) {
                balance -= stoi(container_quantity1);
            }
            else if(port_name1 == port_name) {
                if(calcDiffInMinutes(arrival_time1, date) >= 0 && calcDiffInMinutes(departure_time1, date) <= 0) {
                    balance = std::stoi(container_quantity1);
                    return balance;
                }
            }
            if(i == (int) vec.size()-1 && port_name1 == port_name) {
                if(calcDiffInMinutes(departure_time1, date) > 0) {
                    return std::stoi(container_quantity1);
                }
            }
        }

    }
    return balance;
}
