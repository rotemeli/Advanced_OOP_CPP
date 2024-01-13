#include "Model.h"

std::unique_ptr<Model> Model::ptr = nullptr;

Model &Model::get_Instance() {
    if(!ptr) {
        ptr = std::unique_ptr<Model>(new Model());
    }
    return *ptr;
}

void Model::addSimObj(const shared_ptr<Sim_object> &sim) {
    sim_obj_list.push_back(sim);
}

void Model::addStructure(const shared_ptr<Structure> &structure) {
    struct_list.push_back(structure);
}

void Model::addAgent(const std::shared_ptr<Agent>& agent) {
    agent_list.push_back(agent);
}

const std::vector<std::shared_ptr<Structure>> &Model::getStructList() const {
    return struct_list;
}

const std::vector<std::shared_ptr<Agent>> &Model::getAgentList() const {
    return agent_list;
}

const shared_ptr<View> &Model::getView() const {
    return view;
}

int Model::getTime() const {
    return time;
}

void Model::status() {
    std::cout << std::endl;
    for(const std::shared_ptr<Sim_object>& sim : Model::sim_obj_list) {
        sim->broadcast_current_state();
    }
    std::cout << std::endl;
}

void Model::go() {
    for(auto const& obj : sim_obj_list) {
        obj->update();
    }
    time++;
}

std::vector<double> Model::create_helper(const string &point) {
    std::vector<double> res(2);
    double x, y;
    std::string tmp;
    std::stringstream ss(point);
    ss >> tmp;
    tmp.erase(0, 1); tmp.erase(tmp.size()-1);
    x = stod(tmp);
    ss >> tmp;
    tmp.erase(tmp.size()-1);
    y = stod(tmp);
    res[0] = x;
    res[1] = y;
    return res;
}

void Model::create(const string &name, const std::string& agent_type, const std::string& point) {
    if(agent_type == "Peasant") {
        std::vector<double> tmp = create_helper(point);
        std::shared_ptr<Peasant> p(new Peasant(name, tmp[0], tmp[1]));
        sim_obj_list.push_back(p);
        agent_list.push_back(p);
    }
    else if(agent_type == "Thug") {
        std::vector<double> tmp = create_helper(point);
        std::shared_ptr<Thug> t(new Thug(name, tmp[0], tmp[1]));
        sim_obj_list.push_back(t);
        agent_list.push_back(t);
    }
    else if(agent_type == "Knight") {
        std::string temp;
        temp = point;
        temp.erase(0, 1);
        std::shared_ptr<Knight> k(new Knight(name, temp));
        sim_obj_list.push_back(k);
        agent_list.push_back(k);
    }
}

void Model::insert_objects() {
    for(auto const& obj : agent_list) {
        double min_x = view->getX();
        double max_x = min_x + view->getScale()*(view->getSize() - 1);
        double min_y = view->getY();
        double max_y = min_y + view->getScale()*(view->getSize() - 1);
        if((int)obj->get_location()->x < min_x || (int)obj->get_location()->x > max_x ||
                (int)obj->get_location()->y < min_y || (int)obj->get_location()->y > max_y) {
            continue;
        }

        std::string tmp = obj->getName();
        view->insert_obj((int)obj->get_location()->x, (int)obj->get_location()->y, tmp.substr(0, 2));
    }
    for(auto const& obj : struct_list) {
        double min_x = view->getX();
        double max_x = min_x + view->getScale()*(view->getSize() - 1);
        double min_y = view->getY();
        double max_y = min_y + view->getScale()*(view->getSize() - 1);
        if(obj->get_location()->x < min_x || obj->get_location()->x > max_x ||
           obj->get_location()->y < min_y || obj->get_location()->y > max_y) {
            continue;
        }

        std::string tmp = obj->getName();
        view->insert_obj((int)obj->get_location()->x, (int)obj->get_location()->y, tmp.substr(0, 2));
    }
}

std::shared_ptr<Agent> Model::get_agent(const std::string& agent_name) {
    for(auto& agent : agent_list) {
        if(agent->getName() == agent_name) {
            return agent;
        }
    }
    return nullptr;
}

std::shared_ptr<Structure> Model::get_struct(const string &struct_name) {
    for(auto& st : struct_list) {
        if(st->getName() == struct_name) {
            return st;
        }
    }
    return nullptr;
}

bool Model::agent_exist(const string &agent_name) {
    for(const auto& agent : Model::get_Instance().getAgentList()) {
        if(agent->getName() == agent_name) {
            return true;
        }
    }
    return false;
}

std::string Model::check_agent_type(const string &name) {
    std::string type;
    for(const auto& obj : Model::get_Instance().getAgentList()) {
        if(obj->getName() == name) {
            if(typeid(*obj) == typeid(Thug)) {
                type = "Thug";
                break;
            }
            else if(typeid(*obj) == typeid(Peasant)) {
                type = "Peasant";
                break;
            }
            else if(typeid(*obj) == typeid(Knight)) {
                type = "Knight";
                break;
            }
        }
    }
    return type;
}
