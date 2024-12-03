#pragma once
#include <string>
#include <vector>

class DayTwo
{

    static bool is_valid(int current_level, int next_level);
    static bool is_valid(int current_level, int next_level, bool increasing);
public:
    static int run_part_one(const char* file_name);
    static int run_part_two(const char* file_name);
};
