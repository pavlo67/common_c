#ifndef RECT_H
#define RECT_H

#include <opencv2/core/types.hpp>

using namespace cv;

typedef struct {
    Point2f point;
    float   halfside_x;
    float   halfside_y;
} rect;

inline bool rects_intersect(rect& r0, rect& r1) {
    return std::abs(r0.point.x-r1.point.x) <= r0.halfside_x+r1.halfside_x && std::abs(r0.point.y-r1.point.y) <= r0.halfside_y+r1.halfside_y;
}

inline rect rect_rect2f(Rect2f r) {
    float halfside_x = r.width * 0.5f, halfside_y = r.height * 0.5f;
    return { Point2f(r.x + halfside_x, r.y + halfside_y), halfside_x, halfside_y };
}


Rect2i rect2i(Point2f point, float halfside_x, float halfside_y);
Rect2i rect2i_rect(rect& r);
rect   shifted(const rect& r, Point2f shift, Rect2i bounds);
rect   averaged(const rect& r0, const rect& r1, float ratio_0_to_1);

#endif //RECT_H
