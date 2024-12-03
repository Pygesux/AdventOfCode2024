#include "DayThree.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "Helper.h"

int DayThree::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DayThree/" + std::string(file_name));

    if (!file.is_open()) {
        return -1; // Handle error if file cannot be opened
    }

    std::regex pattern = std::regex("mul\\(\\d{1,3},\\d{1,3}\\)");
    std::smatch match = std::smatch();
    
    std::stringstream ss;
    ss << file.rdbuf();
    std::string input = ss.str();

    int sum = 0;
    while (std::regex_search(input, match, pattern))
    {
        auto values = Helper::split(match.str(), ',');
        int a = std::stoi(values[0].substr(4));
        values[1].pop_back();
        int b = std::stoi(values[1]);
        sum += a * b;
        input = match.suffix().str();
    }
    return sum;
}

int DayThree::run_part_two(const char* file_name)
{
    std::ifstream file("../Data/DayThree/" + std::string(file_name));

    if (!file.is_open()) {
        return -1; // Handle error if file cannot be opened
    }

    std::regex pattern = std::regex("((mul\\(\\d{1,3},\\d{1,3}\\))|(do\\(\\)|don't\\(\\))){1}");
    std::smatch match;

    std::stringstream ss;
    ss << file.rdbuf();
    std::string input = ss.str();

    int sum = 0;
    bool do_not = false;
    while (std::regex_search(input, match, pattern))
    {
        auto str = match.str();

        input = match.suffix().str();

        if (str[0] == 'd') {
            // Handle "do()" or "don't()"
            do_not = str == "don't()";
            continue;
        }

        if (do_not) {
            continue;
        }

        // Handle "mul(xxx,yyy)"
        auto values = Helper::split(str, ',');
        int a = std::stoi(values[0].substr(4));
        values[1].pop_back();
        int b = std::stoi(values[1]);
        sum += a * b;
    }
    return sum;
}