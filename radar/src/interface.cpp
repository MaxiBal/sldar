#include "radar/interface.hpp"

static std::vector<std::string> split_string_by_newline(std::string& str)
{
    auto result = std::vector<std::string>{};
    auto ss = std::stringstream{str};

    for (std::string line; std::getline(ss, line, '\n');)
        result.push_back(line);

    return result;
}

namespace slamdar {
namespace radar {
    
std::map<std::string, std::string> parse_return_message(std::string& message)
{
    std::vector<std::string> message_by_line = split_string_by_newline(message);

    std::map<std::string, std::string> output_map;

    for (std::string& line : message_by_line) {

        if (line.length() == 0) { break; }

        // parse key : value pair
        
        // first and last char will be brackets
        line.erase(0, 1);

        // assert that first item in key is in quotes
        assert(line[0] == '\"');

        // find next quote 
        size_t end_key_index = line.find('\"', 1);

        assert(end_key_index != std::string::npos);

        // extract out key
        std::string key = line.substr(1, end_key_index - 1);

        // find value

        // remove starting key characters
        line.erase(0, end_key_index + 2);

        std::string value = line.substr(0, line.length() - 1);

        // if value starts and ends in quotes, remove them
        if (value[0] == '\"') value.erase(0, 1);
        if (value[value.length() - 1] == '\"') value.pop_back();

        output_map[key] = value;
    }

    return output_map;
}

} // namespace radar
} // namespace slamdar
