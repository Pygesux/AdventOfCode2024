#include "DayEight.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

int DayEight::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DayEight/" + std::string(file_name));
    if (!file.is_open())
    {
        return -1;
    }

    std::unordered_map<char, std::vector<std::tuple<int,int>>> antennas = std::unordered_map<char, std::vector<std::tuple<int,int>>>();
    std::string line;
    int x = 0;
    int y = 0;
    while (std::getline(file, line))
    {
        x = 0;
        for (auto c : line)
        {
            if (c == '.')
            {
                x += 1;
                continue;
            }
            
            if (antennas.find(c) == antennas.end())
            {
                antennas[c] = std::vector<std::tuple<int, int>>();
            }
            antennas[c].emplace_back(x, y);
            x += 1;
        }
        y += 1;
    }

    std::vector<std::tuple<int,int>> anti_nodes = std::vector<std::tuple<int,int>>();
    for (auto antenna : antennas)
    {
        size_t size = antenna.second.size();
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (i == j) continue;
                int ax1 = std::get<0>(antenna.second[i]);
                int ay1 = std::get<1>(antenna.second[i]);
                int ax2 = std::get<0>(antenna.second[j]);
                int ay2 = std::get<1>(antenna.second[j]);
                int dx = ax2 - ax1;
                int dy = ay2 - ay1;
                int anx = ax2 + dx;
                int any = ay2 + dy;
                if(anx >= 0 && anx < x && any >= 0 && any < y)
                {
                    if (std::find(anti_nodes.begin(), anti_nodes.end(), std::make_tuple(anx, any)) == anti_nodes.end())
                    {
                        anti_nodes.emplace_back(anx, any);
                    }
                }
                
            }
        }
    }
    //Return the distinct number of anti-nodes
    return static_cast<int>(std::set<std::tuple<int,int>>(anti_nodes.begin(), anti_nodes.end()).size());
}

int DayEight::run_part_two(const char* file_name)
{
    std::ifstream file("../Data/DayEight/" + std::string(file_name));
    if (!file.is_open())
    {
        return -1;
    }

    std::unordered_map<char, std::vector<std::tuple<int,int>>> antennas = std::unordered_map<char, std::vector<std::tuple<int,int>>>();
    std::string line;
    int x = 0;
    int y = 0;
    std::vector<std::tuple<int,int>> anti_nodes = std::vector<std::tuple<int,int>>();
    while (std::getline(file, line))
    {
        x = 0;
        for (auto c : line)
        {
            if (c == '.')
            {
                x += 1;
                continue;
            }
            
            if (antennas.find(c) == antennas.end())
            {
                antennas[c] = std::vector<std::tuple<int, int>>();
            }
            antennas[c].emplace_back(x, y);
            anti_nodes.emplace_back(x, y);
            x += 1;
        }
        y += 1;
    }

    for (auto antenna : antennas)
    {
        size_t size = antenna.second.size();
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (i == j) continue;
                int ax1 = std::get<0>(antenna.second[i]);
                int ay1 = std::get<1>(antenna.second[i]);
                int ax2 = std::get<0>(antenna.second[j]);
                int ay2 = std::get<1>(antenna.second[j]);
                int dx = ax2 - ax1;
                int dy = ay2 - ay1;
                int anx = ax2 + dx;
                int any = ay2 + dy;
                while (anx >= 0 && anx < x && any >= 0 && any < y)
                {
                    if (std::find(anti_nodes.begin(), anti_nodes.end(), std::make_tuple(anx, any)) == anti_nodes.end())
                    {
                        anti_nodes.emplace_back(anx, any);
                    }
                    anx += dx;
                    any += dy;
                }
                
            }
        }
    }

    //Return the distinct number of anti-nodes
    return static_cast<int>(std::set<std::tuple<int,int>>(anti_nodes.begin(), anti_nodes.end()).size());
}