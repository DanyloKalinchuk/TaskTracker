#include "info.hpp"

void info::print_sub_task_info(std::unique_ptr<Base_Task>&sub_task){
    std::cout << "\tId: " << sub_task->get_id() << "\n" <<
    "\tDescription: " << sub_task->get_description() << "\n" <<
    "\tStatus: " << sts::status_to_string.at(sub_task->get_status()) << "\n" <<
    "\tCreation Date: " << sub_task->get_creation_date() <<
    "\tLast Update: " << sub_task->get_last_update();
}

void info::print_task_info(std::unique_ptr<Task>& task){
    std::cout << "\tId: " << task->get_id() << "\n" <<
    "\tDescription: " << task->get_description() << "\n" <<
    "\tStatus: " << sts::status_to_string.at(task->get_status()) << "\n" <<
    "\tCreation Date: " << task->get_creation_date() <<
    "\tLast Update: " << task->get_last_update() << "\t";
    info::print_sub_tasks_list(task);    
}

void info::print_sub_tasks_list(std::unique_ptr<Task>& task){
    std::cout << "Sub-tasks:\n";

    if (task->sub_tasks_empty()){
        std::cout << "\t\tThere are no sub-tasks \n";
    }else{
        for (const auto& [id, sub_task] : task->get_sub_tasks()){
            std::cout << "\t\tId: " << sub_task->get_id() <<
            " Description: " << sub_task->get_description() << "\n";
        }
    }
}

void info::print_sub_tasks_by_status(std::unique_ptr<Task>& task, sts::Status& status){
    std::vector<int> ids = task->ids_by_status(status);

    if (ids.size() == 0){
        std::cout << "There are no sub_tasks with " << sts::status_to_string.at(status) <<
        " status\n";
    }else{
        std::cout << "Sub-tasks with " << sts::status_to_string.at(status) << " status:\n";
        for (const int& sub_id : ids){
            std::cout << "Id: " << task->get_sub_tasks()[sub_id]->get_id() <<
            " Description: " << task->get_sub_tasks()[sub_id]->get_description() << "\n";
        }
    }    
}

void info::print_tasks_list(Tasks_List& tasks){
    std::cout << "Tasks:\n";

    if (tasks.empty()){
        std::cout << "\tThere are no tasks \n";
    }else{
        for (const auto& [id, task] : tasks.get_tasks()){
            std::cout << "\tId: " << task->get_id() <<
            " Description: " << task->get_description() << "\n";
        }
    }
}

void info::print_tasks_by_status(Tasks_List& tasks, sts::Status& status){
    std::vector<int> ids = tasks.ids_by_status(status);

    if (ids.size() == 0){
        std::cout << "There are no tasks with " << sts::status_to_string.at(status) <<
        " status\n";
    }else{
        std::cout << "Tasks with " << sts::status_to_string.at(status) << " status:\n";
        for (const int& task_id : ids){
            std::cout << "Id: " << tasks.get_tasks()[task_id]->get_id() <<
            " Description: " << tasks.get_tasks()[task_id]->get_description() << "\n";
        }
    }
}

void info::commands_list(){
    std::cout <<
    "\thelp \'print commands\'\n" <<
    "\t------------------\n" <<
    "\tadd description \'add task\'\n" <<
    "\tadd description task_id \'add subtask for an existing task\'\n" <<
    "\tdelete task_id \'delete task by id\'\n" <<
    "\tdelete task_id sub_id \'delete subtask by its parent id and id\'\n" <<
    "\t------------------\n" <<
    "\tset_status_to_do task_id \'set status of the task to \'to_do\'\'\n" <<
    "\tset_status_to_do task_id sub_id \'set status of the sub-task to \'to_do\'\'\n" <<
    "\tset_status_in_progress task_id \'set status of the task to \'in_progrsess\'\'\n" <<
    "\tset_status_in_progress task_id sub_id\'set status of the task to \'in_progrsess\'\'\n" <<
    "\tset_status_done task_id \'set status of the task to \'done\'\'\n" <<
    "\tset_status_done task_id sub_id \'set status of the task to \'done\'\'\n" <<
    "\t------------------\n" << 
    "\tset_desc description task_id \'set new description to the task\'\n" <<
    "\tset_desc description task_id sub_id \'set new description to the sub-task\'\n" <<
    "\t------------------\n" << 
    "\tinfo tasks \'print the list of tasks\'\n" <<
    "\tinfo task_id \'print task information by id\'\n" <<
    "\tinfo task_id -sub \'print list of sub-tasks\'\n" <<
    "\tinfo task_id sub_id \'print sub-task information\'\n"
    "\t------------------\n" <<
    "\tstatus status_value \'print list of tasks with status of status value\'\n" <<
    "\tstatus status_value task_id \'print list of sub-tasks with status of status value\'\n";
}