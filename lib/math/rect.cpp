#include "rect.h"

Rect2i rect2i(Point2f point, float halfside_x, float halfside_y) {
    int x = (int)std::round(point.x - halfside_x);
    int y = (int)std::round(point.y - halfside_y);
    int w = halfside_x > 0 ? std::max(1, (int)std::round(halfside_x * 2)) : 0;
    int h = halfside_y > 0 ? std::max(1, (int)std::round(halfside_y * 2)) : 0;
    return {x, y, w, h};
}

Rect2i rect2i_rect(rect& r) {
    int x = (int)std::round(r.point.x-r.halfside_x);
    int y = (int)std::round(r.point.y-r.halfside_y);
    int w = r.halfside_x > 0 ? std::max(1, (int)std::round(r.halfside_x * 2)) : 0;
    int h = r.halfside_y > 0 ? std::max(1, (int)std::round(r.halfside_y * 2)) : 0;
    return {x, y, w, h};
}

rect averaged(const rect& r0, const rect& r1, float ratio_0_to_1) {
    float ratio0 = ratio_0_to_1 / (ratio_0_to_1 + 1);
    float ratio1 = 1 / (ratio_0_to_1 + 1);
    return {{r0.point.x * ratio0 + r1.point.x * ratio1, r0.point.y * ratio0 + r1.point.y * ratio1},
        r0.halfside_x * ratio0 + r1.halfside_x * ratio1, r0.halfside_y * ratio0 + r1.halfside_y * ratio1};
}

rect shifted(const rect& r, Point2f shift, Rect2i bounds) {
    float x          = r.point.x + shift.x;
    float halfside_x = r.halfside_x;

    float x_over     = x + halfside_x - float(bounds.x + bounds.width - 1);
    if (x_over > 0)  { x -= float(x_over  * 0.5); halfside_x -= float(x_over  * 0.5); }

    float x_under    = float(bounds.x) - (x - halfside_x);
    if (x_under > 0) { x += float(x_under * 0.5); halfside_x -= float(x_under * 0.5); }

    float y = r.point.y + shift.y;
    float halfside_y = r.halfside_y;

    float y_over     = y + halfside_y - float(bounds.y + bounds.height - 1);
    if (y_over > 0)  { y -= float(y_over  * 0.5); halfside_y -= float(y_over  * 0.5); }

    float y_under    = float(bounds.y) - (y - halfside_y);
    if (y_under > 0) { y += float(y_under * 0.5); halfside_y -= float(y_under * 0.5); }

    return {{x, y}, halfside_x, halfside_y};
}
