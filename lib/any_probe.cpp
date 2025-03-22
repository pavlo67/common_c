#include <cstdint>
#include <cstdio>
#include <string>
#include <assert.h>

int main(int argc, char *argv[]) {

    assert(false && "A is not equal to B");


    // double fov_x_width_2  = 320;
    // double fov_y_height_2 = 240;
    // double fov_x_rad_2    =  23 * RAD;
    // double fov_y_rad_2    =  18 * RAD;
    //
    // int  x = 300;
    // int  y = 18;
    // int  w = 127;
    // int  h = 127;
    //
    // double att_bf_roll_deg = 1;
    // double att_pitch_deg   = 22.3;
    //
    // // p: -1.6, r: -3.4, bb: nan/nan deg [x:280 y:160 w:80 h:80]
    //
    // double trg_x = ((double)x + (double)w * 0.5) - fov_x_width_2;
    // double trg_y = ((double)y + (double)h * 0.5) - fov_y_height_2; // y-axis is directed from top to bottom like to pitch values
    //
    // point trg = rotate_by_angle({trg_x, trg_y}, att_bf_roll_deg * RAD);
    //
    // double trg_yaw_deg = angle_in_area_rad(trg.x, fov_x_width_2,   fov_x_rad_2) * DEG;
    // double trg_pitch_deg = angle_in_area_rad(trg.y, fov_y_height_2,  fov_y_rad_2) * DEG + att_pitch_deg;
    //
    // printf("trg_x: %f, trg_y: %f, trg.x: %f, trg.y: %f, trg_pitch_deg: %f\n",  trg_x, trg_y, trg.x, trg.y, trg_pitch_deg);

    // #1554 at 731575 / t: r:1.0, p:22.3, ya:28.0, bb:3.5/10.2 deg [x:300 y:18 w:127 h:127], f:1 >> r:1570, p:1800, y:1518, t:1332
}
