#pragma once

#include <fstream>
#include "../task/tasks_list/tasks_list.hpp"

namespace json_handler{
    Tasks_List read();
    void write(Tasks_List&);
};