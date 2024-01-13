#include "Peasant.h"

Peasant::Peasant(std::string name, double x, double y) : Agent(std::move(name), 10, "Stopped") {
    _location = std::make_shared<Point>(x, y);
    _source = "";
    _destination = "";
    destination_point = std::make_shared<Point>();
    _speed = 5;
    num_boxes = 0;
    curr_course = "";
}

const shared_ptr<Point> &Peasant::get_location() const {
    return _location;
}

void Peasant::update() {
    if(getState() != "Stopped" && getState() != "Dead") {
        Point d(destination_point->x - _location->x, destination_point->y - _location->y);
        double distance = sqrt(d.x*d.x + d.y*d.y);
        double x_offset = (d.x / distance) / (10.00 / _speed);
        double y_offset = (d.y / distance) / (10.00 / _speed);
        _location->x += x_offset;
        _location->y += y_offset;
        for(const auto& s : Model::get_Instance().getStructList()) {
            if((int)_location->x == s->get_location()->x && (int)_location->y == s->get_location()->y) {
                if(curr_course == _source) {
                    change_destination(_destination);
                    std::shared_ptr<Structure> st = Model::get_Instance().get_struct(_source);
                    std::shared_ptr<Farm> f = std::dynamic_pointer_cast<Farm>(s);
                    if(f) {
                        if(f->getCropBoxes() <= 5) {
                            num_boxes = f->getCropBoxes();
                            f->withdraw(f->getCropBoxes());
                        } else {
                            num_boxes = 5;
                            f->withdraw(5);
                        }
                    }
                }
                else {
                    std::shared_ptr<Structure> st = Model::get_Instance().get_struct(_destination);
                    std::shared_ptr<Castle> c = std::dynamic_pointer_cast<Castle>(s);
                    c->deposit(num_boxes);
                    num_boxes = 0;
                    setState("Stopped");
                }
                break;
            }
        }
    }
}

void Peasant::broadcast_current_state() {
    std::cout << "Peasant " << getName() << " at ";
    _location->print();
    if(getState() == "Stopped") {
        std::cout << ", " << getState() << std::endl;
    } else {
        std::cout << ", " << "Heading to " << curr_course << ", speed 5.00 km/h" << std::endl;
    }
}

void Peasant::start_working(std::string source, std::string dest) {
    _source = std::move(source);
     _destination = std::move(dest);
    curr_course = _source;
    change_destination(curr_course);
    setState("Moving to");
}

void Peasant::change_destination(const string &dest) {
    for(const auto& s : Model::get_Instance().getStructList()) {
        if(s->getName() == dest) {
            destination_point->x = s->get_location()->x;
            destination_point->y = s->get_location()->y;
            break;
        }
    }
}

void Peasant::clear_boxes() {
    num_boxes = 0;
}
