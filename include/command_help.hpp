#ifndef COMMAND_HELP_HPP
#define COMMAND_HELP_HPP

#include <string>
#include <unordered_map>

class CommandHelp {
public:
    void add(const std::string& pattern, const std::string& help_text);
    void show(const std::string& pattern = "") const;

private:
    std::unordered_map<std::string, std::string> help_messages;
};

#endif
