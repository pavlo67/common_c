#include <list>
#include <dirent.h>
#include <opencv2/imgcodecs.hpp>

#include "lib/helpers/filelib.h"
#include "in.h"

std::string* files_list      = nullptr;
size_t       files_list_size = 0;
size_t       current_i       = 0;

const int EXTS_CNT = 5;

std::string exts[EXTS_CNT] = {
    ".jpg",
    ".png",
    ".pgm",
    ".bmp",
    ".gif",
};


VideoIn::VideoIn(const char* path, int width, int height, bool grayscale) {
    path_      = path;
    width_     = width;
    height_    = height;
    grayscale_ = grayscale;


    int i_ext = find_extension_in_dir(std::string(path), exts, EXTS_CNT);
    if (i_ext < 0) {
        files_list_size = 0;
        return;
    }

    auto ext = exts[i_ext];
    std::list<std::string> d_names;

    dirent *ent;
    DIR *dir = opendir(path_);
    if (!dir) {
        throw std::runtime_error("could not open directory: " + std::string(path));
    }

    while ((ent = readdir (dir))) {
        std::string d_name(ent->d_name);
        if (d_name.length() > 4 && d_name.substr(d_name.length() - 4) == ext) { d_names.emplace_back(d_name); }
    }
    closedir (dir);

    d_names.sort();

    files_list_size = d_names.size();
    files_list = new std::string[files_list_size];

    size_t i = 0;
    for (const std::string& d_name : d_names) {
        if (i < files_list_size) {
            files_list[i] = d_name;
        } else {
            printf("too many d_names... (#%lu / %s) files_list_size = %lu\n", i, d_name.c_str(), files_list_size);
        }
        i++;
    }

}

bool VideoIn::read(Mat& frame) {
    if (current_i >= files_list_size) { return false; }

    std::string d_name = files_list[current_i++];

    // printf("%s\n", d_name.c_str());

    std::string filename = path_ + d_name;
    frame = imread(filename, (grayscale_ ? IMREAD_GRAYSCALE : IMREAD_UNCHANGED));
    // printf("READ IMAGE FROM %s: %d %d %d\n", filename.c_str(), frame.type(), frame.rows, frame.cols);

    if (frame.empty()) {
        printf("EMPTY IMAGE FROM %s\n", filename.c_str());
        return false;
    }

    return true;
}

bool VideoIn::set_exposure(int exposure_us) {
    return true;
}

void VideoIn::release(bool forced) {
}
