#include "Controller.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cerr << "Invalid arguments <castles_file_name> <farms_file_name>." << std::endl;
        exit(-1);
    }
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);

    Controller controller;
    controller.run(argc, argv);

    return 0;
}
