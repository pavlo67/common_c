#ifndef IMAGE_COMPOSER_H
#define IMAGE_COMPOSER_H

#include <opencv2/opencv.hpp>
using namespace cv;

enum connectivity { conn_none, conn_diagonal, conn_side, conn_intersection };

class Figure {
    public:
        std::vector<Point2i> points_;
        Point2i              position_;

        Rect2i       rect2i();
        connectivity is_connected_to(Figure f);
};


class ImageComposer {

    public:
        ImageComposer() = default;
        ~ImageComposer() = default;
        bool add_figure(Figure f, connectivity connectivity_allowed);
        void get_image(Mat& img, uchar fg, uchar bg, int margin_right, int margin_bottom);

    private:
        std::vector<Figure> figures_;

};



#endif //IMAGE_COMPOSER_H
