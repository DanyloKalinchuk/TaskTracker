#pragma once

#include <exception>
#include "../task/info/info.hpp"

enum exception_type{
    invalid_task_id,
    invalid_sub_id
};

class Invalid_Id : public std::exception{
    exception_type type;

    public:
    Invalid_Id(const exception_type&);

    exception_type get_type() const;
};

namespace input_exception{
    extern const std::unordered_map<exception_type, std::string> exception_to_string;

    void invalid_task_id(Tasks_List&);
    void invalid_sub_id(Tasks_List&, const int&);
    void invalid_id(Tasks_List&, Invalid_Id&, const int&);

    void invalid_command();
};