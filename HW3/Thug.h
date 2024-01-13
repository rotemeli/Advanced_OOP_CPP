#ifndef EX03_ADVCPP_THUG_H
#define EX03_ADVCPP_THUG_H


#include "Agent.h"
#include "Model.h"

class Thug : public Agent {
private:
    std::shared_ptr<Point> _location;       // Current location of the thug
    double _speed;                          // Current speed of the thug
    double direction;                       // Current direction of the thug
    std::shared_ptr<Point> destination;     // Destination point for the thug

    // Helper function to check if there is a knight within a 2.5-kilometer radius
    bool close_knight_checker();

public:
    Thug() = delete;

    Thug(std::string name, double x, double y);

    ~Thug() override = default;

    // Returns the location point of the thug
    const shared_ptr<Point> &get_location() const override;

    // Method for the thug to attack a peasant with the given name
    bool attack(const std::string &peasant_name);

    // Method for updating the state of the thug
    void update() override;

    // Method for broadcasting the current state of the thug
    void broadcast_current_state() override;

    // Method to set the course and speed of the thug with a given angle and speed
    void course(double angle, double speed) override;

    // // Method to set the position and speed of the thug with given coordinates and speed
    void position(double x, double y, double speed) override;

    // Course method for the knight (empty implementation)
    void course(double angle) override {}

    // Position method for the knight (empty implementation)
    void position(double x, double y) override {}

};


#endif //EX03_ADVCPP_THUG_H
