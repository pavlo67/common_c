#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
using namespace cv;

// inline Rect2i get_image_rect(const Mat& mat) { return Rect2i{0, 0, mat.cols, mat.rows}; }
// inline int    get_image_step(const Mat& mat) { return mat.cols * mat.channels(); }
inline int    is_image_gray (const Mat& mat) { return mat.dims == 2 && mat.channels() == 1; }

void log_image_bw_extended(const Mat& mat, const std::string& filename);
void narrow_range_bw      (const Mat& src, Mat& dst, uint8_t range);
void extend_range_bw      (const Mat& src, Mat& dst);

#endif //IMAGE_H


