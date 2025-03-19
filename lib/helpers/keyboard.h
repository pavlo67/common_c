#ifndef KEYBOARD_H
#define KEYBOARD_H

char cli_menu(const char** labels, int cnt);

// char get_key(uint16_t delay_us);
// #include <mutex>
// class Keyboard {
//     public:
//         Keyboard(int queue_length);
//         ~Keyboard();
//         char        poll();
//         uint8_t     queue_max_ = 0;
//         uint8_t     queue_length_;
//         char*       queue_;
//         std::mutex* mutex_;
// };

#endif //KEYBOARD_H
