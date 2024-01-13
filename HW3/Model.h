#ifndef EX03_ADVCPP_MODEL_H
#define EX03_ADVCPP_MODEL_H


#include <sstream>
#include "Farm.h"
#include "Castle.h"
#include "Peasant.h"
#include "Thug.h"
#include "Knight.h"
#include "View.h"

class Model {
private:
    static std::unique_ptr<Model> ptr;                          // Singleton instance pointer
    std::vector<std::shared_ptr<Sim_object>> sim_obj_list;      // List of simulation objects
    std::vector<std::shared_ptr<Structure>> struct_list;        // List of structures
    std::vector<std::shared_ptr<Agent>> agent_list;             // List of agents
    std::shared_ptr<View> view;                                 // View object for displaying the simulation

    int time;       // Current time in the simulation

    Model() {
        view = std::make_shared<View>();
        time = 0;
    }

    // Helper method to parse point string
    std::vector<double> create_helper(const std::string& point);

public:
    static Model& get_Instance();                       // Singleton instance getter

    ~Model() = default;

    // Prevent copy/move construction and assignment
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(Model&&) = delete;

    // Add a simulation object to the model
    void addSimObj(const std::shared_ptr<Sim_object>& sim);

    // Add a structure to the model
    void addStructure(const std::shared_ptr<Structure>& structure);

    // Add an agent to the model
    void addAgent(const std::shared_ptr<Agent>& agent);

    // Print the status of all simulation objects
    void status();

    // Advances the simulation by one time point
    void go();

    // Create a new agent or structure
    void create(const std::string& name, const std::string& agent_type, const std::string& point);

    // Insert the existing objects into the display
    void insert_objects();

    // Check if an agent with the given name exists
    static bool agent_exist(const std::string& agent_name);

    // Check the type of agent with the given name
    static std::string check_agent_type(const std::string& name);

    // Get the current time in the simulation
    int getTime() const;

    // Getters
    const std::vector<std::shared_ptr<Structure>> &getStructList() const;

    const std::vector<std::shared_ptr<Agent>> &getAgentList() const;

    const shared_ptr<View> &getView() const;

    std::shared_ptr<Agent> get_agent(const std::string& agent_name);

    std::shared_ptr<Structure> get_struct(const std::string& struct_name);



};


#endif //EX03_ADVCPP_MODEL_H
