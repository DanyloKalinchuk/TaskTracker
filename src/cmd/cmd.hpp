#pragma once

#include <sstream>
#include "../in_out/in_out.hpp"
#include "../controls/controls.hpp"

namespace cmd{
    void cmd_handler(const int&, char **);
};

static void cmd_add(Tasks_List&, const int&, char **);
static void cmd_delete(Tasks_List&, const int&, char **);
static void cmd_status(Tasks_List&, const int&, char **, const sts::Status&);
static void cmd_set_desc(Tasks_List&, const int&, char **);
static void cmd_info(Tasks_List&, const int&, char **);
static void cmd_status_list(Tasks_List&, const int&, char **);