#include "in.h"
#include "lccv.hpp"

// TODO??? use class inheritance to store lccv::PiCamera in Writer object

lccv::PiCamera cam;

VideoIn::VideoIn(const char* path, int width, int height, bool grayscale) {
    path_      = path;
    width_     = width;
    height_    = height;
    grayscale_ = grayscale;

    float fps        = 60;
    float exposure   = 5000;
    float brightness = 1.5;

    printf("Capturing LCCV: %d * %d, %.1f fps, %.0f us, %.1f brightness\n", width, height, fps, exposure, brightness);

    cam.options->video_width  = width;
    cam.options->video_height = height;
    cam.options->framerate    = fps;
    //cam.options->shutter      = exposure;
    //cam.options->exposure_index=Exposure_Modes::EXPOSURE_SHORT;
    //cam.options->brightness   = brightness;
    cam.startVideo();

    printf("CAPTURED LCCV\n");
}


bool VideoIn::set_exposure(int exposure_us) {
    cam.options->shutter = exposure_us;
    return true;
}

bool VideoIn::read(Mat& frame) {
   return cam.getVideoFrame(frame, 1000);
}

void VideoIn::release(bool forced) {
    cam.stopVideo();
   
}

