#ifndef EX03_ADVCPP_SIM_OBJECT_H
#define EX03_ADVCPP_SIM_OBJECT_H


#include <memory>
#include <utility>
#include "Geometry.h"

class Sim_object {
private:
    std::string name;

public:
    explicit Sim_object(std::string n) : name(std::move(n)) {}

    virtual ~Sim_object() = default;


    // Pure virtual methods for the derived classes
    virtual const shared_ptr<Point> &get_location() const = 0;

    virtual void update() = 0;

    virtual void broadcast_current_state() = 0;

    // Getter
    const std::string &getName() const {
        return name;
    }
};


#endif //EX03_ADVCPP_SIM_OBJECT_H
