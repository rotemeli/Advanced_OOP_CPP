#include <iostream>
#include "MyTerminal.h"


using namespace std;


int main() {
    auto* terminal = new MyTerminal();
    terminal->init();

    delete terminal;

    return 0;
}
