#ifndef FORMAT_H
#define FORMAT_H

#define BIN_STR std::string("%c%c%c%c%c%c%c%c")
#define BIN_FMT "%c%c%c%c%c%c%c%c"
#define BIN(byte)  \
((byte) & 0x80 ? '1' : '0'), \
((byte) & 0x40 ? '1' : '0'), \
((byte) & 0x20 ? '1' : '0'), \
((byte) & 0x10 ? '1' : '0'), \
((byte) & 0x08 ? '1' : '0'), \
((byte) & 0x04 ? '1' : '0'), \
((byte) & 0x02 ? '1' : '0'), \
((byte) & 0x01 ? '1' : '0')

// printf((BIN_STR + BIN_STR).c_str(), BIN(10), BIN(5));


#endif //FORMAT_H
