#pragma once
#include <tuple>
#include <vector>

class DaySix
{
    enum EResult
    {
        Moved,
        HitObstacle,
        Done
    };

    static EResult move_part_one(std::tuple<int, int>& position, const std::tuple<int, int>& direction,
                                 const std::vector<std::tuple<int, int>>& obstacles,
                                 std::vector<std::tuple<int, int>>& visited, std::tuple<int, int>
                                 size);
    static EResult move_part_two(::std::tuple<int, int>& position, const ::std::tuple<int, int>& direction,
                                 const std::vector<std::tuple<int, int>>& obstacles,
                                 std::vector<std::tuple<int, int, int, int>>& visited, std::tuple<int, int> size);

public:
    static int run_part_one(const char* file_name);
    static std::tuple<bool, int, int> process_obstacle(std::tuple<int, int> start_position,
                                                       std::tuple<int, int> start_direction,
                                                       std::tuple<int, int> new_obstacle, std::tuple<int, int> size,
                                                       std::vector<std::tuple<int, int>> obstacles);
    static int run_part_two(const char* file_name);
};
