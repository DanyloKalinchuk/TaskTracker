#include "tasks_list.hpp"

void Tasks_List::add_task(const std::string& description){
    int id;
    if (this->unused_ids.size() == 0){
        id = this->tasks.size();
    }else{
        auto it = this->unused_ids.begin();
        id = *it;
        this->unused_ids.erase(this->unused_ids.begin());
    }

    std::unique_ptr<Task> task = std::make_unique<Task>(id, description);

    if (id == this->tasks.size()){
        this->tasks.push_back(std::move(task));
    }else{
        this->tasks[id] = std::move(task);
    }
    
}

void Tasks_List::del_task(const int& id){
    if (this->tasks.size() <= id || this->tasks[id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    this->tasks[id] = nullptr;
    this->unused_ids.insert(id);
}

void Tasks_List::push_to_unused_ids(const int& id){
    this->unused_ids.insert(id);
}

std::set<int> Tasks_List::get_unused_ids(){
    return this->unused_ids;
}

std::vector<std::unique_ptr<Task>>& Tasks_List::get_tasks(){
    return this->tasks;
}

std::vector<int> Tasks_List::ids_by_status(const sts::Status& status){
    std::vector<int> list;
    for (const auto& task : this->tasks){
        if (task != nullptr && task->get_status() == status){
            list.push_back(task->get_id());
        }
    }
    return list;
}

bool Tasks_List::empty(){
    if (this->tasks.size() == this->unused_ids.size()){
        return true;
    }
    return false;
}