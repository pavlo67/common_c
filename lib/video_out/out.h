
#ifndef OUT_H
#define OUT_H

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class VideoOut {
public:
    VideoOut(const char* path, int width, int height, float fps, bool grayscale);
    void write(Mat frame, int frame_n);
    void release();

private:
    const char* path_;
    int         width_;
    int         height_;
    float       fps_;
    // std::string path_;

};

#endif //OUT_H