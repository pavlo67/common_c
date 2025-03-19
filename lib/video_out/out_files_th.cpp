#include "out.h"

#include <thread>
#include <mutex>
#include <unistd.h>

std::thread out_th;
std::mutex mutex;
Mat frame_saved;
int frame_n_saved;

void writing_loop(const char* path) {
    char buffer[strlen(path) + 10];

    Mat frame_copy;
    int frame_n_copy;

    while (true) {
        mutex.lock();
        if (frame_saved.empty()) {
            mutex.unlock();
            usleep(1000);
            continue;
        }

        frame_copy   = frame_saved.clone();
        frame_n_copy = frame_n_saved;
        mutex.unlock();

        sprintf(buffer, "%s%05d.jpg", path, frame_n_copy);
        imwrite(buffer, frame_copy);
        frame_copy.release();
    }
}

VideoOut::VideoOut(const char* path, int width, int height, float fps, bool grayscale) {
    path_ = path;
    out_th = std::thread(writing_loop, path);
}

void VideoOut::write(Mat frame, int frame_n) {
    mutex.lock();
    frame_saved.release();
    frame_saved   = frame;
    frame_n_saved = frame_n;
    mutex.unlock();
}

void VideoOut::release() {
    frame_saved.release();
    if (true) {
        out_th.detach();
    } else {
        out_th.join();
    }
}
