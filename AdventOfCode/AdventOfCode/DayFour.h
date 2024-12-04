#pragma once
#include <string>
#include <vector>

class DayFour
{
    static bool search_in_direction(std::vector<std::vector<char>>& input, size_t x, size_t y, int x_direction,
                                    int y_direction, const std::string& target_word, int starting_char);
    static bool is_valid(std::vector<std::vector<char>>& input, size_t x, size_t y, std::string target_characters);

public:
    static int run_part_one(const char* file_name);
    static int run_part_two(const char* file_name);
};
