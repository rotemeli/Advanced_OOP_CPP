#include "Thug.h"


Thug::Thug(std::string name, double x, double y) : Agent(std::move(name), 5, "Stopped") {
    _location = std::make_shared<Point>(x, y);
    _speed = -1;
    direction = -1;
    destination = std::make_shared<Point>();
}

const shared_ptr<Point> &Thug::get_location() const {
    return _location;
}

bool Thug::attack(const std::string& peasant_name) {
    if(!Model::agent_exist(peasant_name)) {
        std::cout << "Peasant " << peasant_name << " not exist." << std::endl;
        return false;
    }
    if(Model::check_agent_type(peasant_name) != "Peasant") {
        std::cout << "Agent " << peasant_name << " is not peasant." << std::endl;
        return false;
    }
    std::shared_ptr<Agent> agent = Model::get_Instance().get_agent(peasant_name);
    std::shared_ptr<Peasant> peasant = std::dynamic_pointer_cast<Peasant>(agent);
    double x = _location->x - peasant->get_location()->x;
    double y = _location->y - peasant->get_location()->y;
    double distance = sqrt(x*x + y*y) * 10;

    if(distance <=1) {
        peasant->setHealth(peasant->getHealth() - 1);
    }
    
    // checking if an attack can be done
    if( (getHealth() > peasant->getHealth()) && distance <=1 && !close_knight_checker() ) {
        // Peasant update
        peasant->clear_boxes();
        if(peasant->getHealth() == 0) {
            peasant->setState("Dead");
        } else {
            peasant->setState("Stopped");
        }

        // Thug update
        setState("Stopped");
        setHealth(getHealth() + 1);

        std::cout << "The attack was successful." << std::endl;
        return true;
    }

    setHealth(getHealth() - 1);
    if(getHealth() == 0) {
        setState("Dead");
    } else {
        setState("Stopped");
    }
    std::cout << "The attack was unsuccessful." << std::endl;
    return false;
}

void Thug::update() {
    if(getState() != "Stopped" && getState() != "Dead") {
        if(getState() == "Moving on course") {
            double rad_angle = to_radians(direction);
            double col_offset = _speed * cos(rad_angle) / 10;
            double row_offset = _speed * sin(rad_angle) / 10;
            _location->x += row_offset;
            _location->y += col_offset;
        }
        else if(getState() == "Moving to") {
            Point d1(destination->x - _location->x, destination->y - _location->y);
            double distance = sqrt(d1.x*d1.x + d1.y*d1.y);
            if(distance >= 1) {
                double x_offset = d1.x / distance;
                double y_offset = d1.y / distance;
                _location->x += x_offset;
                _location->y += y_offset;
            } else {
                setState("Stopped");
            }
        }
    }
}

void Thug::broadcast_current_state() {
    std::cout << "Thug " << getName() << " at ";
    _location->print();

    if(getState() == "Moving on course") {
        std::cout << ", Heading on course " << direction << " deg, speed " << _speed << " km/h" << std::endl;
    }
    else if(getState() == "Moving to") {
        std::cout << ", Moving to ";
        destination->print();
        std::cout << " , speed " << _speed << " km/h" << std::endl;
    }
    else if(getState() == "Stopped"){
        std::cout << ", Stopped" << std::endl;
    }

}

void Thug::course(double angle, double speed) {
    if(speed < 1 || speed > 30) {
        std::cout << "invalid speed\n";
        return;
    }
    if(angle < 0 || angle > 360) {
        std::cout << "invalid angle\n";
        return;
    }
    direction = angle;
    _speed = speed;
    setState("Moving on course");
}

void Thug::position(double x, double y, double speed) {
    destination->x = x;
    destination->y = y;
    _speed = speed;
    std::string state = "Moving to";
}

bool Thug::close_knight_checker() {
    for(auto const& obj : Model::get_Instance().getAgentList()) {
        if(Model::check_agent_type(obj->getName()) == "Knight") {
            double x = _location->x - obj->get_location()->x;
            double y = _location->y - obj->get_location()->y;
            double distance = sqrt(x*x + y*y) * 10;
            if(distance <= 2.5) {
                return true;
            }
        }
    }
    return false;
}
