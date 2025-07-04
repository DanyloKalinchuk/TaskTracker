#pragma once

#include "../tasks_list/tasks_list.hpp"

namespace info{
    void print_sub_task_info(std::unique_ptr<Base_Task>&);
    
    void print_task_info(std::unique_ptr<Task>&);
    void print_sub_tasks_list(std::unique_ptr<Task>&);
    void print_sub_tasks_by_status(std::unique_ptr<Task>&, sts::Status&);

    void print_tasks_list(Tasks_List&);
    void print_tasks_by_status(Tasks_List&, sts::Status&);

    void commands_list();
};