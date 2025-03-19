// #include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "out.h"

// TODO??? use class inheritance to store VideoWriter in Writer object

VideoWriter writer;

VideoOut::VideoOut(const char* path, int width, int height, float fps, bool grayscale) {
   path_   = path;
   width_  = width;
   height_ = height;
   fps_    = fps;
   writer  = VideoWriter(
      path,
      CAP_GSTREAMER,
      0,
      fps_,
      Size(width_,height_),
      !grayscale);

   if (!writer.isOpened()) {
      // TODO???
   }
}

void VideoOut::write(Mat frame, int frame_n) {
   writer.write(frame);
   frame.release();
}

void VideoOut::release() {
   writer.release();
}


// inline const char*   VID_OUT         = "gst-launch-1.0 libcamerasrc ! queue ! autovideosink";
