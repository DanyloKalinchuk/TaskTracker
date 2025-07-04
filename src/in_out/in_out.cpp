#include "in_out.hpp"

Tasks_List json_handler::read(){
    std::fstream input("tasks.json");
    Tasks_List tasks;

    if (input.is_open()){
        Json::Reader reader;
        Json::Value root;

        if (reader.parse(input, root)){
            for (const auto& task_json : root["tasks"]){
                std::unique_ptr<Task> task = std::make_unique<Task>(task_json["id"].asInt(), 
                    task_json["description"].asString(), task_json["creation_date"].asString());

                task->from_json(task_json);

                if (tasks.get_tasks().size() <= task->get_id()){
                    tasks.get_tasks().resize(task->get_id() + 1);
                }
                tasks.get_tasks()[task->get_id()] = std::move(task);
            }

            for (const auto& id_json : root["unused_ids"]){
                tasks.push_to_unused_ids(id_json.asInt());
            }
        }
        input.close();
    }

    return tasks;
}

void json_handler::write(Tasks_List& tasks){
    Json::Value root;

    Json::Value tasks_json(Json::arrayValue);
    for (const auto& task : tasks.get_tasks()){
        if (task != nullptr){
            tasks_json.append(task->to_json());
        }
    }
    root["tasks"] = tasks_json;

    Json::Value unused_ids_json(Json::arrayValue);
    for (const int& id : tasks.get_unused_ids()){
        unused_ids_json.append(id);
    }
    root["unused_ids"] = unused_ids_json;

    std::ofstream output("tasks.json");
    output << root;

    output.close();
}