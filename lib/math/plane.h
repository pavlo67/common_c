#ifndef PLANE_H
#define PLANE_H
#include <math.h>

const double RAD = M_PI / 180;
const double DEG = 180 / M_PI;

typedef struct {
    double x;
    double y;
} point;

typedef struct {
    point p0;
    point p1;
} segment;

double x_to_y_angle_from_ox(point p);
point  rotate_by_angle(point p, double angle);
double angle_in_area_rad(double v, double v_max, double angle_max);
double angles_delta(point p0, point p1);
point* lines_intersection(segment s0, segment s1);

inline double plane_distance(point p1, point p2)  {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
inline point vector(point p0, point p1) {
    return {p1.x - p0.x, p1.y - p0.y};
}

inline double cross(point p1, point p2)  {
    return p1.x * p2.y - p1.y * p2.x;
}


#endif //PLANE_H
