#ifndef RADAR_INTERFACE_HPP
#define RADAR_INTERFACE_HPP

#include <cassert>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "serial_handler.hpp"

namespace slamdar {
namespace radar {


// Parses a message that is sent from the USB serial connection to the radar
// Message should come in the format of:
//  {"Product":"OPS242"}
//  {"Version":"1.3.0"}
//  ...
// Returns an std::map with key name and value
//  Converts any integer or float value into string 
std::map<std::string, std::string> parse_return_message(std::string&);

};
};

#endif