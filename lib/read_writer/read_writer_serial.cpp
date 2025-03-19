#include "read_writer.h"

#include <fstream>
#include <fcntl.h>
#include <unistd.h>

#include <cstring>

ReadWriterSerial::ReadWriterSerial(const std::string* fc_addrs, int fc_addrs_cnt, int baud_rate, serial_options* opts) {
    fc_addrs_     = fc_addrs;
    fc_addrs_cnt_ = fc_addrs_cnt;
    device_       = nullptr;
    baud_rate_    = baud_rate;
    opts_         = opts ? *opts : serial_options{};
    serial_fd_    = 0;
    serial_    = {};
}

bool ReadWriterSerial::connect() {

    for (int i = 0; i < fc_addrs_cnt_; i++) {

        const char* device = fc_addrs_[i].c_str();
        printf("CONNECTING TO %s\n", device);

        serial_fd_ = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
        if (serial_fd_ == -1) {
            printf("ReadWriterSerial::connect() --> error opening %s (errno = %d / %s)\n", device, errno, std::strerror(errno));
            continue;
        };

        if (tcgetattr(serial_fd_, &serial_) < 0) {
            printf("ReadWriterSerial::connect() --> error getting configuration from %s (errno = %d / %s)\n", device, errno, std::strerror(errno));
            continue;
        };

        tcflag_t baud_rate_flag = (baud_rate_ == 230400) ? B230400 : (baud_rate_ == 57600) ? B57600 : B115200;  // TODO!!!
        serial_.c_iflag = 0;
        serial_.c_oflag = 0;
        serial_.c_lflag = 0;
        serial_.c_cflag = 0;
        serial_.c_cc[VMIN] = 0;
        serial_.c_cc[VTIME] = 0;
        serial_.c_cflag = baud_rate_flag | CS8 | CREAD;
        if (tcsetattr(serial_fd_, TCSANOW, &serial_) != 0) {
            printf("ReadWriterSerial::connect() --> error setting up %s to %d (errno = %d / %s)\n", device, baud_rate_, errno, std::strerror(errno));
            continue;
        }

        device_ = device;
        printf("CONNECTED TO %s at %d\n", device_, baud_rate_);
        return is_connected_ = true;
    }

    return false;
}

uint16_t ReadWriterSerial::read(uint8_t* buffer, uint16_t buffer_length) {

    return ::read(serial_fd_, buffer, buffer_length);
}

uint16_t ReadWriterSerial::write(const uint8_t* buffer, uint16_t buffer_length) {
    auto n = ::write(serial_fd_, buffer, buffer_length);
    if (n != buffer_length) {
        printf("ReadWriterSerial::write() --> %ld instead of %d bytes (errno = %d / %s)\n", n, buffer_length, errno, std::strerror(errno));
    }

    return n;
}


