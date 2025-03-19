#include "plane.h"

#include <cmath>

point* lines_intersection(segment s0, segment s1) {
    // https://stackoverflow.com/questions/7446126/opencv-2d-line-intersection-helper-function
    // https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

    point r = {s0.p1.x - s0.p0.x, s0.p1.y - s0.p0.y};
    point l = {s1.p1.x - s1.p0.x, s1.p1.y - s1.p0.y};

    double cr = cross(r, l);
    if (cr > -1e-8 && cr < -1e-8) {
        // lines are about parallel (they may be collinear!)
        return nullptr;
    }

    point q = {s1.p0.x - s0.p0.x, s1.p0.y - s0.p0.y};
    double t = cross(q, l) / cr;

    auto p = new point();
    p->x = s0.p0.x + t*r.x;
    p->y = s0.p0.y + t*r.y;

    return p;

}

double x_to_y_angle_from_ox_rad(point p) {
    if (p.x == 0) {
        if (p.y > 0) {
            return M_PI_2;
        } else if (p.y < 0) {
            return -M_PI_2;
        } else {
            return NAN;
        }
    } else if (p.x >= 0) {
        return std::atan(p.y / p.x);
    } else if (p.y >= 0) {
        return std::atan(p.y / p.x) + M_PI;
    } else {
        return std::atan(p.y / p.x) - M_PI;
    }
}

double angles_delta(point p0, point p1) {
    double angle = x_to_y_angle_from_ox_rad(p1) - x_to_y_angle_from_ox_rad(p0);
    return (angle > M_PI) ? angle - 2 * M_PI : (angle <= -M_PI) ? angle + 2 * M_PI : angle;
}

point rotate_by_angle(point p, double add_angle_rad) {
    double r = std::sqrt(p.x*p.x + p.y*p.y); if (r == 0) { return {0, 0}; }
    double a = x_to_y_angle_from_ox_rad(p);

    return {r * std::cos(a + add_angle_rad), r * std::sin(a + add_angle_rad)};
}

// Angle — це кут напряму до точки, яка на зображенні має v пікселів відхилення від центру
// vMax, angleMax — відхилення/кут деякої иншої точки на зображенні (береться крайня точка фрейму)
double angle_in_area_rad(double v, double v_max, double angle_max_rad) {
    // d - "відстань" до цілі (проєкція в площині Oxy)
    // vMax = d * std::tan(angleMax)
    // v    = d * std::tan(angle)
    // std::tan(angle) = v * std::tan(angleMax) / vMax

    return std::atan(std::tan(angle_max_rad) * v / v_max);
    // return angleMax * v / vMax  // approximately...
}

