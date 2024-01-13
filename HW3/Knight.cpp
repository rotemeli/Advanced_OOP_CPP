#include "Knight.h"

Knight::Knight(std::string name, std::string start_location) : Agent(std::move(name), 20, "Stopped") {
    bool flag = true;
    for(const auto& s :  Model::get_Instance().getStructList()) {
        if(s->getName() == start_location) {
            location_point = std::make_shared<Point>(s->get_location()->x, s->get_location()->y);
            flag = false;
            break;
        }
    }
    if(flag) {
        std::cout << "Structure " << start_location << " not exist." << std::endl;
        exit(-1);
    }
    _start_location = std::move(start_location);
    _speed = 10;
    _destination = "";
    direction = -1;
    destination_point = std::make_shared<Point>();
    visited_sites.insert(_start_location);
}

const shared_ptr<Point> &Knight::get_location() const {
    return location_point;
}

void Knight::update() {
    if(getState() != "Stopped") {
        if(getState() == "Moving to destination") {
            Point d1(destination_point->x - location_point->x, destination_point->y - location_point->y);
            double distance1 = sqrt(d1.x*d1.x + d1.y*d1.y);
            double x_offset = d1.x / distance1;
            double y_offset = d1.y / distance1;
            location_point->x += x_offset;
            location_point->y += y_offset;
            
            Point d2(location_point->x - destination_point->x, location_point->y - destination_point->y);
            double distance2 = sqrt(d2.x*d2.x + d2.y*d2.y);
            if(distance2 < 1) {
                location_point->x = destination_point->x;
                location_point->y = destination_point->y;

                visited_sites.insert(_destination);

                if(visited_sites.size() == Model::get_Instance().getStructList().size()) {
                    std::shared_ptr<Structure> s = Model::get_Instance().get_struct(_start_location);
                    location_point->x = s->get_location()->x;
                    location_point->y = s->get_location()->y;
                    setState("Stopped");
                    visited_sites.clear();
                }
                else {
                    destination(get_next_site());
                }
            }
        }
        else if(getState() == "Moving on course") {
            double rad_angle = to_radians(direction);
            double col_offset = _speed * cos(rad_angle) / 10;
            double row_offset = _speed * sin(rad_angle) / 10;
            location_point->x += row_offset;
            location_point->y += col_offset;
        }
        else if(getState() == "Moving to") {
            Point d1(destination_point->x - location_point->x, destination_point->y - location_point->y);
            double distance = sqrt(d1.x*d1.x + d1.y*d1.y);
            if(distance >= 1) {
                double x_offset = d1.x / distance;
                double y_offset = d1.y / distance;
                location_point->x += x_offset;
                location_point->y += y_offset;
            } else {
                setState("Stopped");
            }
        }
    }
}

void Knight::course(double angle) {
    if(angle < 0 || angle > 360) {
        std::cout << "invalid angle\n";
        return;
    }
    direction = angle;
    setState("Moving on course");
}

void Knight::position(double x, double y) {
    destination_point->x = x;
    destination_point->y = y;
    setState("Moving to");
}

void Knight::destination(std::string dest) {
    _destination = std::move(dest);
    for(const auto& s : Model::get_Instance().getStructList()) {
        if(s->getName() == _destination) {
            destination_point->x = s->get_location()->x;
            destination_point->y = s->get_location()->y;
            break;
        }
    }
    setState("Moving to destination");
}

void Knight::broadcast_current_state() {
    std::cout << "Knight " << getName() << " at ";
    location_point->print();
    if(getState() != "Moving to destination") {
        std::cout << ", Heading to " << _destination << ", speed 10 km/h" << std::endl;
    }
    else if(getState() == "Moving on course") {
        std::cout << ", Heading on course " << direction << " deg, speed 10 km/h" << std::endl;
    }
    else if(getState() == "Moving to") {
        std::cout << ", Moving to ";
        destination_point->print();
        std::cout << " , speed 10 km/h" << std::endl;
    }
    else if(getState() == "Stopped"){
        std::cout << ", Stopped" << std::endl;
    }
}

std::string Knight::get_next_site() {
    std::string closest_site;
    double distance1;

    for(const auto &obj : Model::get_Instance().getStructList()) {
        auto it = visited_sites.find(obj->getName());
        if(it == visited_sites.end()) {
            closest_site = obj->getName();
            Point d(location_point->x - obj->get_location()->x, location_point->y - obj->get_location()->y);
            distance1 = sqrt(d.x*d.x + d.y*d.y);
            break;
        }
    }

    for(const auto &obj : Model::get_Instance().getStructList()) {
        auto it = visited_sites.find(obj->getName());
        if(it == visited_sites.end()) {
            Point d(location_point->x - obj->get_location()->x, location_point->y - obj->get_location()->y);
            double distance2 = sqrt(d.x*d.x + d.y*d.y);
            if(distance2 < distance1) {
                closest_site = obj->getName();
            }
            else if(distance2 == distance1) {
                if(obj->getName() < closest_site) {
                    closest_site = obj->getName();
                }
            }
        }
    }
    return closest_site;
}
