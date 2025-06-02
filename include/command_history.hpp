#ifndef COMMAND_HISTORY_HPP
#define COMMAND_HISTORY_HPP

#include <string>
#include <vector>

class CommandHistory {
public:
    void add(const std::string& command);
    void show() const;

private:
    std::vector<std::string> history;
};

#endif
