#include "DaySix.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <mutex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

namespace std
{
    class thread;
}

DaySix::EResult DaySix::move_part_one(std::tuple<int, int>& position, const std::tuple<int, int>& direction,
                                      const std::vector<std::tuple<int, int>>& obstacles,
                                      std::vector<std::tuple<int, int>>& visited, std::tuple<int, int> size)
{
    int x = std::get<0>(position);
    int y = std::get<1>(position);
    int new_x = x + std::get<0>(direction);
    int new_y = y + std::get<1>(direction);

    if (std::find(obstacles.begin(), obstacles.end(), std::make_tuple(new_x, new_y)) != obstacles.end())
    {
        return EResult::HitObstacle;
    }
    if (new_x < 0 || new_x >= std::get<0>(size) || new_y < 0 || new_y >= std::get<1>(size))
    {
        return EResult::Done;
    }

    position = std::make_tuple(new_x, new_y);
    visited.emplace_back(new_x, new_y);
    return EResult::Moved;
}

DaySix::EResult DaySix::move_part_two(std::tuple<int, int>& position, const std::tuple<int, int>& direction,
                                      const std::vector<std::tuple<int, int>>& obstacles,
                                      std::vector<std::tuple<int, int, int, int>>& visited, std::tuple<int, int> size)
{
    int x = std::get<0>(position);
    int y = std::get<1>(position);
    int new_x = x + std::get<0>(direction);
    int new_y = y + std::get<1>(direction);

    if (std::find(obstacles.begin(), obstacles.end(), std::make_tuple(new_x, new_y)) != obstacles.end())
    {
        return EResult::HitObstacle;
    }
    if (new_x < 0 || new_x >= std::get<0>(size) || new_y < 0 || new_y >= std::get<1>(size))
    {
        return EResult::Done;
    }

    position = std::make_tuple(new_x, new_y);
    visited.emplace_back(new_x, new_y, std::get<0>(direction), std::get<1>(direction));
    return EResult::Moved;
}

int DaySix::run_part_one(const char* file_name)
{
    std::ifstream file("../Data/DaySix/" + std::string(file_name));

    if (!file.is_open())
    {
        return -1;
    }

    std::string line;
    std::vector<std::tuple<int, int>> obstacles = std::vector<std::tuple<int, int>>();
    int x = 0;
    int y = 0;
    std::tuple<int, int> position = std::make_tuple(0, 0);
    std::tuple<int, int> direction = std::make_tuple(0, -1); // Up
    std::tuple<int, int> size;
    while (std::getline(file, line))
    {
        x = 0;
        for (auto c : line)
        {
            if (c == '#') // Is obstacle
                obstacles.emplace_back(x, y);
            if (c == '^')
                position = std::make_tuple(x, y);
            x += 1;
        }
        y += 1;
    }
    size = std::make_tuple(x, y);

    bool done = false;
    std::vector<std::tuple<int, int>> visited = std::vector<std::tuple<int, int>>();
    while (!done)
    {
        switch (move_part_one(position, direction, obstacles, visited, size))
        {
        case Moved:
            // Do nothing
            break;
        case HitObstacle:
            // Turn right
            if (std::get<0>(direction) == 0)
            {
                direction = std::get<1>(direction) == -1 ? std::make_tuple(1, 0) : std::make_tuple(-1, 0);
            }
            else
            {
                direction = std::get<0>(direction) == -1 ? std::make_tuple(0, -1) : std::make_tuple(0, 1);
            }
            break;
        case Done:
            done = true;
            break;
        }
    }
    return static_cast<int>(std::set<std::tuple<int, int>>(visited.begin(), visited.end()).size());
}


