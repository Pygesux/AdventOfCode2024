
#include <iostream>
#include <gtest/gtest.h>

#include "DayOne.h"

int main(int argc, char* argv[])
{
    std::cout << "Day One Part One: " << DayOne::run_part_one("Input.txt") << '\n';
    std::cout << "Day One Part Two: " << DayOne::run_part_two("Input.txt") << '\n';
#ifdef _DEBUG
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    return 0;
#endif
}

TEST(DayOne, PartOne)
{
    EXPECT_EQ(DayOne::run_part_one("Example.txt"), 11);
}

TEST(DayOne, PartTwo)
{
    EXPECT_EQ(DayOne::run_part_two("Example.txt"), 31);
}

