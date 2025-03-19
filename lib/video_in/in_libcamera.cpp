#include "in.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

#include "libcamera.h"

LibCamera cam;
uint32_t  stride;

VideoIn::VideoIn(const char* path, int width, int height, bool grayscale) {
    path_      = path;
    width_     = width;
    height_    = height;
    grayscale_ = grayscale;

    if (int res = cam.initCamera()) {
        throw std::runtime_error("Camera initialization error: " + std::to_string(res));
    };

    int64_t                      frame_time = 16667;  // frame rate
    controls::AeExposureModeEnum ae_mode    = controls::ExposureShort;
    bool                         ae_enable  = true;

    printf("Capturing libcamera: %d * %d, %ld us frame time, auto exposure: %d, auto exposure mode: %d\n", width, height, frame_time, ae_enable, ae_mode);

    cam.configureStill(width, height, formats::YUV422, 0, 0);

    ControlList controls_;

    controls_.set(controls::FrameDurationLimits, libcamera::Span<const int64_t, 2>({ frame_time, frame_time }));

    // controls_.set(controls::ExposureTime, 40000);
    // controls_.set(controls::AnalogueGain, 5.0);
    // controls_.set(controls::Brightness, 1.0);
    // controls_.set(controls::Contrast, 1.0);
    // controls_.set(controls::AeEnable, false);

    controls_.set(controls::AeEnable, ae_enable);
    controls_.set(controls::AeExposureMode, ae_mode);
    cam.set(controls_);

    cam.startCamera();
    cam.VideoStream(&width_, &height_, &stride);

    printf("CAPTURED LIBCAMERA\n");

}

bool VideoIn::set_exposure(int exposure_us) {
    ControlList controls_;
    controls_.set(controls::ExposureTime, exposure_us);
    cam.set(controls_);

    return true;
}

LibcameraOutData frameData;

bool VideoIn::read(Mat& frame) {
    if (!cam.readFrame(&frameData)) { return false;  }

    // printf("width_: %d, height_: %d, stride: %d\n", width_, height_, stride);

    Mat imYUV((int)height_, (int)width_, CV_8UC2, frameData.imageData, stride);
    // cvtColor(imYUV, frame,  COLOR_YUV2RGB_YUY2);
    cvtColor(imYUV, frame,  grayscale_ ? COLOR_YUV2GRAY_YUY2 : COLOR_YUV2RGB_YUY2);
    cam.returnFrameBuffer(frameData);

    // avg <190 us
    // Mat imYUV((int)h, (int)w, CV_8UC2, frameData.imageData, stride);
    // Mat im_gray; cvtColor(imYUV, im_gray, COLOR_YUV2GRAY_YUY2);

    // avg ~350 us
    // Mat im_gray(480, 640, CV_8UC1); uint32_t size = 640 * 480;;
    // for (uint32_t i = 0; i < size; i++) { im_gray.data[i] = frameData.imageData[i*2]; }


    return true;
}

void VideoIn::release(bool forced) {
    cam.stopCamera();
    cam.closeCamera();
}

