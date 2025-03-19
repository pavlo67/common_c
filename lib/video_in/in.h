
#ifndef IN_H
#define IN_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

class VideoIn {
    public:
        VideoIn(const char* path, int width, int height, bool grayscale);
        bool set_exposure(int exposure_us);
        bool read(Mat& frame);
        void release(bool forced);

    private:
        const char* path_         = nullptr;
        bool        grayscale_    = false;
        bool        grayscale_in_ = false;
        uint32_t    width_        = 0;
        uint32_t    height_       = 0;

};

#endif //IN_H