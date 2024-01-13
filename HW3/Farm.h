#ifndef EX03_ADVCPP_FARM_H
#define EX03_ADVCPP_FARM_H


#include "Structure.h"

class Farm : public Structure {
private:
    int crop_boxes;     // Number of crop boxes in the farm
    int production;     // Production value of the farm

public:
    Farm() = delete;

    Farm(std::string name, double x, double y, int boxes, int prod) : Structure(std::move(name), x, y),
                                                                      crop_boxes(boxes), production(prod) {}

    ~Farm() override = default;

    // Returns the location point of the farm
    const shared_ptr<Point> &get_location() const override;

    // Method for broadcasting the current state of the farm
    void broadcast_current_state() override;

    // Method for updating the state of the farm
    void update() override;

    // Method for withdrawing crop boxes from the farm's stock
    void withdraw(int boxes);

    // Getter method for retrieving the number of crop boxes in the farm
    int getCropBoxes() const;
};


#endif //EX03_ADVCPP_FARM_H
