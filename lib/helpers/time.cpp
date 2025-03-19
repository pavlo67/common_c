#include <ctime>

#include "time.h"

std::string custom_time(std::time_t t) {
    char timeString[std::size("yyyy-mm-dd_hh:mm:ss")];
    std::strftime(std::data(timeString), std::size(timeString),"%F_%T", std::localtime(&t));
    return timeString;
}

moment now() {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

uint64_t now_ms() {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

Timing::Timing() {
    cnt_        = 0;
    min_num_    = 0;
    max_num_    = 0;
    sum_        = 0;
    min_        = 0;
    max_        = 0;
};

void Timing::add(moment started_at) {
    duration once = now() - started_at;

    cnt_++;
    sum_ += once;

    if (cnt_ == 1) {
        min_     = max_     = once;
        min_num_ = max_num_ = 1;

    } else if (once < min_) {
        min_     = once;
        min_num_ = cnt_;

    } else if (once > max_) {
        max_     = once;
        max_num_ = cnt_;
    }
}

timing_stat Timing::get() {
    timing_stat stat = {cnt_,  min_num_, max_num_,min_, max_,  0};

    if (cnt_ > 0) {
        stat.avg = sum_ / static_cast<duration>(cnt_);
    }

    return stat;
}

void Timing::show(const std::string& label) {
    timing_stat s = get();
    printf((label + " timing: cnt = %6d, avg = %8d us, max = %8d us, min = %8d us\n").c_str(),
        s.cnt, s.avg / MICROSECOND, s.max / MICROSECOND, s.min / MICROSECOND);
}





//
// func (tm *Timing) Add(momentPrev time.Time) {
//     if tm == nil {
//         return
//     }
//
//     d := time.Now().Sub(momentPrev)
//
//     if tm.Cnt == 0 {
//         tm.Cnt = 1
//         tm.Sum = d
//         tm.Min = d
//         tm.Max = d
//     } else {
//         tm.Cnt++
//         tm.Sum += d
//         if d < tm.Min {
//             tm.Min = d
//         }
//         if d > tm.Max {
//             tm.Max = d
//         }
//     }
// }
//
// func (tm *Timing) String() string {
//     if tm == nil || tm.Cnt <= 0 {
//         return "<empty tm>"
//     }
//
//     return fmt.Sprintf("tm: cnt = %d, avg = %s, min = %s, max = %s",
//         tm.Cnt, tm.Sum/time.Duration(tm.Cnt), tm.Min, tm.Max)
// }
