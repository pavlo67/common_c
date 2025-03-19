#include "out.h"

VideoOut::VideoOut(const char* path, int width, int height, float fps, bool grayscale) {
    path_ = path ? path : "";
}

void VideoOut::write(Mat frame, int frame_n) {
    char buffer[strlen(path_) + 10];

    sprintf(buffer, "%s%05d.jpg", path_, frame_n);
    imwrite(buffer, frame);
    frame.release();
}

void VideoOut::release() {
}
