#include "image.h"

void narrow_range_bw(const Mat& src, Mat& dst, uint8_t range) {
    if (src.type() != CV_8UC1) {
        throw std::runtime_error("narrow_range_bw(): src type (" + std::to_string(src.type()) + ") is not CV_8UC1");
    }

    dst.create(src.rows, src.cols, CV_8UC1);
    uint8_t *pix_max = src.data + src.rows * src.cols;

    uint32_t sum = 0; // TODO!!! be careful with integer overflow
    for (uint8_t *pix = src.data; pix < pix_max; pix++) {
        sum += *pix;
    }
    uint8_t avg = sum / (src.rows * src.cols);
    uint8_t range_2 = range / 2;

    uint8_t val_min = (avg <=       range_2) ?   0 : avg - range_2;
    uint8_t val_max = (avg >= 255 - range_2) ? 255 : avg + range_2;

    printf("avg = %d, val_min: %d, val_max: %d\n", avg, val_min, val_max);

    for (uint8_t *pix = src.data; pix < pix_max; pix++) {
        // *(dst.data + (pix - src.data)) = std::max(val_min,std::min(val_max, *pix));
        *(dst.data + (pix - src.data)) = (*pix < val_min) ? val_min : (*pix > val_max) ? val_max : *pix;
    }
}

void extend_range_bw(const Mat& src, Mat& dst) {
    if (src.type() != CV_8UC1) {
        throw std::runtime_error("extend_range_bw(): src type (" + std::to_string(src.type()) + ") is not CV_8UC1");
    }

    dst.create(src.rows, src.cols, CV_8UC1);
    uint8_t *pix_max = src.data + src.rows * src.cols;

    uint8_t p_max = 0;
    for (uint8_t *pix = src.data; pix < pix_max; pix++) {
        if (*pix > p_max) p_max = *pix;
    }

    float v_max = p_max;
    for (uint8_t *pix = src.data; pix < pix_max; pix++) {
        // TODO??? use integer operations only:  uint8_t((255 * uint16_t(*pix)) / (uint16_t)p_max))
        *(dst.data + (pix - src.data)) = uint8_t(std::round(255 * (float(*pix) / v_max) * (float(*pix) / v_max)));
    }
}

