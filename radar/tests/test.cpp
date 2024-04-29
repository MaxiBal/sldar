#include "radar/interface.hpp"
#include <iostream>

int main(void)
{
    std::string message = "{\"Product\":\"OPS242\"}\n{\"Version\":\"1.3.0\"}\n{\"SamplingRate\":10000, \"resolution\":0.0607}\n{\"SampleSize\":1024}\n{\"Clock\":\"54\"}\n{\"Q2COUNT\":\"1149\"}\n{\"PowerMode\":\"Continuous\"}\n{\"Squelch\":\"100\"}\n{\"RequiredMinSpeed\":\"0.000\"}";

    auto message_map = slamdar::radar::parse_return_message(message);

    if (message_map["Clock"] != "54") { return 1; }
    if (message_map["Version"] != "1.3.0") { return 1; }

    /* Test serial device */

    const unsigned long baudrate = 115200;

    std::string port = "/dev/ttyACM0";

    slamdar::radar::radar radar_conn(port, baudrate);

    std::cout << "Heard: " << radar_conn.readline() << "\n";

    return 0;
}