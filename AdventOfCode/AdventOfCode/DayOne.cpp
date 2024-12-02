#include "DayOne.h"

#include <fstream>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int DayOne::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DayOne/PartOne/" + std::string(file_name));

    if (!file.is_open()) {
        std::cout << "Unable to open file" << '\n';
        return -1; // Handle error if file cannot be opened
    }
    
    std::vector<int> left_numbers;
    std::vector<int> right_numbers;
    std::regex pattern = std::regex("\\d+");
    std::smatch match = std::smatch();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int left_number, right_number;
        if (iss >> left_number >> right_number)
        {
            left_numbers.push_back(left_number);
            right_numbers.push_back(right_number);
        }
    }
    std::sort(left_numbers.begin(), left_numbers.end());
    std::sort(right_numbers.begin(), right_numbers.end());

    int sum = 0;
    
    for (size_t i = 0; i < left_numbers.size(); ++i)
    {
        sum += std::abs(left_numbers[i] - right_numbers[i]);
    }
    return sum;
}
