
#include "out.h"

VideoOut::VideoOut(const char* path, int width, int height, float fps, bool grayscale) {
    path_ = "!!!";
    namedWindow(path_, WINDOW_AUTOSIZE);
}

void VideoOut::write(Mat frame, int frame_n) {
    imshow(path_, frame);
    waitKey(5);
    frame.release();
}

void VideoOut::release() {
    destroyWindow(path_);
}
