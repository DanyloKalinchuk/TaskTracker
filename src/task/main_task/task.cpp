#include "task.hpp"

Task::Task(const int& id, const std::string& description) :
    Base_Task(id, description) {}

Task::Task(const int& id, const std::string& description, const std::string& creation_date) :
    Base_Task(id, description, creation_date) {}

void Task::add_sub_task(const std::string& description){
    int sub_id;
    if (this->unused_ids.size() == 0){
        sub_id = this->sub_tasks.size();
    }else{
        auto it = this->unused_ids.begin();
        sub_id = *it;
        this->unused_ids.erase(this->unused_ids.begin());
    }

    std::unique_ptr<Base_Task> sub_task = std::make_unique<Base_Task>(sub_id, description);

    if (sub_id == this->sub_tasks.size()){
        this->sub_tasks.push_back(std::move(sub_task));
    }else{
        this->sub_tasks[sub_id] = std::move(sub_task);
    }
    
    this->update_last_update();
}

void Task::del_sub_task(const int& id){
    if (this->sub_tasks.size() <= id || this->sub_tasks[id] == nullptr){
        throw std::invalid_argument("Invalid sub-task id value!");
    }
    this->sub_tasks[id] = nullptr;
    this->unused_ids.insert(id);

}

std::vector<int> Task::ids_by_status(sts::Status& status){
    std::vector<int> list;
    for (const auto& sub_task : this->sub_tasks){
        if (sub_task != nullptr && sub_task->get_status() == status){
            list.push_back(sub_task->get_id());
        }
    }
    return list;
}

std::vector<std::unique_ptr<Base_Task>>& Task::get_sub_tasks(){
    return this->sub_tasks;
}

bool Task::sub_tasks_empty(){
    if (this->unused_ids.size() == this->sub_tasks.size()){
        return true;
    }
    return false;
}

void Task::update_sub_tasks_description(const int& sub_id, const std::string& description){
    this->sub_tasks[sub_id]->update_description(description);
}

void Task::update_sub_task_status(const int& sub_id, const sts::Status& status){
    this->sub_tasks[sub_id]->update_status(status);
}

Json::Value Task::to_json() const{
    Json::Value root = Base_Task::to_json();

    Json::Value sub_tasks_arr(Json::arrayValue);
    for (const auto& sub_task : this->sub_tasks){
        if (sub_task != nullptr){
            sub_tasks_arr.append(sub_task->to_json());
        }
    }
    root["sub_tasks"] = sub_tasks_arr;

    Json::Value ununsed_ids_arr(Json::arrayValue);
    for (const int& id : this->unused_ids){
        ununsed_ids_arr.append(id);
    }
    root["unused_ids"] = ununsed_ids_arr;

    return root;
}

void Task::from_json(const Json::Value& root){
    this->update_status(sts::string_to_status.at(root["status"].asString()));
    this->set_last_update(root["last_update"].asString());

    for (const auto& sub_task_json : root["sub_tasks"]){
        std::unique_ptr<Base_Task> sub_task = Base_Task::from_json(sub_task_json);
        while(this->sub_tasks.size() <= sub_task->get_id()){
            this->sub_tasks.push_back(nullptr);
        }
        this->sub_tasks[sub_task->get_id()] = std::move(sub_task);
    }

    for (const auto& id_json : root["unused_ids"]){
        this->unused_ids.insert(id_json.asInt());
    }
}