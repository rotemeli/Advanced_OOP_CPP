#include "Controller.h"


void Controller::run(int argc, char **argv) {
    read_file(argv[1]);
    read_file(argv[2]);

    std::stringstream ss;
    std::string op;

    // For attack
    std::string peasant_name;
    std::shared_ptr<Agent> agent_thug;
    bool attack = true;

    while(true) {
        std::cout << "Time " << Model::get_Instance().getTime() << ": enter command: " << std::endl;
        std::getline(std::cin, op);
        ss.clear();
        ss.str(op);
        ss >> op;

        if(op == "exit") {
            break;
        }
        // View commands
        else if(op == "default") {
            Model::get_Instance().getView()->default_size();
        }

        else if(op == "size") {
            int x;
            ss >> x;
            if(!ss) {
                std::cout << "ERROR: Expected an integer." << std::endl;
                continue;
            }
            Model::get_Instance().getView()->new_size(x);
        }

        else if(op == "zoom") {
            double z;
            ss >> z;
            if(!ss) {
                std::cout << "ERROR: Expected a double." << std::endl;
                continue;
            }
            Model::get_Instance().getView()->new_zoom(z);
        }

        else if(op == "pan") {
            double x, y;
            ss >> x; ss >> y;
            Model::get_Instance().getView()->pan(x, y);
        }

        else if(op == "show") {
            Model::get_Instance().getView()->clear();
            Model::get_Instance().insert_objects();
            Model::get_Instance().getView()->show();
        }

        // Model commands
        else if(op == "status") {
            Model::get_Instance().status();
        }

        else if(op == "go") {
            Model::get_Instance().go();
            if(!attack) {
                // Checks if the attack can be performed next time
                std::shared_ptr<Thug> thug = std::dynamic_pointer_cast<Thug>(agent_thug);
                attack = thug->attack(peasant_name);
                peasant_name.clear();
                attack = true;
            }
        }

        else if(op == "create") {
            std::string name, agent_type, start_point;
            ss >> name; ss >> agent_type; getline(ss, start_point);
            if(Model::agent_exist(name)) {
                std::cout << "Agent " << name << " already exist." << std::endl;
                continue;
            }
            Model::get_Instance().create(name, agent_type, start_point);
        }

        // Agent commands
        else {
            std::string name, agent_type;
            name = op;
            if(!Model::agent_exist(name)) {
                std::cout << "Agent " << name << " not exist." << std::endl;
                continue;
            }
            agent_type = Model::check_agent_type(name);
            ss >> op;
            if(op == "course") {
                double angle;
                if(agent_type == "Thug") {
                    double speed;
                    ss >> angle;
                    ss >> speed;
                    std::shared_ptr<Agent> a = Model::get_Instance().get_agent(name);
                    a->course(angle, speed);
                }
                else if(agent_type == "Knight") {
                    ss >> angle;
                    std::shared_ptr<Agent> a = Model::get_Instance().get_agent(name);
                    a->course(angle);
                }
            }

            else if(op == "position") {
                double x, y;
                if(agent_type == "Knight") {
                    ss >> x; ss >> y;
                    Model::get_Instance().get_agent(name)->position(x, y);
                }
                else if(agent_type == "Thug") {
                    double speed;
                    ss >> x; ss >> y; ss >> speed;
                    Model::get_Instance().get_agent(name)->position(x, y, speed);
                }
                else {
                    std::cout << "Agent of type " << agent_type << " cannot use position." << std::endl;
                }
            }

            else if(op == "destination") {
                std::string dest;
                ss >> dest;
                std::shared_ptr<Agent> a = Model::get_Instance().get_agent(name);
                if(agent_type == "Knight") {
                    std::shared_ptr<Knight> k = std::dynamic_pointer_cast<Knight>(a);
                    if(k) {
                        k->destination(dest);
                    }
                }
            }

            else if(op == "stop") {
                Model::get_Instance().get_agent(name)->setState("Stopped");
            }

            else if(op == "attack") {
                if(agent_type != "Thug") {
                    std::cout << "Agent " << name << " cannot use attack!" << std::endl;
                    continue;
                }
                ss >> peasant_name;
                agent_thug = Model::get_Instance().get_agent(name);
                std::shared_ptr<Thug> thug = std::dynamic_pointer_cast<Thug>(agent_thug);
                attack = thug->attack(peasant_name);
            }

            else if(op == "start_working") {
                if(!(agent_type == "Peasant")) {
                    continue;
                }
                std::string source, dest;
                ss >> source; ss >> dest;
                std::shared_ptr<Agent> a = Model::get_Instance().get_agent(name);
                std::shared_ptr<Peasant> p = std::dynamic_pointer_cast<Peasant>(a);
                if(p) {
                    p->start_working(source, dest);
                }
            }

            else {
                std::cout << "Invalid command!" << std::endl;
                continue;
            }
        }
    }
}

void Controller::helper(const string &str, string &s1, string &s2, string &s3, string &s4, string &s5) {
    std::stringstream ss;
    ss.str(str);
    std::string tmp;
    int count = 1;
    while (std::getline(ss, tmp, ',')) {
        switch (count) {
            case 1:
                s1 = tmp;
                count++;
                break;
            case 2:
                s2 = tmp;
                count++;
                break;
            case 3:
                s3 = tmp;
                count++;
                break;
            case 4:
                s4 = tmp;
                count++;
                break;
            case 5:
                s5 = tmp;
                break;
            default:
                count = 1;
                break;
        }
    }
}

void Controller::read_file(const string &file_name) {
    std::ifstream file(file_name);
    if(!file) {
        throw FileNotFound("File " + file_name + " Not Found!\n");
    }
    std::string tmp;
    std::string name, x_point, y_point, boxes, prod;
    double x, y;

    while (std::getline(file, tmp)) {
        prod.clear();
        helper(tmp, name, x_point, y_point, boxes, prod);
        x_point.erase(0, 2);
        y_point.erase(y_point.size()-1);
        x = stod(x_point);
        y = stod(y_point);

        if(prod.empty()) {
            std::shared_ptr<Castle> castle(new Castle(name, x, y, stoi(boxes)));
            Model::get_Instance().addSimObj(castle);
            Model::get_Instance().addStructure(castle);
        } else {
            std::shared_ptr<Farm> farm(new Farm(name, x, y, stoi(boxes), stoi(prod)));
            Model::get_Instance().addSimObj(farm);
            Model::get_Instance().addStructure(farm);
        }
    }
    file.close();
}