// int DaySix::run_part_two(const char* file_name)
// {
//     std::ifstream file("../Data/DaySix/" + std::string(file_name));
//
//     if (!file.is_open())
//     {
//         return -1;
//     }
//
//     std::string line;
//     std::vector<std::tuple<int, int>> obstacles = std::vector<std::tuple<int, int>>();
//     int x = 0;
//     int y = 0;
//     std::tuple<int, int> position = std::make_tuple(0, 0);
//     std::tuple<int, int> direction = std::make_tuple(0, -1); // Up
//     std::tuple<int, int> size;
//     while (std::getline(file, line))
//     {
//         x = 0;
//         for (auto c : line)
//         {
//             if (c == '#') // Is obstacle
//                 obstacles.emplace_back(x, y);
//             if (c == '^')
//                 position = std::make_tuple(x, y);
//             x += 1;
//         }
//         y += 1;
//     }
//     size = std::make_tuple(x, y);
//
//     bool done = false;
//     std::vector<std::tuple<int, int>> visited = std::vector<std::tuple<int, int>>();
//     std::vector<std::tuple<int, int, int, int>> path = std::vector<std::tuple<int, int, int, int>>();
//     while (!done)
//     {
//         switch (move(position, direction, obstacles, visited, size))
//         {
//         case Moved:
//             // Do nothing
//             break;
//         case HitObstacle:
//             // Turn right
//             if (std::get<0>(direction) == 0)
//             {
//                 direction = std::get<1>(direction) == -1 ? std::make_tuple(1, 0) : std::make_tuple(-1, 0);
//             }
//             else
//             {
//                 direction = std::get<0>(direction) == -1 ? std::make_tuple(0, -1) : std::make_tuple(0, 1);
//             }
//             path.emplace_back(std::get<0>(position), std::get<1>(position), std::get<0>(direction),
//                               std::get<1>(direction));
//
//             break;
//         case Done:
//             done = true;
//             break;
//         }
//     }
//
//     int count = 0;
//     std::vector<std::tuple<int, int>> new_obstacles = std::vector<std::tuple<int, int>>();
//     // Find all points where a square can be created by creating a new obstacle
//     for (size_t i = 0; i < path.size() - 2; i++)
//     {
//         std::tuple<int, int> point_one = std::make_tuple(std::get<0>(path[i]), std::get<1>(path[i]));
//         for (size_t j = i + 2; j < path.size(); j += 4)
//         {
//             std::tuple<int, int> point_three = std::make_tuple(std::get<0>(path[j]), std::get<1>(path[j]));
//             std::tuple<int, int> dir = std::make_tuple(std::get<2>(path[j]), std::get<3>(path[j]));
//             std::tuple<int, int> desired_direction;
//             std::tuple<int, int> intersection;
//             std::tuple<int, int> new_obstacle;
//
//             //Cases
//             /*
//              * Up = (0, -1) becomes Right = (1, 0) and intersection = (x, y)
//              * Right = (1, 0) becomes Down = (0, 1) and intersection = (x, y)
//              * Down = (0, 1) becomes Left = (-1, 0) and intersection = (x, y)
//              * Left = (-1, 0) becomes Up = (0, -1) and intersection = (x, y)
//              * 
//              */
//             // Desired direction is turn left from direction
//             if (std::get<0>(dir) == 0)
//             {
//                 desired_direction = std::get<1>(dir) == -1 ? std::make_tuple(1, 0) : std::make_tuple(-1, 0);
//                 intersection = std::make_tuple(std::get<0>(point_three), std::get<1>(point_one));
//             }
//             else
//             {
//                 desired_direction = std::get<0>(dir) == -1 ? std::make_tuple(0, -1) : std::make_tuple(0, 1);
//                 intersection = std::make_tuple(std::get<0>(point_one), std::get<1>(point_three));
//             }
//             new_obstacle = std::make_tuple(std::get<0>(intersection) + std::get<0>(dir),
//                                            std::get<1>(intersection) + std::get<1>(dir));
//             dir = std::make_tuple(std::get<0>(dir) * -1, std::get<1>(dir) * -1);
//
//             if (std::find(new_obstacles.begin(), new_obstacles.end(), new_obstacle) != new_obstacles.end())
//             {
//                 continue;
//             }
//                 // Check if the obstacle is not already in the list of obstacles and if it's not outside the bounds of the grid
//             // and detect if there is no obstacle between intersection and point_one and point_three
//             if (std::find(obstacles.begin(), obstacles.end(), new_obstacle) == obstacles.end() &&
//                 std::get<0>(new_obstacle) >= 0 && std::get<0>(new_obstacle) < std::get<0>(size) &&
//                 std::get<1>(new_obstacle) >= 0 && std::get<1>(new_obstacle) < std::get<1>(size))
//             {
//                 
//                 
//                 bool found = valid_obstacle(obstacles, dir, desired_direction, intersection, new_obstacle, point_one,
//                                             point_three);
//
//                 if (!found)
//                 {
//                     new_obstacles.emplace_back(new_obstacle);
//                     std::cout << "New obstacle at: " << std::get<0>(new_obstacle) << ", " << std::get<1>(new_obstacle)
//                         << '\n';
//                     count++;
//                 }
//             }
//         }
//     }
//     return count;
// }
//
// bool DaySix::valid_obstacle(const std::vector<std::tuple<int, int>>& obstacles, const std::tuple<int, int>& dir,
//                             const std::tuple<int, int>& desired_direction, const std::tuple<int, int>& intersection,
//                             const std::tuple<int, int>& new_obstacle, const std::tuple<int, int>& point_one,
//                             const std::tuple<int, int>& point_three)
// {
//     bool found = false;
//     for (auto& obstacle : obstacles)
//     {
//         if (std::get<0>(desired_direction) == 0) // Going vertical
//         {
//             if (std::get<0>(obstacle) == std::get<0>(intersection))
//             {
//                 if (std::get<1>(desired_direction) == 1) // Going down
//                 {
//                     if (std::get<1>(obstacle) > std::get<1>(intersection) &&
//                         std::get<1>(obstacle) < std::get<1>(point_one))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//                 else
//                 {
//                     if (std::get<1>(obstacle) < std::get<1>(intersection) &&
//                         std::get<1>(obstacle) > std::get<1>(point_one))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//             }
//         }
//         else
//         {
//             if (std::get<1>(obstacle) == std::get<1>(intersection))
//             {
//                 if (std::get<0>(desired_direction) == 1) // Going right
//                 {
//                     if (std::get<0>(obstacle) > std::get<0>(intersection) &&
//                         std::get<0>(obstacle) < std::get<0>(point_one))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//                 else
//                 {
//                     if (std::get<0>(obstacle) < std::get<0>(intersection) &&
//                         std::get<0>(obstacle) > std::get<0>(point_one))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//             }
//         }
//         if (std::get<0>(dir) == 0) //Going vertical
//         {
//             if (std::get<0>(obstacle) == std::get<0>(new_obstacle))
//             {
//                 if (std::get<1>(dir) == 1) // Going down
//                 {
//                     if (std::get<1>(obstacle) > std::get<1>(new_obstacle) && std::get<1>(obstacle) <
//                         std::get<1>(point_three))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//                 else // Going up
//                 {
//                     if (std::get<1>(obstacle) < std::get<1>(new_obstacle) && std::get<1>(obstacle) >
//                         std::get<1>(point_three))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//             }
//         }
//         else
//         {
//             if (std::get<1>(obstacle) == std::get<1>(new_obstacle))
//             {
//                 if (std::get<0>(dir) == 1) // Going right
//                 {
//                     if (std::get<0>(obstacle) > std::get<0>(new_obstacle) && std::get<0>(obstacle) <
//                         std::get<0>(point_three))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//                 else // Going left
//                 {
//                     if (std::get<0>(obstacle) < std::get<0>(new_obstacle) && std::get<0>(obstacle) >
//                         std::get<0>(point_three))
//                     {
//                         found = true;
//                         break;
//                     }
//                 }
//             }
//         }
//         if (found)
//         {
//             break;
//         }
//     }
//     return found;
// }

