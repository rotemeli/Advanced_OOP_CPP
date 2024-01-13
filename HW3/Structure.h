#ifndef EX03_ADVCPP_STRUCTURE_H
#define EX03_ADVCPP_STRUCTURE_H


#include "Sim_object.h"

class Structure : public Sim_object {
private:
    std::shared_ptr<Point> _location;

public:
    Structure() = delete;

    Structure(std::string name, double x, double y) : Sim_object(std::move(name)) {
        _location = std::make_shared<Point>(x, y);
    }

    ~Structure() override = default;

    // Pure virtual methods for the derived classes
    void update() override = 0;

    void broadcast_current_state() override = 0;

    // Getter
    const shared_ptr<Point> &get_location() const override {
        return _location;
    }
};


#endif //EX03_ADVCPP_STRUCTURE_H
