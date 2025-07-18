#include "base_task.hpp"

const std::map<sts::Status, std::string> sts::status_to_string = {
    {Status::to_do, "to_do"},
    {Status::in_progress, "in_progress"},
    {Status::done, "done"}    
};

const std::map<std::string, sts::Status> sts::string_to_status = {
    {"to_do", Status::to_do},
    {"in_progress", Status::in_progress},
    {"done", Status::done}    
};

std::string Base_Task::current_time(){
    std::time_t now = std::time(nullptr);
    std::tm * local_time = std::localtime(&now);
    
    return std::string(asctime(local_time));
}

void Base_Task::update_last_update(){
    this->last_update = Base_Task::current_time();
}

Base_Task::Base_Task(const int& id, const std::string& description):
    id(id), description(description), status(sts::Status::to_do),
    creation_date(Base_Task::current_time()), last_update(Base_Task::current_time()) {}

Base_Task::Base_Task(const int& id, const std::string& description, const std::string& creation_date):
    id(id), description(description), creation_date(creation_date), status(sts::Status::to_do),
    last_update(creation_date) {}

int Base_Task::get_id() const{
    return this->id;
}

std::string Base_Task::get_description(){
    return this->description;
}

sts::Status Base_Task::get_status(){
    return this->status;
}

std::string Base_Task::get_creation_date() const{
    return this->creation_date;
}

std::string Base_Task::get_last_update(){
    return this->last_update;
}

void Base_Task::update_description(const std::string& description){
    this->description = description;
    Base_Task::update_last_update();
}

void Base_Task::update_status(const sts::Status& status){
    this->status = status;
    Base_Task::update_last_update();
}

void Base_Task::set_last_update(const std::string& last_update){
    this->last_update = last_update;
}

Json::Value Base_Task::to_json() const{
    Json::Value root;

    root["id"] = this->id;
    root["description"] = this->description;
    root["status"] = sts::status_to_string.at(this->status);
    root["creation_date"] = this->creation_date;
    root["last_update"] = this->last_update;

    return root;
}

std::unique_ptr<Base_Task> Base_Task::from_json(const Json::Value& root){
    auto task = std::make_unique<Base_Task>(root["id"].asInt(), root["description"].asString(), root["creation_date"].asString());

    task->status = sts::string_to_status.at(root["status"].asString());
    task->last_update = root["last_update"].asString();

    return task;
}