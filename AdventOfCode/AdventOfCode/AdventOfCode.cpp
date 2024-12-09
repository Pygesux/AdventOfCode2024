#include <iostream>
#include <gtest/gtest.h>

#include "DayFive.h"
#include "DayFour.h"
#include "DayOne.h"
#include "DaySix.h"
#include "DayThree.h"
#include "DayTwo.h"

int main(int argc, char* argv[])
{
    int test_results = 0;
#ifdef _DEBUG
    ::testing::InitGoogleTest(&argc, argv);
    test_results = RUN_ALL_TESTS();
#endif
    // std::cout << "Day One Part One: " << DayOne::run_part_one("Input.txt") << '\n';
    // std::cout << "Day One Part Two: " << DayOne::run_part_two("Input.txt") << '\n';
    // std::cout << "Day Two Part One: " << DayTwo::run_part_one("Input.txt") << '\n';
    // std::cout << "Day Two Part Two: " << DayTwo::run_part_two("Input.txt") << '\n';
    // std::cout << "Day Three Part One: " << DayThree::run_part_one("Input.txt") << '\n';
    // std::cout << "Day Three Part Two: " << DayThree::run_part_two("Input.txt") << '\n';
    // std::cout << "Day Four Part One: " << DayFour::run_part_one("Input.txt") << '\n';
    // std::cout << "Day Four Part Two: " << DayFour::run_part_two("Input.txt") << '\n';
    // std::cout << "Day Five Part One: " << DayFive::run_part_one("Input.txt") << '\n';
    // std::cout << "Day Five Part Two: " << DayFive::run_part_two("Input.txt") << '\n';
    // std::cout << "Day Six Part One: " << DaySix::run_part_one("Input.txt") << '\n';
    // std::cout << "Day Six Part Two: " << DaySix::run_part_two("Input.txt") << '\n';
    return test_results;
}

TEST(DayOne, PartOne)
{
    EXPECT_EQ(DayOne::run_part_one("Example.txt"), 11);
}

TEST(DayOne, PartTwo)
{
    EXPECT_EQ(DayOne::run_part_two("Example.txt"), 31);
}

TEST(DayTwo, PartOne)
{
    EXPECT_EQ(DayTwo::run_part_one("Example.txt"), 2);
}

TEST(DayTwo, PartTwo)
{
    EXPECT_EQ(DayTwo::run_part_two("Example.txt"), 4);
}

TEST(DayThree, PartOne)
{
    EXPECT_EQ(DayThree::run_part_one("Example.txt"), 161);
}

TEST(DayThree, PartTwo)
{
    EXPECT_EQ(DayThree::run_part_two("Example.txt"), 48);
}

TEST(DayFour, PartOne)
{
    EXPECT_EQ(DayFour::run_part_one("Example.txt"), 18);
}

TEST(DayFour, PartTwo)
{
    EXPECT_EQ(DayFour::run_part_two("Example.txt"), 9);
}

TEST(DayFive, PartOne)
{
    EXPECT_EQ(DayFive::run_part_one("Example.txt"), 143);
}

TEST(DayFive, PartTwo)
{
    EXPECT_EQ(DayFive::run_part_two("Example.txt"), 123);
}

TEST(DaySix, PartOne)
{
    EXPECT_EQ(DaySix::run_part_one("Example.txt"), 41);
}

TEST(DaySix, PartTwo)
{
    EXPECT_EQ(DaySix::run_part_two("Example.txt"), 6);
}
