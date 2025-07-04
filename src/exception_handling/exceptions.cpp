#include "exceptions.hpp"

const std::unordered_map<exception_type, std::string> input_exception::exception_to_string = {
    {exception_type::invalid_sub_id, "Invalid sub-task id"},
    {exception_type::invalid_task_id, "Invalid task id"}    
};

Invalid_Id::Invalid_Id(const exception_type& type):
    type(type) {}

exception_type Invalid_Id::get_type() const{
    return this->type;
}

void input_exception::invalid_task_id(Tasks_List& tasks){
    "Valid task id values:\n";
    info::print_tasks_list(tasks);
}

void input_exception::invalid_sub_id(Tasks_List& tasks, const int& task_id){
    std::cerr << "Valid sub-task id values:\n";
    std::vector<std::unique_ptr<Task>>& list = tasks.get_tasks();
    info::print_sub_tasks_list(list[task_id]);    
}

void input_exception::invalid_id(Tasks_List& tasks, Invalid_Id& e, const int& task_id){
    if (e.get_type() == exception_type::invalid_task_id || task_id == -1){
        input_exception::invalid_task_id(tasks);
    }else{
        input_exception::invalid_sub_id(tasks, task_id);
    }
}

void input_exception::invalid_command(){
    std::cerr << "Invalid command. Use help to see the list of commands.\n";
    exit(1);
}