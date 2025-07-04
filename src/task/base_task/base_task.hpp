#pragma once

#include <json/json.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <ctime>

namespace sts{
    enum Status{
        to_do,
        in_progress,
        done
    };

    extern const std::unordered_map<Status, std::string> status_to_string;
    extern const std::unordered_map<std::string, Status> string_to_status;
};

class Base_Task{
    const int id;
    std::string description;
    sts::Status status;
    const std::string creation_date;
    std::string last_update;

    std::string current_time();

    public:
    Base_Task(const int&, const std::string&);
    Base_Task(const int&, const std::string&, const std::string&);

    int get_id() const;
    std::string get_description();
    sts::Status get_status();
    std::string get_creation_date() const;
    std::string get_last_update();

    void update_last_update();

    void update_description(const std::string&);
    void update_status(const sts::Status&);
    void set_last_update(const std::string&);

    Json::Value to_json() const;
    std::unique_ptr<Base_Task> from_json(const Json::Value& root);
};