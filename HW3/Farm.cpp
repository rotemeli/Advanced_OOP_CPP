#include "Farm.h"

const shared_ptr<Point> &Farm::get_location() const {
    return Structure::get_location();
}

void Farm::broadcast_current_state() {
    std::cout << "Farm " << getName() << " at position ";
    get_location()->print();
    std::cout << ", Inventory: " << crop_boxes << std::endl;
}

void Farm::update() {
    crop_boxes += production;
}

void Farm::withdraw(int boxes) {
    crop_boxes -= boxes;
}

int Farm::getCropBoxes() const {
    return crop_boxes;
}
