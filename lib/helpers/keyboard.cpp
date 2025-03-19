#include <cstdio>
#include <filesystem>

#include "keyboard.h"

char cli_menu(const char** labels, int cnt) {
    for (char i = 0; i < std::min(10, cnt); i++) {
        printf("%d: %s\n", i, labels[i]);
    }

    int ch;
    while (true) {
        ch = getchar();
        if (ch >= '0' && (ch - '0') < cnt) {
            char selected = char((int)ch - '0');
            printf("SELECTED: %s\n", labels[selected]);
            return selected;
        }
    }
}

// #include <thread>
//
// std::thread th;
//
// // TODO!!! use kbhit()
// // TODO!!! hide Keyboard class fields with private declaration
//
// void loop(Keyboard* kb) {
//     if (kb == nullptr) { return; }
//
//     bool new_line = true;
//
//     while (true) {
//         char ch = getchar();
//         if (!(ch == 10 || ch == 13)) {
//             new_line = false;
//
//         } else if (!new_line) {
//             new_line = true;
//             continue;
//
//         }
//
//         // printf("got %c / %d\n", ch, ch);
//
//         kb->mutex_->lock();
//         if (kb->queue_max_ < kb->queue_length_) {
//             kb->queue_[kb->queue_max_++] = ch;
//         } else {
//             for (int i = 1; i < kb->queue_length_; i++) { kb->queue_[i-1] = kb->queue_[i]; } kb->queue_[kb->queue_length_-1] = ch;
//         }
//         kb->mutex_->unlock();
//     }
// }
//
//
// Keyboard::Keyboard(int queue_length) {
//     queue_length_ = queue_length;
//     queue_        = new char[std::max(1, queue_length) ];
//     mutex_        = new std::mutex();
//     th            = std::thread(loop, this);
// }
//
// Keyboard::~Keyboard() {
//     th.detach();
//     printf("keyboard is detached!\n");
// }
//
// char Keyboard::poll() {
//     char ch;
//
//     mutex_->lock();
//     if (queue_max_ <= 0) {
//         ch = 0;;
//     } else {
//         ch = queue_[0];
//         for (int i = 1; i < queue_max_; i++) { queue_[i-1] = queue_[i]; }
//         queue_max_--;
//     }
//     mutex_->unlock();
//
//     return ch;
// }
//
//

// #include <unistd.h>
// #include <sys/time.h>
// #include <sys/types.h>
// #include <termios.h>
// const uint16_t GET_KEY_DELAY_US = 10000;
// char get_key(uint16_t delay_us) {
//     termios oldSettings, newSettings;
//
//     tcgetattr( fileno( stdin ), &oldSettings );
//     newSettings = oldSettings;
//     newSettings.c_lflag &= (~ICANON & ~ECHO);
//     tcsetattr( fileno(stdin), TCSANOW, &newSettings );
//
//     fd_set set;
//     timeval tv;
//
//     tv.tv_sec  = 0;
//     tv.tv_usec = delay_us;
//
//     FD_ZERO(&set); FD_SET(fileno(stdin), &set);
//
//     char c = -1;
//     int res = select(fileno(stdin)+1, &set, nullptr, nullptr, &tv);
//     if (res > 0) {
//         read(fileno(stdin), &c, 1);
//     }
//
//     tcsetattr( fileno(stdin), TCSANOW, &oldSettings );
//     return c;
// }
