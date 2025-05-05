#ifndef PARSELINE_H
#define PARSELINE_H

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <iostream>
#include <sstream>

struct Command {
    std::string name;
    std::string description;
    std::function<void(const std::vector<std::string>&)> action; // Function that runs when command is executed
};

class CommandRegistry {
private:
    std::unordered_map<std::string, Command> commands;

public:
    void register_command(const Command& cmd);

    bool execute_command(const std::string& input_line);

    void print_help() const;
};

void run_repl(CommandRegistry& registry);

#endif // PARSELINE_H
