#include "image_composer.h"

Rect2i Figure::rect2i() {
    Rect2i r = {};

    for (Point2i p : points_) {
        if (r.width == 0) {
            r.x     = p.x;
            r.y     = p.y;
            r.width = r.height = 1;

            // printf("x: %d, y: %d, width: %d, height: %d\n", r.x, r.y, r.width, r.height);

        } else {
            if (p.x < r.x) {
                r.width += r.x - p.x;
                r.x = p.x;
            } else if (p.x >= r.x + r.width) {
                r.width = p.x + 1 - r.x;
            }
            if (p.y < r.y) {
                r.height += r.y - p.y;
                r.y = p.y;
            } else if (p.y >= r.y + r.height) {
                r.height = p.y + 1 - r.y;
            }
            // printf("x: %d, y: %d --> x: %d, y: %d, width: %d, height: %d\n", p.x, p.y, r.x, r.y, r.width, r.height);
        }
    }

    return r + position_;
}

connectivity Figure::is_connected_to(Figure f) {
    connectivity conn = conn_none;
    for (Point2i p_add_int : f.points_) {
        Point2i p_add = p_add_int + f.position_;
        for (Point2i p_int : points_) {
            Point2i p = p_int + position_;
            if (p_add == p) {
                return conn_intersection;
            } else if (conn == conn_side) {
                continue;
            } else if ((p_add.x == p.x && (p_add.y == p.y-1 || p_add.y == p.y+1))
                   ||  (p_add.y == p.y && (p_add.x == p.x-1 || p_add.x == p.x+1))) {
                conn = conn_side;
            } else if (conn == conn_diagonal) {
                continue;
            } else if ((p_add.x == p.x-1 && p_add.y == p.y-1) || (p_add.x == p.x-1 && p_add.y == p.y+1)
                   ||  (p_add.x == p.x+1 && p_add.y == p.y-1) || (p_add.x == p.x+1 && p_add.y == p.y+1)) {
                conn = conn_diagonal;
            }
        }
    }

    return conn;
}

bool ImageComposer::add_figure(Figure f, connectivity connectivity_allowed) {
    for (const Figure& f_ : figures_) {
        if (f.is_connected_to(f_) > connectivity_allowed) {
            return false;
        }
    }
    figures_.push_back(f);

    return true;
}

void ImageComposer::get_image(Mat &img, uchar fg, uchar bg, int margin_right, int margin_bottom) {
    Rect2i rect;
    for (Figure& f_ : figures_) {
        rect |= f_.rect2i();
    }

    img = Mat(rect.y + rect.height + margin_bottom, rect.x + rect.width + margin_right, CV_8UC1);

    uchar* data = img.data;
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            data[x] = bg;
        }
        data += img.step;
    }

    for (Figure& f_ : figures_) {
        for (Point2i p : f_.points_) {
            img.data[(p.y + f_.position_.y) * img.step + (p.x + f_.position_.x)] = fg;
        }
    }
}
