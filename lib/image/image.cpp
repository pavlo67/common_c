#include "image.h"

// bool image_from_mat(const Mat& mat, Point2i point, image& img) {
//     if (mat.data == nullptr) {
//         printf("image_from_mat(): mat.data == nullptr\n");
//         return false;
//     } else if (mat.dims != 2) {
//         printf("image_from_mat(): mat.dims = %d\n", mat.dims);
//         return false;
//     }
//
//     img.point = point;
//     img.mat   = mat;
//
//     return true;
// }
//

void log_image_bw_extended(const Mat& mat, const std::string& filename) {
    Mat mat_extended; extend_range_bw(mat, mat_extended);
    if (!imwrite(filename, mat_extended)) { printf("can't save %s\n", filename.c_str()); }
    mat_extended.release();
}

