#include "DayFour.h"

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

bool DayFour::search_in_direction(std::vector<std::vector<char>>& input, size_t x, size_t y, int x_direction,
                                  int y_direction,
                                  const std::string& target_word, int starting_char)
{
    int target_index = starting_char;
    x += x_direction;
    y += y_direction;
    while (x >= 0 && x < input.size() && y >= 0 && y < input[x].size())
    {
        if (input[y][x] != target_word[target_index])
        {
            return false;
        }
        x += x_direction;
        y += y_direction;
        target_index++;
        if (target_index == static_cast<int>(target_word.size()))
        {
            return true;
        }
    }
    return false;
}

bool DayFour::is_valid(std::vector<std::vector<char>>& input, size_t x, size_t y,
                       std::string target_characters)
{
    if (x > 0 && y > 0 && x < input.size() - 1 && y < input[y].size() - 1)
    {
        int found_one = -1;
        int found_two = -1;
        for (int i = 0; i < static_cast<int>(target_characters.size()); i++)
        {
            if (found_one == -1 && input[y - 1][x - 1] == target_characters[i])
            {
                found_one = i;
            }
            if (found_two == -1 && input[y - 1][x + 1] == target_characters[i])
            {
                found_two = i;
            }
        }
        if (found_one == -1 || found_two == -1)
        {
            return false;
        }
        bool search_one = true;
        bool search_two = true;
        for (int i = 0; i < static_cast<int>(target_characters.size()); i++)
        {
            if (search_one && i != found_one && input[y + 1][x + 1] == target_characters[i])
            {
                search_one = false;
            }
            if (search_two && i != found_two && input[y + 1][x - 1] == target_characters[i])
            {
                search_two = false;
            }
        }
        return !search_one && !search_two;
    }
    return false;
}

int DayFour::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DayFour/" + std::string(file_name));
    std::string target_word = "XMAS";

    if (!file.is_open())
    {
        return -1;
    }

    std::vector<std::vector<char>> input = std::vector<std::vector<char>>();

    std::vector<std::tuple<uint16_t, uint16_t>> starting_characters = std::vector<std::tuple<uint16_t, uint16_t>>();


    std::string line;
    int x = 0;
    int y = 0;

    while (std::getline(file, line))
    {
        input.emplace_back();
        x = 0;
        for (char c : line)
        {
            input[y].push_back(c);
            if (c == target_word[0])
            {
                starting_characters.emplace_back(x, y);
            }
            x++;
        }
        y++;
    }

    std::vector<std::tuple<int8_t, int8_t>> directions;
    // Up, Down, Left, Right, Up-Left, Up-Right, Down-Left, Down-Right
    directions.emplace_back(0, -1);
    directions.emplace_back(0, 1);
    directions.emplace_back(-1, 0);
    directions.emplace_back(1, 0);
    directions.emplace_back(-1, -1);
    directions.emplace_back(-1, 1);
    directions.emplace_back(1, -1);
    directions.emplace_back(1, 1);

    int count = 0;
    for (auto starting_character : starting_characters)
    {
        for (auto direction : directions)
        {
            if (search_in_direction(input, std::get<0>(starting_character), std::get<1>(starting_character),
                                    std::get<0>(direction), std::get<1>(direction), target_word, 1))
            {
                count++;
            }
        }
    }
    return count;
}

int DayFour::run_part_two(const char* file_name)
{
    std::ifstream file("../Data/DayFour/" + std::string(file_name));
    std::string target_characters = "MS";

    if (!file.is_open())
    {
        return -1;
    }

    std::vector<std::vector<char>> input = std::vector<std::vector<char>>();
    std::vector<std::tuple<size_t, size_t>> starting_characters = std::vector<std::tuple<size_t, size_t>>();

    std::string line;
    size_t x = 0;
    size_t y = 0;
    while (std::getline(file, line))
    {
        input.emplace_back();
        x = 0;
        for (char c : line)
        {
            input[y].push_back(c);
            if (c == 'A')
            {
                starting_characters.emplace_back(x, y);
            }
            x++;
        }
        y++;
    }

    int count = 0;
    for (auto word : starting_characters)
    {
        x = std::get<0>(word);
        y = std::get<1>(word);
         if (is_valid(input, x, y, target_characters))
        {
            count++;
        }
    }
    return count;
}
