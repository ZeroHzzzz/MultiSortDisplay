#ifndef _MACHINE_HPP_
#define _MACHINE_HPP_
#include <map>
#include <string>
#include <vector>

class Machine {
   public:
    std::vector<int> sort_array;  // Use to store the array to be sorted
    std::map<std::string, int> speed = {{"0.5x", 500},
                                        {"1x", 1000},
                                        {"1.5x", 1500},
                                        {"2x", 2000},
                                        {"4x", 4000}};

    void AutoTest();
    void ManualTest();
};

#endif