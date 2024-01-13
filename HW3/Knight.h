#ifndef EX03_ADVCPP_KNIGHT_H
#define EX03_ADVCPP_KNIGHT_H


#include <set>
#include <memory>
#include <utility>
#include "Agent.h"
#include "Model.h"

class Knight : public Agent {
private:
    std::string _start_location;                    // Starting location of the knight
    std::shared_ptr<Point> location_point;          // Current location of the knight
    std::string _destination;                       // Destination location of the knight
    std::shared_ptr<Point> destination_point;       // Destination point for the knight
    std::set<std::string> visited_sites;            // Set of visited sites by the knight

    double _speed;                                  // Current speed of the knight
    double direction;                               // Current direction of the knight

    std::string get_next_site();

public:
    Knight() = delete;
    Knight(std::string name, std::string start_location);
    ~Knight() override = default;

    // Returns the location point of the knight
    const shared_ptr<Point> &get_location() const override;

    // Method for updating the state of the knight
    void update() override;

    // Method for broadcasting the current state of the knight
    void broadcast_current_state() override;

    // Method to set the course of the knight with a given angle
    void course(double angle) override;

    // Method to set the position of the knight with given coordinates
    void position(double x, double y) override;

    // Method to set the destination of the knight
    void destination(std::string dest);

    // Course method for the thug (empty implementation)
    void course(double angle, double speed) override {}

    // Position method for the thug (empty implementation)
    void position(double x, double y, double speed) override {}
};


#endif //EX03_ADVCPP_KNIGHT_H
