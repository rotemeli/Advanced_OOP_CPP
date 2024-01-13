#ifndef EX03_ADVCPP_CASTLE_H
#define EX03_ADVCPP_CASTLE_H


#include "Structure.h"

class Castle : public Structure {
private:
    int crop_boxes;     // Number of crop boxes in the castle

public:
    Castle() = delete;

    Castle(std::string name, double x, double y, int boxes) : Structure(std::move(name), x, y), crop_boxes(boxes) {}

    ~Castle() override = default;

    // Method for depositing additional crop boxes into the castle's stock
    void deposit(int boxes);

    // Returns the location point of the castle
    const shared_ptr<Point> &get_location() const override;

    // Method for updating the state of the castle
    void update() override;

    // Method for broadcasting the current state of the castle
    void broadcast_current_state() override;
};


#endif //EX03_ADVCPP_CASTLE_H
