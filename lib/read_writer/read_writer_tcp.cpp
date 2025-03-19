#include "read_writer.h"

#include <cstring>
#include <cstdio>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <mutex>
#include <unistd.h>

ReadWriterTCP::ReadWriterTCP(const char* ip, int port, tcp_options* opts) {
    ip_   = ip;
    port_ = port;
    opts_ = opts ? *opts : tcp_options{};
}

bool ReadWriterTCP::connect() {
    printf("CONNECTING TO %s:%d\n", ip_, port_);

    bzero(&sock_addr_, sizeof(sock_addr_));
    hostent* host = gethostbyname(ip_);
    sock_addr_.sin_family = AF_INET;
    sock_addr_.sin_addr.s_addr = inet_addr(inet_ntoa(*(in_addr*)*host->h_addr_list));
    sock_addr_.sin_port = htons(port_);
    sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    int status = ::connect(sock_fd_, (sockaddr*) &sock_addr_, sizeof(sock_addr_));
    if (status < 0) {
        printf("ReadWriterTCP::connect() --> error connecting %s:%d (errno = %d / %s)\n", ip_, port_, errno, std::strerror(errno));
        return false;
    }

    printf("CONNECTED TO %s:%d\n", ip_, port_);
    is_connected_ = true;

    return true;
}

uint16_t ReadWriterTCP::read(uint8_t* buffer, uint16_t buffer_length) {
    socklen_t src_addr_len = sizeof(sock_addr_);
    return recvfrom(sock_fd_, buffer, buffer_length, 0, (sockaddr*)(&sock_addr_), &src_addr_len);
}

uint16_t ReadWriterTCP::write(const uint8_t* buffer, uint16_t buffer_length) {
    auto n = sendto(sock_fd_, buffer, buffer_length, 0, (const sockaddr*)&sock_addr_, sizeof(sock_addr_));
    if (n != buffer_length) {
        printf("ReadWriterTCP::write() --> %ld instead of %d bytes (errno = %d / %s)\n", n, buffer_length, errno, std::strerror(errno));
    }

    return n;
}
