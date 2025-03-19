#ifndef READWRITER_H
#define READWRITER_H

#include <cstdint>
#include <string>

// TODO??? use template class

class ReadWriter {
    public:
        virtual ~ReadWriter() {};
        virtual bool     connect()                                            = 0;
        virtual uint16_t required_buffer_length()                             = 0;
        virtual uint16_t read(uint8_t* buffer, uint16_t buffer_length)        = 0;
        virtual uint16_t write(const uint8_t* buffer, uint16_t buffer_length) = 0;
        inline  bool     is_connected() const { return is_connected_; }
    protected:
        bool    is_connected_ = false;
};

#include <termios.h>

typedef struct {} serial_options;

class ReadWriterSerial : public ReadWriter {
    public:
        ReadWriterSerial(const std::string* fc_addrs, int fc_addrs_cnt, int baud_rate, serial_options* opts = nullptr);
        ~ReadWriterSerial() override {};

        bool     connect()                                            override;
        uint16_t required_buffer_length()                             override { return 512; };
        uint16_t read(uint8_t* buffer, uint16_t buffer_length)        override;
        uint16_t write(const uint8_t* buffer, uint16_t buffer_length) override;

private:
        const std::string* fc_addrs_;
        int                fc_addrs_cnt_;
        const char*        device_;
        int                baud_rate_;
        serial_options     opts_;
        int                serial_fd_;
        termios            serial_{};
};

#include <netinet/in.h>

typedef struct {} tcp_options;

class ReadWriterTCP : public ReadWriter {
    public:
        ReadWriterTCP(const char* ip, int port, tcp_options* opts = nullptr);
        ~ReadWriterTCP() override {};

        bool     connect()                                            override;
        uint16_t required_buffer_length()                             override { return 4096; };
        uint16_t read(uint8_t* buffer, uint16_t buffer_length)        override;
        uint16_t write(const uint8_t* buffer, uint16_t buffer_length) override;
    private:
        const char* ip_;
        int         port_;
        tcp_options opts_;
        int         sock_fd_;
        sockaddr_in sock_addr_;
};

#endif //READWRITER_H
