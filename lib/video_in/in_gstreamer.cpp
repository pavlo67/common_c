#include <opencv2/videoio.hpp>

#include "in.h"

// TODO??? use class inheritance to store VideoWriter in Writer object

VideoCapture cap;


VideoIn::VideoIn(const char* path, int width, int height, bool grayscale) {
   path_      = path;
   grayscale_ = grayscale;

   printf("CAPTURING %s...\n", path);
   cap = VideoCapture(path);
   if (!cap.isOpened()) {
      throw std::runtime_error("Cannot open video: " + std::string(path));
   }
   printf("CAPTURED %s\n", path);

   grayscale_in_ = (int)round(cap.get(CAP_PROP_MONOCHROME));
   width_        = (int)round(cap.get(CAP_PROP_FRAME_WIDTH));
   height_       = (int)round(cap.get(CAP_PROP_FRAME_HEIGHT));

}

bool VideoIn::set_exposure(int exposure_us) {
   return false;
}

bool VideoIn::read(Mat& frame) {
   if (grayscale_ == grayscale_in_) {
      return cap.read(frame);
   }

   Mat frame0;
   if (!cap.read(frame0)) { return false; }

   // TODO!!! check another conversion pairs
   cvtColor(frame0, frame, grayscale_ ? COLOR_BGR2GRAY : COLOR_GRAY2BGR);

   return true;
}

void VideoIn::release(bool forced) {
   cap.release();
}

