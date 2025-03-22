#include "image.h"

void log_image_bw_extended(const Mat& mat, const std::string& filename) {
    Mat mat_extended; extend_range_bw(mat, mat_extended);
    if (!imwrite(filename, mat_extended)) { printf("can't save %s\n", filename.c_str()); }
    mat_extended.release();
}

