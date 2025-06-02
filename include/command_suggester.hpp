#ifndef COMMAND_SUGGESTER_HPP
#define COMMAND_SUGGESTER_HPP

#include <vector>
#include <string>

class CommandSuggester {
public:
    void addCommand(const std::string& name);
    void suggest(const std::string& input) const;

private:
    std::vector<std::string> commands;
};

#endif
