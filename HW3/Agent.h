#ifndef EX03_ADVCPP_AGENT_H
#define EX03_ADVCPP_AGENT_H


#include "Sim_object.h"
#include <cmath>

class Agent : public Sim_object {
private:
    int _health;
    std::string _state;

public:
    // Constructor
    Agent(std::string name, int health, std::string state) : Sim_object(std::move(name)), _health(health), _state(std::move(state)) {}

    ~Agent() override = default;

    // Pure virtual methods for the derived classes
    const shared_ptr<Point> &get_location() const override = 0;

    void update() override = 0;

    void broadcast_current_state() override = 0;

    virtual void course(double angle) = 0;

    virtual void course(double angle, double speed) = 0;

    virtual void position(double x, double y) = 0;

    virtual void position(double x, double y, double speed) = 0;

    // Getters
    int getHealth() const {
        return _health;
    }

    const std::string &getState() const {
        return _state;
    }

    // Setters
    void setHealth(int health) {
        _health = health;
    }

    void setState(const string &state) {
        _state = state;
    }

};


#endif //EX03_ADVCPP_AGENT_H
