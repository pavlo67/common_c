#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "lib/helpers/time.h"
#include "lib/video_in/libcamera.h"

using namespace cv;

int main() {
    // time_t start_time = time(0);
    // int frame_count = 0;
    // float lens_position = 100;
    // float focus_step = 50;

    uint32_t width = 640;
    uint32_t height = 480;
    uint32_t stride;

    int key;
    namedWindow("libcamera-demo", WINDOW_NORMAL);
    resizeWindow("libcamera-demo", width, height);

    LibCamera cam;
    if (cam.initCamera() != 0) {
        return -1;
    };

    cam.configureStill((int)width, (int)height, formats::YUV422, 1, 0);

     //    ControlList controls_;
     //    int64_t frame_time = 3000000 / 10;  // frame rate
     //    controls_.set(controls::FrameDurationLimits, libcamera::Span<const int64_t, 2>({ frame_time, frame_time }));
     //    controls_.set(controls::Brightness, 0.01);
     //    controls_.set(controls::Contrast, 0.1);
     //    controls_.set(controls::ExposureTime, 1000);
     //    cam.set(controls_);

    cam.startCamera();
    cam.VideoStream(&width, &height, &stride);

    int frames_cnt = 0, gaps_cnt   = 0;

    LibcameraOutData frameData;
    while (true) {
        if (!cam.readFrame(&frameData)) {
            gaps_cnt++;
            continue;
        }
        frames_cnt++;
        printf("frames_cnt: %d, gaps_cnt: %d\n", frames_cnt, gaps_cnt);
        // usleep(100000);
        // if (++frame_n % 25 == 2) {
        //     tm_grayscaling.show("to grayscale");
        // }
        //
        // auto at = now();
        //
        // // avg <190 us
        // Mat imYUV((int)height, (int)width, CV_8UC2, frameData.imageData, stride);
        // Mat im_gray; cvtColor(imYUV, im_gray, COLOR_YUV2GRAY_YUY2);
        //
        // // avg ~350 us
        // // Mat im_gray(480, 640, CV_8UC1); uint32_t size = 640 * 480;;
        // // for (uint32_t i = 0; i < size; i++) { im_gray.data[i] = frameData.imageData[i*2]; }
        //
        // tm_grayscaling.add(at);
        //
        // // size_t step = im_gray.step;
        // // printf("im_gray.cols: %d, im_gray.rows: %d, im_gray.step: %llu\n", im_gray.cols, im_gray.rows, step );
        //
        // imshow("libcamera-demo", im_gray);
        // key = waitKey(1);
        //
        // if (key == 'q') { break; }

        cam.returnFrameBuffer(frameData);
    }
    destroyAllWindows();
    cam.stopCamera();
    cam.closeCamera();
    return 0;
}
