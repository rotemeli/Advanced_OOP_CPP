#include "Castle.h"

void Castle::deposit(int boxes) {
    crop_boxes += boxes;
}

const shared_ptr<Point> &Castle::get_location() const {
    return Structure::get_location();
}

void Castle::update() {}

void Castle::broadcast_current_state() {
    std::cout << "Castle " << getName() << " at position ";
    get_location()->print();
    std::cout << ", Inventory: " << crop_boxes << std::endl;
}
