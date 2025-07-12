#include "cmd.hpp"

static void cmd_add(Tasks_List& tasks, const int& argc, char ** argv){
    std::string description = std::string(argv[2]);
    if (description.size() == 0){
        description = "New Task";
    }

    if (argc == 3){
        controls::add(tasks, description);
    }else{
        std::stringstream cnvrt_task_id{argv[3]};
        int task_id;
        if (!(cnvrt_task_id >> task_id)){
            throw std::invalid_argument("Invalid task id value!");
        }
        cnvrt_task_id >> task_id;
        controls::add(tasks, task_id, description);
    }
}

static void cmd_delete(Tasks_List& tasks, const int& argc, char ** argv){
    std::stringstream cnvrt_task_id{argv[2]};
    int task_id;
    if (!(cnvrt_task_id >> task_id)){
        throw std::invalid_argument("Invalid task id value!");
    }
    cnvrt_task_id >> task_id;

    if (argc == 3){
        controls::del(tasks, task_id);
    }else{
        std::stringstream cnvrt_sub_id{argv[3]};
        int sub_id;
        if (!(cnvrt_sub_id >> sub_id)){
            throw std::invalid_argument("Invalid sub-task id value!");
        }
        cnvrt_sub_id >> sub_id;
        controls::del(tasks, task_id, sub_id);
    }
}

static void cmd_status(Tasks_List& tasks, const int& argc, char ** argv, const sts::Status& status){
    std::stringstream cnvrt_task_id{argv[2]};
    int task_id;
    if (!(cnvrt_task_id >> task_id)){
        throw std::invalid_argument("Invalid task id value!");
    }
    cnvrt_task_id >> task_id;

    if (argc == 3){
        controls::set_status(tasks, task_id, status);
    }else{
        std::stringstream cnvrt_sub_id{argv[3]};
        int sub_id;
        if (!(cnvrt_sub_id >> sub_id)){
            throw std::invalid_argument("Invalid sub-task id value!");
        }
        cnvrt_sub_id >> sub_id;
        controls::set_status(tasks, task_id, sub_id, status);
    }    
}

static void cmd_set_desc(Tasks_List& tasks, const int& argc, char ** argv){
    std::string description = std::string(argv[2]);

    std::stringstream cnvrt_task_id{argv[3]};
    int task_id;
    if (!(cnvrt_task_id >> task_id)){
        throw std::invalid_argument("Invalid task id value!");
    }
    cnvrt_task_id >> task_id;

    if (argc == 4){
        controls::set_description(tasks, task_id, description);
    }else{
        std::stringstream cnvrt_sub_id{argv[4]};
        int sub_id;
        if (!(cnvrt_sub_id >> sub_id)){
            throw std::invalid_argument("Invalid sub-task id value!");
        }
        cnvrt_sub_id >> sub_id;

        controls::set_description(tasks, task_id, sub_id, description);
    }
}

static void cmd_info(Tasks_List& tasks, const int& argc, char ** argv){
    if (std::string(argv[2]) == "tasks"){
        controls::info_list(tasks);
    }else{
        std::stringstream cnvrt_task_id{argv[2]};
        int task_id;
        if (!(cnvrt_task_id >> task_id)){
            throw std::invalid_argument("Invalid task id value!");
        }
        cnvrt_task_id >> task_id;

        if (argc == 3){
            controls::info_task(tasks, task_id);
        }else{
            if (std::string(argv[3]) == "-sub"){
                controls::info_sub_task_list(tasks, task_id);
            }else{
                std::stringstream cnvrt_sub_id{argv[3]};
                int sub_id;
                if (!(cnvrt_sub_id >> sub_id)){
                    throw std::invalid_argument("Invalid sub-task id value!");
                }
                cnvrt_sub_id >> sub_id;
                controls::info_sub_task(tasks, task_id, sub_id);
            }
        }                    
    }
}

static void cmd_status_list(Tasks_List& tasks, const int& argc, char ** argv){
    std::string status_str = std::string(argv[2]);
    if(sts::string_to_status.find(status_str) == sts::string_to_status.end()){
        throw std::invalid_argument("Invalid status value!");
    }
    sts::Status status = sts::string_to_status.at(status_str);

    if (argc == 3){
        controls::list_by_status(tasks, status);
    }else{
        std::stringstream cnvrt_task_id{argv[3]};
        int task_id;
        if(!(cnvrt_task_id >> task_id)){
            throw std::invalid_argument("Invalid task id value!");
        }
        cnvrt_task_id >> task_id;

        controls::list_by_status(tasks, task_id, status);
    }
}

void cmd::cmd_handler(const int& argc, char ** argv){
    if (argc > 1){
        std::string cmd = std::string(argv[1]);

        if (cmd == "help"){
            controls::help();
        }else if (argc < 3 || argc > 5) throw std::invalid_argument("Invalid command!");
        
        else{
            Tasks_List tasks = json_handler::read();

            if (cmd == "add"){
                cmd_add(tasks, argc, argv);
            }else if (cmd == "delete"){
                cmd_delete(tasks, argc, argv);
            }else if (cmd == "set_status_to_do"){
                cmd_status(tasks, argc, argv, sts::to_do);
            }else if (cmd == "set_status_in_progress"){
                cmd_status(tasks, argc, argv, sts::in_progress);
            }else if (cmd == "set_status_done"){
                cmd_status(tasks, argc, argv, sts::done);
            }else if (cmd == "set_desc"){
                cmd_set_desc(tasks, argc, argv);
            }else if (cmd == "info"){
                cmd_info(tasks, argc, argv);
            }else if (cmd == "status"){
                cmd_status_list(tasks, argc, argv);
            }

            json_handler::write(tasks);
        }

    }else throw std::invalid_argument("Invalid command!");
}