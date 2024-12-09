#pragma once
#include <algorithm>
#include <string>
#include <vector>

class Base3Set {
public:
    Base3Set(unsigned int num) {
        while (num > 0) {
            base3Array.push_back(num % 3);
            num /= 3;
        }
        std::reverse(base3Array.begin(), base3Array.end());
    }

    std::string to_string() const {
        std::string result;
        for (int digit : base3Array) {
            result += std::to_string(digit);
        }
        return result;
    }

    int operator[](size_t index) const {
        if (index >= base3Array.size()) {
            return 0;
        }
        return base3Array[index];
    }

    size_t size() const {
        return base3Array.size();
    }
    
    
    std::vector<int> base3Array;
};
