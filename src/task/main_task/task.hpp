#pragma once

#include <set>
#include <memory>
#include "../base_task/base_task.hpp"

class Task : public Base_Task{
    std::map<int, std::unique_ptr<Base_Task>> sub_tasks;
    std::set<int> unused_ids;
    int next_id = 0;

    public:
    Task(const int&, const std::string&);
    Task(const int&, const std::string&, const std::string&);

    void add_sub_task(const std::string&);
    void del_sub_task(const int&);

    std::vector<int> ids_by_status(sts::Status&);
    std::map<int, std::unique_ptr<Base_Task>>& get_sub_tasks();
    bool sub_tasks_empty();

    void update_sub_tasks_description(const int&, const std::string&);
    void update_sub_task_status(const int&, const sts::Status&);

    Json::Value to_json() const;
    void from_json(const Json::Value&);
};