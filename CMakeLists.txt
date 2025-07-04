cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-mingw-static")

project(TaskTracker)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp CONFIG REQUIRED)

add_executable(TaskTracker
    src/main.cpp 
    src/task/base_task/base_task.cpp 
    src/task/info/info.cpp 
    src/task/main_task/task.cpp 
    src/task/tasks_list/tasks_list.cpp 
    src/controls/controls.cpp 
    src/exception_handling/exceptions.cpp 
    src/in_out/in_out.cpp
)

target_link_libraries(TaskTracker PRIVATE jsoncpp_static)