#include <thread>

int DaySix::run_part_two(const char* file_name)
{
    std::ifstream file("../Data/DaySix/" + std::string(file_name));

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << file_name << '\n';
        return -1;
    }

    std::string line;
    std::vector<std::tuple<int, int>> obstacles;
    int x = 0;
    int y = 0;
    std::tuple<int, int> position = std::make_tuple(0, 0);
    std::tuple<int, int> direction = std::make_tuple(0, -1); // Up
    std::tuple<int, int> size;
    while (std::getline(file, line))
    {
        x = 0;
        for (auto c : line)
        {
            if (c == '#') // Is obstacle
                obstacles.emplace_back(x, y);
            if (c == '^')
                position = std::make_tuple(x, y);
            x += 1;
        }
        y += 1;
    }
    size = std::make_tuple(x, y);

    bool done = false;
    std::vector<std::tuple<int, int, int, int>> visited;
    std::vector<std::tuple<int, int, int, int>> path;
    std::set<std::tuple<int, int>> new_obstacles_set;
    std::tuple<int, int> start_position = position;
    std::tuple<int, int> start_direction = direction;
    while (!done)
    {
        switch (move_part_two(position, direction, obstacles, visited, size))
        {
        case Moved:
            if (std::get<0>(start_position) == std::get<0>(position) && std::get<1>(start_position) == std::get<
                1>(position))
            {
                break;
            }
            new_obstacles_set.emplace(std::get<0>(position), std::get<1>(position));
            break;
        case HitObstacle:
            if (std::get<0>(direction) == 0)
            {
                direction = std::get<1>(direction) == -1 ? std::make_tuple(1, 0) : std::make_tuple(-1, 0);
            }
            else
            {
                direction = std::get<0>(direction) == -1 ? std::make_tuple(0, -1) : std::make_tuple(0, 1);
            }
            path.emplace_back(std::get<0>(position), std::get<1>(position), std::get<0>(direction),
                              std::get<1>(direction));
            break;
        case Done:
            done = true;
            break;
        }
    }

    std::vector<std::tuple<int, int>> new_obstacles(new_obstacles_set.begin(), new_obstacles_set.end());

    std::vector<std::tuple<bool, int, int>> results(new_obstacles.size());
    std::mutex mtx;

    auto process = [&](size_t i)
    {
        auto result = process_obstacle(start_position, start_direction, new_obstacles[i], size, obstacles);
        std::lock_guard<std::mutex> lock(mtx);
        results[i] = result;
        // std::cout << "Processed obstacle: " << i << " out of " << new_obstacles.size() << '\n';
    };


    std::vector<std::thread> threads;
    for (size_t i = 0; i < new_obstacles.size(); ++i)
    {
        threads.emplace_back(process, i);
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
    // for (auto obstacle : new_obstacles)
    // {
    //     results.emplace_back(process_obstacle(start_position, start_direction, obstacle, size, obstacles));
    //     std::cout << "Processed obstacle: " << std::get<0>(obstacle) << ", " << std::get<1>(obstacle) << '\n';
    // }

    int count = 0;
    for (const auto& result : results)
    {
        if (std::get<0>(result))
        {
            count++;
        }
    }

    return count;
}

