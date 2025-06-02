#include "argparser.hpp"
#include <sstream>

void ArgParser::parse(const std::string& input) {
    args.clear();
    options.clear();
    std::istringstream stream(input);
    std::string token;
    while (stream >> token) {
        if (token.rfind("--", 0) == 0) {
            auto pos = token.find('=');
            if (pos != std::string::npos) {
                options[token.substr(2, pos - 2)] = token.substr(pos + 1);
            } else {
                options[token.substr(2)] = "";
            }
        } else if (token.rfind("-", 0) == 0) {
            options[token.substr(1)] = "";
        } else {
            args.push_back(token);
        }
    }
}

const std::vector<std::string>& ArgParser::getArgs() const { return args; }
const std::unordered_map<std::string, std::string>& ArgParser::getOptions() const { return options; }
