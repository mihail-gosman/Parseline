#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <string>
#include <vector>
#include <unordered_map>

class ArgParser {
public:
    void parse(const std::string& input);
    const std::vector<std::string>& getArgs() const;
    const std::unordered_map<std::string, std::string>& getOptions() const;

private:
    std::vector<std::string> args;
    std::unordered_map<std::string, std::string> options;
};

#endif
