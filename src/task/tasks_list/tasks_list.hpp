#pragma once

#include <stdexcept>
#include "../main_task/task.hpp"

struct Tasks_List{
    void add_task(const std::string&);
    void del_task(const int&);
    void push_to_unused_ids(const int&);
    void set_next_id(int);

    std::set<int> get_unused_ids();
    int get_next_id();
    std::map<int, std::unique_ptr<Task>>& get_tasks();
    std::vector<int> ids_by_status(const sts::Status&);
    bool empty();

    private:
    std::map<int, std::unique_ptr<Task>> tasks;
    std::set<int> unused_ids;
    int next_id = 0;
};