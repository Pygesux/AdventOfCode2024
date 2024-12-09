#include "DaySeven.h"

#include <bitset>
#include <complex>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "Base3Set.h"
#include "Helper.h"

#include <cmath>
#include <unordered_map>

size_t DaySeven::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DaySeven/" + std::string(file_name));
    if (!file.is_open())
    {
        return -1;
    }

    std::vector<std::tuple<size_t, std::vector<int>>> operations = std::vector<std::tuple<size_t, std::vector<int>>>();
    std::string line;

    while (std::getline(file, line))
    {
        try
        {
            auto tmp = Helper::split(line, ' ');
            size_t result = std::stoull(tmp[0].substr(0, tmp[0].size() - 1));
            std::vector<int> operation = std::vector<int>();
            for (size_t i = 1; i < tmp.size(); i++)
            {
                operation.emplace_back(std::stoi(tmp[i]));
            }
            operations.emplace_back(result, operation);
        }
        catch (const std::exception&)
        {
            std::cout << "Failed to parse line: " << line << '\n';
        }
    }

    size_t sum = 0;
    for (auto operation : operations)
    {
        size_t result = std::get<0>(operation);
        std::vector<int> values = std::get<1>(operation);

        for (unsigned int i = 0; i < std::pow(2, std::get<1>(operation).size()); i++)
        {
            size_t current = values[0];
            std::bitset<32> bits(i);
            for (size_t j = 1; j < values.size(); j++)
            {
                if (bits[j] == 1)
                {
                    current += values[j];
                }
                else
                {
                    current *= values[j];
                }
            }
            if (current == result)
            {
                sum += result;
                break;
            }
        }
    }
    return sum;
}



size_t DaySeven::run_part_two(const char* file_name)
{
    std::ifstream file("../Data/DaySeven/" + std::string(file_name));
    if (!file.is_open())
    {
        return -1;
    }

    std::vector<std::tuple<size_t, std::vector<int>>> operations;
    std::string line;

    while (std::getline(file, line))
    {
        try
        {
            auto tmp = Helper::split(line, ' ');
            size_t result = std::stoull(tmp[0].substr(0, tmp[0].size() - 1));
            std::vector<int> operation;
            for (size_t i = 1; i < tmp.size(); i++)
            {
                operation.emplace_back(std::stoi(tmp[i]));
            }
            operations.emplace_back(result, operation);
        }
        catch (const std::exception&)
        {
            std::cout << "Failed to parse line: " << line << '\n';
        }
    }

    size_t sum = 0;
    std::unordered_map<size_t, size_t> power_of_3;
    for (size_t i = 0; i < 20; ++i) // Precompute powers of 3 up to a reasonable limit
    {
        power_of_3[i] = static_cast<size_t>(std::pow(3, i));
    }

    int index = 0;
    for (const auto& operation : operations)
    {
        std::cout << "Processing operation: " << index << " out of " << operations.size() << '\n';
        index++;
        size_t result = std::get<0>(operation);
        const std::vector<int>& values = std::get<1>(operation);

        size_t num_combinations = power_of_3[values.size()];
        for (size_t i = 0; i < num_combinations; i++)
        {
            size_t current = values[0];
            Base3Set b(i);
            for (size_t j = 1; j < values.size(); j++)
            {
                if (b[j] == 1)
                {
                    current += values[j];
                }
                else if (b[j] == 2)
                {
                    current = std::stoull(std::to_string(current) + std::to_string(values[j]));
                }
                else
                {
                    current *= values[j];
                }
            }
            if (current == result)
            {
                sum += result;
                break;
            }
        }
    }
    return sum;
}
