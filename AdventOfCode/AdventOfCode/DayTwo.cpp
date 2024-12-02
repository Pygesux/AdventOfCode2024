#include "DayTwo.h"

#include <fstream>
#include <sstream>
#include <string>

std::vector<std::string> DayTwo::split(const std::string& str, char delimiter)
{
    std::vector<std::string> output;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
    {
        output.push_back(token);
    }
    return output;
}

bool DayTwo::is_valid(const int current_level, const int next_level)
{
    int absolute = std::abs(current_level - next_level);
    return absolute >= 1 && absolute <= 3;
}

bool DayTwo::is_valid(const int current_level, const int next_level, bool increasing)
{
    int absolute = std::abs(current_level - next_level);
    if (absolute < 1 || absolute > 3)
    {
        return false;
    }
    return increasing ? current_level < next_level : current_level > next_level;
}

int DayTwo::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DayTwo/PartOne/" + std::string(file_name));

    if (!file.is_open()) {
        return -1; // Handle error if file cannot be opened
    }

    int count = 0;

    std::string line;

    while (std::getline(file, line))
    {
        auto levels = split(line, ' ');
        bool increasing = true;
        bool valid = true;
        for (size_t i = 0; i < levels.size()-1; i++)
        {
            int current_level = std::stoi(levels[i]);
            int next_level = std::stoi(levels[i + 1]);

            if(i == 0)
            {
                if(!is_valid(current_level, next_level))
                {
                    
                    valid = false;
                    break;
                }
                increasing = current_level < next_level;

            } else
            {
                if(!is_valid(current_level, next_level, increasing))
                {
                    valid = false;
                    break;
                }
            }
            

          
        }
        if(valid)
            count++;
    }
    return count;
}

int DayTwo::run_part_two(const char* file_name)
{
    std::ifstream file("../Data/DayTwo/PartTwo/" + std::string(file_name));

    if (!file.is_open())
    {
        return -1; // Handle error if file cannot be opened
    }

    int count = 0;

    std::string line;

    while (std::getline(file, line))
    {
        auto levels = split(line, ' ');
        bool increasing = true;
        bool increasing_set = false;
        bool valid = true;
        bool has_buffer = true;
        for (size_t i = 0; i < levels.size() - 1; i++)
        {
            int current_level = std::stoi(levels[i]);
            int next_level = std::stoi(levels[i + 1]);

            if (i == 0 || !increasing_set)
            {
                if (!is_valid(current_level, next_level))
                {
                    if (has_buffer)
                    {
                        has_buffer = false;
                        continue;
                    }
                    valid = false;
                    break;
                }
                increasing = current_level < next_level;
                increasing_set = true;
            }
            else
            {
                if (!is_valid(current_level, next_level, increasing))
                {
                    if (!has_buffer)
                    {
                        valid = false;
                        break;
                    }

                    if (i == 1 && (is_valid(current_level, next_level, !increasing) && !increasing == next_level < std::stoi(levels[i + 2])))
                    {
                        // Check if index 0 can be removed
                        increasing = !increasing;
                        has_buffer = false;
                    }

                    if (i + 2 < levels.size())
                        next_level = std::stoi(levels[i + 2]);
                    if (!is_valid(current_level, next_level, increasing))
                    {
                        next_level = std::stoi(levels[i + 1]);
                        current_level = std::stoi(levels[i - 1]);
                        if (i == 1)
                        {
                            if (!is_valid(current_level, next_level, current_level < next_level))
                            {
                                valid = false;
                                break;
                            }
                            increasing = current_level < next_level;
                        }else
                        {
                            if (!is_valid(current_level, next_level, increasing))
                            {
                                valid = false;
                                break;
                            } 
                        }
                        
                    }
                }
            }
        }
        if (valid)
            count++;
    }
    return count;
}