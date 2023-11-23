
#include <gtest/gtest.h>
#include "LogComponent/ILogComponent.hpp"
#include "LogComponent/LogComponent.hpp"
#include <memory>

class LogComponentTest : public ::testing::Test {
protected:
    void SetUp() override{
        mILogComponent = std::make_unique<Components::LogComponent>();
    }
    std::unique_ptr<Components::ILogComponent> mILogComponent;
};


TEST_F(LogComponentTest, auto) {
    mILogComponent->init("/tmp");
    // log name core had been created in the process of initialization
    EXPECT_FALSE(mILogComponent->createLogName("Core"));
    // create an newer log name
    EXPECT_TRUE(mILogComponent->createLogName("test"));
    mILogComponent->info("Hello Core", "Core");
    mILogComponent->info("Hello test", "test");


}
