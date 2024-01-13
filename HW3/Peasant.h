#ifndef EX03_ADVCPP_PEASANT_H
#define EX03_ADVCPP_PEASANT_H


#include "Agent.h"
#include "Model.h"

class Peasant : public Agent {
private:
    std::shared_ptr<Point> _location;           // Current location of the peasant
    int _speed;                                 // Current speed of the peasant
    int num_boxes;                              // Number of boxes carried by the peasant
    std::string _source;                        // Source location of the peasant's work
    std::string _destination;                   // Destination location of the peasant's work
    std::shared_ptr<Point> destination_point;   // Destination point for the peasant's work
    std::string curr_course;                    // Current course of the peasant


    // Helper method to change the destination of the peasant's work
    void change_destination(const std::string &dest);

public:
    Peasant() = delete;

    Peasant(std::string name, double x, double y);

    ~Peasant() override = default;

    // Returns the location point of the peasant
    const shared_ptr<Point> &get_location() const override;

    // Method for updating the state of the peasant
    void update() override;

    // Method for broadcasting the current state of the peasant
    void broadcast_current_state() override;

    // Method for starting the peasant's work with the given source and destination locations
    void start_working(std::string source, std::string dest);

    // Method to clear the boxes carried by the peasant
    void clear_boxes();

    // Empty implementation methods that peasant does not support
    void course(double angle) override {}

    void course(double angle, double speed) override {}

    void position(double x, double y) override {}

    void position(double x, double y, double speed) override {}
};


#endif //EX03_ADVCPP_PEASANT_H
