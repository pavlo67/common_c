#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "lib/helpers/time.h"
#include "lib/video_in/in.h"
#include "lib/video_out/out.h"

using namespace cv;

const char* WINDOW = "video_check";

int main() {
    int width = 640;
    int height = 480;

    // int key;

    float fps = 10;

    VideoIn in(nullptr, width, height, false);
    VideoOut out(WINDOW, width, height, fps, false);

    Mat frame; int frame_n = 0; uint64_t at = 0, at_new;

    while (true) {
        if (!in.read(frame)) {
            // printf("#%d: can't read frame\n", frame_n);
            continue;
        }

        ++frame_n;

        at_new = now_ms();

        uint64_t delta = at_new - at;

        if (delta > 25) {
            printf("!!!! #%d at %lu\n", frame_n, delta);
        }
        at = at_new;

        // if (frame_n % 25 == 2) {
        //     printf("#%d\n", frame_n);
        // }

        out.write(frame, frame_n);

        // imshow(WINDOW, frame);
        // key = waitKey(1);
        //
        // if (key == 'q') { break; }

    }
    destroyAllWindows();
    in.release(false);

    return EXIT_SUCCESS;
}
