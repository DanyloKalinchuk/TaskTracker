#include <sstream>
#include "in_out/in_out.hpp"
#include "controls/controls.hpp"

int main(int argc, char* argv[]){
    Tasks_List tasks = json_handler::read();
    if (argc > 1){
        std::string cmd = std::string(argv[1]);

        if (cmd == "help"){
            controls::help();
        }else if (argc < 3 || argc > 5) input_exception::invalid_command();

        else if (cmd == "add"){
            try{
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
                        throw std::invalid_argument("Invalid command");
                    }
                    cnvrt_task_id >> task_id;
                    controls::add(tasks, task_id, description);
                }

            }
            catch(std::invalid_argument e){
                input_exception::invalid_command();
            }
        }else if (cmd == "delete"){
            try{
                std::stringstream cnvrt_task_id{argv[2]};
                int task_id;
                if (!(cnvrt_task_id >> task_id)){
                    throw std::invalid_argument("Invalid command");
                }
                cnvrt_task_id >> task_id;

                if (argc == 3){
                    controls::del(tasks, task_id);
                }else{
                    std::stringstream cnvrt_sub_id{argv[3]};
                    int sub_id;
                    if (!(cnvrt_sub_id >> sub_id)){
                        throw std::invalid_argument("Invalid command");
                    }
                    cnvrt_sub_id >> sub_id;
                    controls::del(tasks, task_id, sub_id);
                }
            }
            catch(std::invalid_argument e){
                input_exception::invalid_command();
            }           
        }else if (cmd == "set_status_to_do"){
            try{
                std::stringstream cnvrt_task_id{argv[2]};
                int task_id;
                if (!(cnvrt_task_id >> task_id)){
                    throw std::invalid_argument("Invalid command");
                }
                cnvrt_task_id >> task_id;

                if (argc == 3){
                    controls::set_status(tasks, task_id, sts::to_do);
                }else{
                    std::stringstream cnvrt_sub_id{argv[3]};
                    int sub_id;
                    if (!(cnvrt_sub_id >> sub_id)){
                        throw std::invalid_argument("Invalid command");
                    }
                    cnvrt_sub_id >> sub_id;
                    controls::set_status(tasks, task_id, sub_id, sts::to_do);
                }
            }
            catch(std::invalid_argument e){
                input_exception::invalid_command();
            }                        
        }else if (cmd == "set_status_in_progress"){
            try{
                std::stringstream cnvrt_task_id{argv[2]};
                int task_id;
                if (!(cnvrt_task_id >> task_id)){
                    throw std::invalid_argument("Invalid command");
                }
                cnvrt_task_id >> task_id;

                if (argc == 3){
                    controls::set_status(tasks, task_id, sts::in_progress);
                }else{
                    std::stringstream cnvrt_sub_id{argv[3]};
                    int sub_id;
                    if (!(cnvrt_sub_id >> sub_id)){
                        throw std::invalid_argument("Invalid command");
                    }
                    cnvrt_sub_id >> sub_id;
                    controls::set_status(tasks, task_id, sub_id, sts::in_progress);
                }
            }
            catch(std::invalid_argument e){
                input_exception::invalid_command();
            }                        
        }else if (cmd == "set_status_done"){
            try{
                std::stringstream cnvrt_task_id{argv[2]};
                int task_id;
                if (!(cnvrt_task_id >> task_id)){
                    throw std::invalid_argument("Invalid command");
                }
                cnvrt_task_id >> task_id;

                if (argc == 3){
                    controls::set_status(tasks, task_id, sts::done);
                }else{
                    std::stringstream cnvrt_sub_id{argv[3]};
                    int sub_id;
                    if (!(cnvrt_sub_id >> sub_id)){
                        throw std::invalid_argument("Invalid command");
                    }
                    cnvrt_sub_id >> sub_id;
                    controls::set_status(tasks, task_id, sub_id, sts::done);
                }
            }
            catch(std::invalid_argument e){
                input_exception::invalid_command();
            }                        
        }else if (cmd == "set_desc"){
            std::string description = std::string(argv[2]);
            try{
                std::stringstream cnvrt_task_id{argv[3]};
                int task_id;
                if (!(cnvrt_task_id >> task_id)){
                    throw std::invalid_argument("Invalid command");
                }
                cnvrt_task_id >> task_id;

                if (argc == 4){
                    controls::set_description(tasks, task_id, description);
                }else{
                    std::stringstream cnvrt_sub_id{argv[4]};
                    int sub_id;
                    if (!(cnvrt_sub_id >> sub_id)){
                        throw std::invalid_argument("Invalid command");
                    }
                    cnvrt_sub_id >> sub_id;

                    controls::set_description(tasks, task_id, sub_id, description);
                }
            }
            catch(std::invalid_argument e){
                input_exception::invalid_command();
            }
        }else if (cmd == "info"){
            if (std::string(argv[2]) == "tasks"){
                controls::info_list(tasks);
            }else{
                try{
                    std::stringstream cnvrt_task_id{argv[2]};
                    int task_id;
                    if (!(cnvrt_task_id >> task_id)){
                        throw std::invalid_argument("Invalid command");
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
                                throw std::invalid_argument("Invalid command");
                            }
                            cnvrt_sub_id >> sub_id;
                            controls::info_sub_task(tasks, task_id, sub_id);
                        }
                    }                    
                }
                catch(std::invalid_argument e){
                    input_exception::invalid_command();
                }
            }
        }else if (cmd == "status"){
            try{
                std::string status_str = std::string(argv[2]);
                if(sts::string_to_status.find(status_str) == sts::string_to_status.end()){
                    throw 1;
                }
                sts::Status status = sts::string_to_status.at(status_str);

                if (argc == 3){
                    controls::list_by_status(tasks, status);
                }else{
                    std::stringstream cnvrt_task_id{argv[3]};
                    int task_id;
                    if(!(cnvrt_task_id >> task_id)){
                        throw std::invalid_argument("Invalid command");
                    }
                    cnvrt_task_id >> task_id;

                    controls::list_by_status(tasks, task_id, status);
                }
            }
            catch(int e){
                std::cerr << "Invalid status value\n" << "Satus value options: \n";
                for (const auto& [str, st] : sts::string_to_status){
                    std::cerr << "\t" << str << "\n";
                }
            }

            catch(std::invalid_argument e){
                input_exception::invalid_command();
            }
        }

    }else{
        input_exception::invalid_command();
    }

    json_handler::write(tasks);

    return 0;
}