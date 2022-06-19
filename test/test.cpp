#include <cstdlib>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Pipeline.h"

TEST(pipeline, workflow) 
{
    // Arrange

    // Act

    // Assert
    ASSERT_EQ(true, true);
}

int main(int ac, char* av[])
{
        testing::InitGoogleTest(&ac, av);
        return RUN_ALL_TESTS();
} 
