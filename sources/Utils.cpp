#include "Utils.hpp"
#include <stdio.h>
int countParams(char **params) {
    int count = 0;
    while (params[count]) {
        count++;
    }
    return count;
}


std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}