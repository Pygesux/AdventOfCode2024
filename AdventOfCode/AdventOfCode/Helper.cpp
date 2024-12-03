#include "Helper.h"

#include <sstream>

std::vector<std::string> Helper::split(const std::string& str, char delimiter)
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
