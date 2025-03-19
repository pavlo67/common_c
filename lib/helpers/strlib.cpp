#include <unistd.h>

#include "strlib.h"

std::vector<std::string> split(std::string s, const std::string& delimiter) {
    std::vector<std::string> res;
    while (!s.empty()){
        size_t pos = s.find(delimiter);
        // printf("%lu / %s\n", pos, s.c_str());
        if (pos >= s.length()) {
            res.push_back(s);
            break;
        }

        res.push_back(s.substr(0,pos));
        s = s.substr(pos+1);
    }
    return res;
}
