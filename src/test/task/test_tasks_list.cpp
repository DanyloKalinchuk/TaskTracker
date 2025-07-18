#include <gtest/gtest.h>
#include "../../task/tasks_list/tasks_list.hpp"

TEST(TasksListTest, Initialization){
    std::unique_ptr<Tasks_List> tasks = std::make_unique<Tasks_List>();
    EXPECT_EQ(tasks->empty(), true);
    EXPECT_EQ(tasks->get_unused_ids().size(), 0);
}

TEST(TasksListTest, AddTask){
    std::unique_ptr<Tasks_List> tasks = std::make_unique<Tasks_List>();
    tasks->add_task("Task");
    ASSERT_EQ(tasks->get_tasks().size(), 1);
    ASSERT_NE(tasks->get_tasks()[0], nullptr);
    EXPECT_EQ(tasks->get_tasks()[0]->get_id(), 0);
    EXPECT_EQ(tasks->get_tasks()[0]->get_description(), "Task");
}

TEST(TasksListTest, DeleteTask){
    std::unique_ptr<Tasks_List> tasks = std::make_unique<Tasks_List>();
    tasks->add_task("Task");
    tasks->del_task(0);
    EXPECT_EQ(tasks->empty(), true);
}

TEST(TasksListTest, IdMaintenanceSubTask){
    std::unique_ptr<Tasks_List> tasks = std::make_unique<Tasks_List>();
    tasks->add_task("Task1");
    tasks->add_task("Task2");
    tasks->add_task("Task3");
    ASSERT_EQ(tasks->get_tasks().size(), 3);
    tasks->del_task(2);
    tasks->del_task(0);

    ASSERT_EQ(tasks->get_tasks()[0], nullptr);
    ASSERT_EQ(tasks->get_tasks()[2], nullptr);

    tasks->add_task("Task4");
    ASSERT_NE(tasks->get_tasks()[0], nullptr);
    EXPECT_EQ(tasks->get_tasks()[0]->get_id(), 0);
    EXPECT_EQ(tasks->get_tasks()[0]->get_description(), "Task4");
}

TEST(TasksListTest, LargeTaskNumber){
    std::unique_ptr<Tasks_List> tasks = std::make_unique<Tasks_List>();
    for (int i = 0; i < 10000; i++){
        tasks->add_task("Task");
    }

    EXPECT_EQ(tasks->get_tasks().size(), 10000);

    ASSERT_NE(tasks->get_tasks()[500], nullptr);
    tasks->del_task(500);

    ASSERT_EQ(tasks->get_tasks()[500], nullptr);
    tasks->add_task("New Task");

    ASSERT_NE(tasks->get_tasks()[500], nullptr);
    EXPECT_EQ(tasks->get_tasks()[500]->get_description(), "New Task");    
}

TEST(TasksListTest, LargeTaskNumberDeletion){
    std::unique_ptr<Tasks_List> tasks = std::make_unique<Tasks_List>();
    for (int i = 0; i < 10000; i++){
        tasks->add_task("Task");
    }

    EXPECT_EQ(tasks->get_tasks().size(), 10000);

    for (int i = 0; i < 10000; i++){
        tasks->del_task(i);
    }

    EXPECT_EQ(tasks->empty(), true);
}