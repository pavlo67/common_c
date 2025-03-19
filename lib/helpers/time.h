#ifndef TIMING_H
#define TIMING_H

#include <cstdint>
#include <string>

// base types & functions ---------------------------------------------------------

typedef uint64_t duration;
typedef uint64_t moment;

const duration NANOSECOND  = 1;
const duration MICROSECOND = 1e3;
const duration MILLISECOND = 1e6;
const duration SECOND      = 1e9;

std::string custom_time(time_t t);
moment      now();
uint64_t    now_ms();

// Timing -------------------------------------------------------------------------

typedef struct {
    int32_t  cnt;
    int32_t  min_num;
    int32_t  max_num;
    duration min;
    duration max;
    duration avg;
} timing_stat;

class Timing {
public:

    Timing();
    void        add(moment started_at);
    timing_stat get();
    void        show(const std::string& label);

private:
    int32_t  cnt_;
    int32_t  min_num_;
    int32_t  max_num_;
    duration min_;
    duration max_;
    duration sum_;
};



#endif //TIMING_H
