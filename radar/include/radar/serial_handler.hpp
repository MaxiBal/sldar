#ifndef RADAR_SERIAL_HANDLER_HPP
#define RADAR_SERIAL_HANDLER_HPP

#include <string>
#include <vector>
#include <cassert>

#include "serialib.h"


namespace slamdar {
namespace radar {

class radar
{
    std::string port;
    unsigned long baudrate;
    serialib serial;
    
public:

    radar() : serial() {};

    void open(std::string& port_, unsigned long baudrate_)
    {
        port = port_;
        baudrate = baudrate_;
        std::cout << "Connecting to port: " << port_ << "with baudrate: " << baudrate_ << "\n";
        char open_error = serial.openDevice(port_.c_str(), baudrate_);
        assert(open_error == 1);
    }

    std::string readline(const size_t max_buf_size = 32) 
    {
        char buf[max_buf_size];

        serial.readString(buf, '\n', max_buf_size);

        return std::string(buf);
    }

    // bool isOpen()
    // {
    //     return serial.();
    // }
};

}
}

#endif