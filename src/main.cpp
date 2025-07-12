#include <sstream>
#include "cmd/cmd.hpp"

int main(int argc, char* argv[]){
    try{
        cmd::cmd_handler(argc, argv);
    }
    catch (std::invalid_argument e){
        std::cerr << e.what() << "\n";
        std::cerr << "To see the command list use \'help\' command\n";
        return -1;
    }
    

    return 0;
}