std::tuple<bool, int, int> DaySix::process_obstacle(std::tuple<int, int> start_position,
                                                    std::tuple<int, int> start_direction,
                                                    std::tuple<int, int> new_obstacle, std::tuple<int, int> size,
                                                    std::vector<std::tuple<int, int>> obstacles)
{
    auto position = std::make_tuple(std::get<0>(start_position), std::get<1>(start_position));
    auto direction = std::make_tuple(std::get<0>(start_direction), std::get<1>(start_direction));
    auto visited = std::vector<std::tuple<int, int, int, int>>();
    int x = std::get<0>(new_obstacle);
    int y = std::get<1>(new_obstacle);
    // std::cout << "Processing obstacle at: " << x << ", " << y << '\n';

    std::vector<std::tuple<int, int, int, int>> states = std::vector<std::tuple<int, int, int, int>>();
    obstacles.emplace_back(x, y);
    while (true)
    {
        auto before = visited;
        switch (move_part_two(position, direction, obstacles, visited, size))
        {
        case Moved:

            // Do nothing
            // if(std::find(before.begin(), before.end(), std::make_tuple(std::get<0>(position), std::get<1>(position), std::get<0>(direction), std::get<1>(direction))) != before.end())
            // {
            // return true;
            // }
            // if(log)
            // std::cout << "Moved to: " << std::get<0>(position) << ", " << std::get<1>(position) << '\n';
            break;
        case HitObstacle:
            // if(log)
            // {
            // std::cout << "Hit obstacle at: " << std::get<0>(position) << ", " << std::get<1>(position) << '\n';
            // }
            // Turn right
            if (std::get<0>(direction) == 0)
            {
                direction = std::get<1>(direction) == -1 ? std::make_tuple(1, 0) : std::make_tuple(-1, 0);
            }
            else
            {
                direction = std::get<0>(direction) == -1 ? std::make_tuple(0, -1) : std::make_tuple(0, 1);
            }
            if (std::find(states.begin(), states.end(),
                          std::make_tuple(std::get<0>(position), std::get<1>(position), std::get<0>(direction),
                                          std::get<1>(direction))) != states.end())
            {
                // std::cout << "Found loop at: " << std::get<0>(position) << ", " << std::get<1>(position) << '\n';
                return std::make_tuple(true, std::get<0>(position), std::get<1>(position));
            }
            states.emplace_back(std::get<0>(position), std::get<1>(position), std::get<0>(direction),
                                std::get<1>(direction));
        // if(count > path_size * 2) {
        // return true;
        // }
        // count++;
            break;
        case Done:
            return std::make_tuple(false, 0, 0);
            break;
        }
    }
    return std::make_tuple(false, 0, 0);
}
