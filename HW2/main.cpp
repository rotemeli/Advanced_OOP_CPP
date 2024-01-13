#include <iostream>
#include <string>

#include "Program_Management.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Missing files" << endl;
        exit(-1);
    }
    int len;
    string s(argv[argc - 2]);
    string output = "output.dat";
    if (s != "-o") {
        len = argc;
    } else {
        len = argc - 2;
        output = argv[argc - 1];
    }

    Program_Management program;

    for (int i = 2; i < len; i++) {
        program.read_file(argv[i]);
    }

    program.write(output);
    program.init();


    return 0;
}
