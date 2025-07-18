#include <gtest/gtest.h>
#include "../../task/main_task/task.hpp"

struct TaskTest : testing::Test{
    protected:
    std::unique_ptr<Task> task1;

    TaskTest(){
        task1 = std::make_unique<Task>(1, "Test_Task");
    }
};

TEST_F(TaskTest, Initialization){
    ASSERT_NE(task1, nullptr);
    EXPECT_EQ(task1->get_sub_tasks().size(), 0);
    EXPECT_EQ(task1->sub_tasks_empty(), true);
}

TEST_F(TaskTest, AddSubTask){
    task1->add_sub_task("Sub-Task");
    EXPECT_EQ(task1->get_sub_tasks().size(), 1);
    EXPECT_EQ(task1->get_sub_tasks()[0]->get_id(), 0);
    EXPECT_EQ(task1->get_sub_tasks()[0]->get_description(), "Sub-Task");
}

TEST_F(TaskTest, DeleteSubTask){
    task1->add_sub_task("Sub-Task");
    task1->del_sub_task(0);
    EXPECT_EQ(task1->sub_tasks_empty(), true);
}

TEST_F(TaskTest, IdMaintenanceSubTask){
    task1->add_sub_task("Sub-Task1");
    task1->add_sub_task("Sub-Task2");
    task1->add_sub_task("Sub-Task3");

    ASSERT_NE(task1->get_sub_tasks()[0], nullptr);
    ASSERT_NE(task1->get_sub_tasks()[2], nullptr);

    task1->del_sub_task(0);
    task1->del_sub_task(2);
    EXPECT_EQ(task1->get_sub_tasks()[0], nullptr);
    EXPECT_EQ(task1->get_sub_tasks()[2], nullptr);

    task1->add_sub_task("Sub-Task4");
    ASSERT_NE(task1->get_sub_tasks()[0], nullptr);
    EXPECT_EQ(task1->get_sub_tasks()[0]->get_description(), "Sub-Task4");

    task1->add_sub_task("Sub-Task5");
    ASSERT_NE(task1->get_sub_tasks()[2], nullptr);
    EXPECT_EQ(task1->get_sub_tasks()[2]->get_description(), "Sub-Task5");
}

TEST_F(TaskTest, LargeSubTaskNumber){
    for (int i = 0; i < 10000; i++){
        task1->add_sub_task("Sub-Task");
    }

    EXPECT_EQ(task1->get_sub_tasks().size(), 10000);

    ASSERT_NE(task1->get_sub_tasks()[500], nullptr);
    task1->del_sub_task(500);

    ASSERT_EQ(task1->get_sub_tasks()[500], nullptr);
    task1->add_sub_task("New Sub-Task");

    ASSERT_NE(task1->get_sub_tasks()[500], nullptr);
    EXPECT_EQ(task1->get_sub_tasks()[500]->get_description(), "New Sub-Task");
}

TEST_F(TaskTest, LargeSubTaskNumberDeletion){
    for (int i = 0; i < 10000; i++){
        task1->add_sub_task("Sub-Task");
    }

    EXPECT_EQ(task1->get_sub_tasks().size(), 10000);

    for (int i = 0; i < 10000; i++){
        task1->del_sub_task(i);
    }

    EXPECT_EQ(task1->sub_tasks_empty(), true);
}