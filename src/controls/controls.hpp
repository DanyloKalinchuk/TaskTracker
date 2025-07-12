#pragma once

#include "../task/info/info.hpp"

namespace controls{
    void add(Tasks_List&, const std::string&);
    void add(Tasks_List&, const int&, const std::string&);

    void del(Tasks_List&, const int&);
    void del(Tasks_List&, const int&, const int&);

    void set_status(Tasks_List&, const int&, const sts::Status&);
    void set_status(Tasks_List&, const int&, const int&, const sts::Status&);

    void set_description(Tasks_List&, const int&, const std::string&);
    void set_description(Tasks_List&, const int&, const int&, const std::string&);
    
    void info_list(Tasks_List&);
    void info_task(Tasks_List&, const int&);
    void info_sub_task_list(Tasks_List&, const int&);
    void info_sub_task(Tasks_List&, const int&, const int&);

    void list_by_status(Tasks_List&, sts::Status&);
    void list_by_status(Tasks_List&, const int&, sts::Status&);

    void help();
};