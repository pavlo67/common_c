
#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <string>
#include <vector>


std::string new_path(const std::string& path);
FILE*       new_file(const std::string& filename); // new_path doesn't add a time-part to the path
void        read_text_file(const std::string& filename, std::vector<std::string>& lines);
int         find_extension_in_dir(const std::string& path, const std::string* exts, int exts_cnt);


#endif //LOGGER_H
