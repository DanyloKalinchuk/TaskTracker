#include "controls.hpp"

void controls::add(Tasks_List& tasks, const std::string& describtion){
    tasks.add_task(describtion);
}

void controls::add(Tasks_List& tasks, const int& task_id, const std::string& description){
    std::vector<std::unique_ptr<Task>>& list = tasks.get_tasks();
    if (task_id < 0 || list.size() <= task_id || list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }else{
        list[task_id]->add_sub_task(description);
    }
}

void controls::del(Tasks_List& tasks, const int& id){
    if (id < 0 || tasks.get_tasks().size() <= id || tasks.get_tasks()[id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }else{
        tasks.del_task(id);
    }
}

void controls::del(Tasks_List& tasks, const int& task_id, const int& sub_id){
    std::vector<std::unique_ptr<Task>>& list = tasks.get_tasks();

    if (task_id < 0 || list.size() <= task_id || list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }else if (list[task_id]->get_sub_tasks().size() <= sub_id || list[task_id]->get_sub_tasks()[sub_id] == nullptr){
        throw std::invalid_argument("Invalid sub-task id value!");
    }
    list[task_id]->del_sub_task(sub_id);
}

void controls::set_status(Tasks_List& tasks, const int& task_id, const sts::Status& status){
    std::vector<std::unique_ptr<Task>>& list = tasks.get_tasks();
    if (task_id < 0 || list.size() <= task_id || list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    list[task_id]->update_status(status);
}

void controls::set_status(Tasks_List& tasks, const int& task_id, const int& sub_id, const sts::Status& status){
    std::vector<std::unique_ptr<Task>>& task_list = tasks.get_tasks();
    if (task_id < 0 || task_list.size() <= task_id || task_list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    std::vector<std::unique_ptr<Base_Task>>& sub_list = task_list[task_id]->get_sub_tasks();
    if (sub_id < 0 || sub_list.size() <= sub_id || sub_list[sub_id] == nullptr){
        throw std::invalid_argument("Invalid sub-task id value!");
    }

    sub_list[sub_id]->update_status(status);   
}

void controls::set_description(Tasks_List& tasks, const int& task_id, const std::string& description){
    std::vector<std::unique_ptr<Task>>& task_list = tasks.get_tasks();
    if (task_id < 0 || task_list.size() < task_id || task_list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    task_list[task_id]->update_description(description);
}

void controls::set_description(Tasks_List& tasks, const int& task_id, const int& sub_id, const std::string& description){
    std::vector<std::unique_ptr<Task>>& task_list = tasks.get_tasks();
    if (task_id < 0 || task_list.size() <= task_id || task_list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    std::vector<std::unique_ptr<Base_Task>>& sub_list = task_list[task_id]->get_sub_tasks();
    if (sub_id < 0 || sub_list.size() <= sub_id || sub_list[sub_id] == nullptr){
        throw std::invalid_argument("Invalid sub-task id value!");
    }

    sub_list[sub_id]->update_description(description);  
}

void controls::info_list(Tasks_List& tasks){
    info::print_tasks_list(tasks);
}

void controls::info_task(Tasks_List& tasks, const int& task_id){
    std::vector<std::unique_ptr<Task>>& list = tasks.get_tasks();
    if (task_id < 0 || list.size() <= task_id || list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    info::print_task_info(list[task_id]);
}

void controls::info_sub_task_list(Tasks_List& tasks, const int& id){
    std::vector<std::unique_ptr<Task>>& list = tasks.get_tasks();
    if (id < 0 || list.size() <= id || list[id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    info::print_sub_tasks_list(list[id]);
}

void controls::info_sub_task(Tasks_List& tasks, const int& task_id, const int& sub_id){
    const std::vector<std::unique_ptr<Task>>& task_list = tasks.get_tasks();
    if (task_id < 0 || task_list.size() <= task_id || task_list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }
    auto& sub_list = task_list[task_id]->get_sub_tasks();
    if (sub_id < 0 || sub_list.size() <= sub_id || sub_list[sub_id] == nullptr){
        throw std::invalid_argument("Invalid sub-task id value!");
    }
    info::print_sub_task_info(sub_list[sub_id]);
}

void controls::list_by_status(Tasks_List& tasks, sts::Status& status){
    info::print_tasks_by_status(tasks, status);
}

void controls::list_by_status(Tasks_List& tasks, const int& task_id, sts::Status& status){
    std::vector<std::unique_ptr<Task>>& task_list = tasks.get_tasks();
    if (task_id < 0 || task_list.size() <= task_id || task_list[task_id] == nullptr){
        throw std::invalid_argument("Invalid task id value!");
    }

    info::print_sub_tasks_by_status(task_list[task_id], status);  
}

void controls::help(){
    info::commands_list();
}