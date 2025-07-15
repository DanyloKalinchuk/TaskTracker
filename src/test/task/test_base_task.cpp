#include <gtest/gtest.h>
#include "../../task/base_task/base_task.hpp"

struct BaseTaskTest : testing::Test{
    protected:
    std::unique_ptr<Base_Task> bs_task1;
    

    BaseTaskTest(){
        bs_task1 = std::make_unique<Base_Task>(1, "Test_Task");
    }
};

TEST_F(BaseTaskTest, BaseTaskInitialization){
    ASSERT_NE(bs_task1, nullptr);
    EXPECT_EQ(bs_task1->get_id(), 1);
    EXPECT_EQ(bs_task1->get_description(), "Test_Task");
    EXPECT_EQ(bs_task1->get_status(), sts::to_do);
    EXPECT_NE(bs_task1->get_creation_date(), "");
    EXPECT_NE(bs_task1->get_last_update(), "");
    EXPECT_EQ(bs_task1->get_creation_date(), bs_task1->get_last_update());
}

TEST_F(BaseTaskTest, StatusUpdate){
    bs_task1->update_status(sts::in_progress);
    EXPECT_EQ(bs_task1->get_status(), sts::in_progress);

    bs_task1->update_status(sts::done);
    EXPECT_EQ(bs_task1->get_status(), sts::done);

    bs_task1->update_status(sts::to_do);
    EXPECT_EQ(bs_task1->get_status(), sts::to_do);
}

TEST_F(BaseTaskTest, DescriptionUpdate){
    bs_task1->update_description("Updated description");
    EXPECT_EQ(bs_task1->get_description(), "Updated description");
}

TEST(BaseTaskEdgeCases, EmptyDescInitialization){
    std::unique_ptr<Base_Task> bs_task = std::make_unique<Base_Task>(1, "");
    ASSERT_NE(bs_task, nullptr);
    EXPECT_EQ(bs_task->get_description(), "");
}

TEST(BaseTaskEdgeCases, LargeID){
    std::unique_ptr<Base_Task> bs_task = std::make_unique<Base_Task>(9999999, "Test_Task");
    ASSERT_NE(bs_task, nullptr);
    EXPECT_EQ(bs_task->get_id(), 9999999);    
}

TEST(BaseTaskEdgeCases, MaxID){
    std::unique_ptr<Base_Task> bs_task = std::make_unique<Base_Task>(INT_MAX, "Test_Task");
    ASSERT_NE(bs_task, nullptr);
    EXPECT_EQ(bs_task->get_id(), INT_MAX);    
}