cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-mingw-static")

project(TaskTracker)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(TaskTracker
    src/main.cpp 
    src/task/base_task/base_task.cpp 
    src/task/info/info.cpp 
    src/task/main_task/task.cpp 
    src/task/tasks_list/tasks_list.cpp 
    src/controls/controls.cpp 
    src/cmd/cmd.cpp
    src/in_out/in_out.cpp
)

target_link_libraries(TaskTracker PRIVATE jsoncpp_static)

add_executable(BaseTaskTest
    src/test/task/test_base_task.cpp
    src/task/base_task/base_task.cpp
)

target_link_libraries(BaseTaskTest PRIVATE jsoncpp_static GTest::gtest GTest::gtest_main)

add_executable(TaskTest
    src/test/task/test_main_task.cpp
    src/task/base_task/base_task.cpp
    src/task/main_task/task.cpp
)

target_link_libraries(TaskTest PRIVATE jsoncpp_static GTest::gtest GTest::gtest_main)

add_executable(TasksListTest
    src/test/task/test_tasks_list.cpp
    src/task/base_task/base_task.cpp
    src/task/main_task/task.cpp
    src/task/tasks_list/tasks_list.cpp
)

target_link_libraries(TasksListTest PRIVATE jsoncpp_static GTest::gtest GTest::gtest_main)

add_executable(TestMain
    src/test/test_main.cpp
    src/test/task/test_base_task.cpp
    src/test/task/test_main_task.cpp
    src/test/task/test_tasks_list.cpp
    src/task/base_task/base_task.cpp
    src/task/main_task/task.cpp
    src/task/tasks_list/tasks_list.cpp
)

target_link_libraries(TestMain PRIVATE jsoncpp_static GTest::gtest GTest::gtest_main)