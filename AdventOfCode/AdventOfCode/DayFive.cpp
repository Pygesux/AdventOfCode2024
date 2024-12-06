#include "DayFive.h"

#include <fstream>
#include <string>
#include <tuple>
#include <valarray>
#include <vector>

#include "Helper.h"


int DayFive::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DayFive/" + std::string(file_name));

    if (!file.is_open())
    {
        return -1;
    }

    std::vector<std::tuple<int, int>> rules = std::vector<std::tuple<int, int>>();

    std::vector<std::vector<int>> updates = std::vector<std::vector<int>>();

    std::string line;
    bool rules_done = false;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            rules_done = true;
            continue;
        }
        if (!rules_done)
        {
            auto rule = Helper::split(line, '|');
            rules.emplace_back(std::stoi(rule[0]), std::stoi(rule[1]));
        }
        else
        {
            updates.emplace_back();
            auto update = Helper::split(line, ',');
            for (const auto& u : update)
            {
                updates.back().push_back(std::stoi(u));
            }
        }
    }
    int sum = 0;
    for (auto update : updates)
    {
        //Find applicable rules
        size_t count = update.size();
        for (size_t i = 0; i < count; i++)
        {
            int value = update[i];
            for (auto rule : rules)
            {
                if (value == std::get<1>(rule))
                {
                    for (size_t j = i; j < count; ++j)
                    {
                        if(std::get<0>(rule) == update[j])
                        {
                            goto invalid;
                        }
                    }
                }
            }
        }
        sum += update[static_cast<int>(static_cast<float>(count)/2.0f)];
        invalid:
        continue;
    }
    return sum;
}

int DayFive::run_part_two(const char* file_name)
{
    std::ifstream file("../Data/DayFive/" + std::string(file_name));

    if (!file.is_open())
    {
        return -1;
    }

    std::vector<std::tuple<int, int>> rules = std::vector<std::tuple<int, int>>();

    std::vector<std::vector<int>> updates = std::vector<std::vector<int>>();

    std::string line;
    bool rules_done = false;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            rules_done = true;
            continue;
        }
        if (!rules_done)
        {
            auto rule = Helper::split(line, '|');
            rules.emplace_back(std::stoi(rule[0]), std::stoi(rule[1]));
        }
        else
        {
            updates.emplace_back();
            auto update = Helper::split(line, ',');
            for (const auto& u : update)
            {
                updates.back().push_back(std::stoi(u));
            }
        }
    }
    int sum = 0;
    for (auto update : updates)
    {
        std::vector<int> result = std::vector<int>();
        //Find applicable rules
        size_t count = update.size();
        for (long long i = count - 1; i >= 0; --i)
        {
            int value = update[i];
            int index = 0;
            for (auto rule : rules)
            {
                for (auto j = 0; j < result.size(); ++j)
                {
                    // If 
                    
                    if (result[j] == std::get<0>(rule) && value == std::get<1>(rule))
                    {
                        index = std::max(index, j + 1);
                    }
                }
            }
            result.insert(result.begin() + index, value);
        }
        if(update != result)
            sum += result[static_cast<int>(static_cast<float>(count)/2.0f)];
    }
    return sum;
}