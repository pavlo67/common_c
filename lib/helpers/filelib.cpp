#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <dirent.h>

#include "filelib.h"


FILE* new_file(const std::string& filename) {
    const char* log_file_c = filename.c_str();
    FILE* f_log_ptr = fopen(log_file_c, "w");
    if (!f_log_ptr) {
        printf("new_file(): error opening %s (errno = %d / %s)\n", log_file_c, errno, std::strerror(errno));
    } else {
        printf("new_file() -->  %s\n", log_file_c);
    }

    return f_log_ptr;
}

std::string new_path(const std::string& path) {
    if (path.empty()) {
        return "";
    }

    try {
        std::filesystem::create_directories(path);
    } catch (const std::exception& e) {
        printf("new_path(): error creating log path %s: %s\n", path.c_str(), e.what());
        return "";
    }

    return path.back() == '/' ? path : path + "/";;
}

void read_text_file(const std::string& filename, std::vector<std::string>& lines) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        printf("read_text_file(): error opening file: %s\n", filename.c_str());
        return;
    }

    std::string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();
}

int find_extension_in_dir(const std::string& path, const std::string* exts, int exts_cnt) {
    if (exts_cnt <= 0) {
        return -1;
    }

    dirent *ent;
    DIR *dir = opendir(path.c_str());
    if (!dir) {
        closedir(dir);
        throw std::runtime_error("find_extension_in_dir(): could not open directory: " + std::string(path));
    }

    while ((ent = readdir (dir))) {
        std::string d_name(ent->d_name);
        for (int i = 0; i < exts_cnt; i++) {
            int ext_length = exts[i].length();
            if (d_name.length() > ext_length && d_name.substr(d_name.length() - ext_length) == exts[i]) {
                closedir(dir);
                return i;
            }
        }
    }
    closedir(dir);

    return -1;
}