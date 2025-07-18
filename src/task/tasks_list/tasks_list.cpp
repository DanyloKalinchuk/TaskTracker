#include "tasks_list.hpp"

void Tasks_List::add_task(const std::string& description){
    int id;
    if (this->unused_ids.size() == 0){
        id = this->next_id;
        this->next_id++;
    }else{
        auto it = this->unused_ids.begin();
        id = *it;
        this->unused_ids.erase(this->unused_ids.begin());
    }

    std::unique_ptr<Task> task = std::make_unique<Task>(id, description);
    this->tasks[id] = std::move(task);
}

void Tasks_List::del_task(const int& id){
    if (this->tasks.find(id) == this->tasks.end()){
        throw std::invalid_argument("Invalid task id value!");
    }
    this->tasks.erase(id);
    this->unused_ids.insert(id);
}

void Tasks_List::push_to_unused_ids(const int& id){
    this->unused_ids.insert(id);
}

void Tasks_List::set_next_id(int next_id){
    this->next_id = next_id;
}

std::set<int> Tasks_List::get_unused_ids(){
    return this->unused_ids;
}

int Tasks_List::get_next_id(){
    return this->next_id;
}

std::map<int, std::unique_ptr<Task>>& Tasks_List::get_tasks(){
    return this->tasks;
}

std::vector<int> Tasks_List::ids_by_status(const sts::Status& status){
    std::vector<int> list;
    for (const auto& [id, task] : this->tasks){
        if (task->get_status() == status){
            list.push_back(task->get_id());
        }
    }
    return list;
}

bool Tasks_List::empty(){
    if (this->tasks.size() == 0){
        return true;
    }
    return false;
}