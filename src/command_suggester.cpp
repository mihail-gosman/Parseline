#include "command_suggester.hpp"
#include <iostream>

void CommandSuggester::addCommand(const std::string& name) {
    commands.push_back(name);
}

void CommandSuggester::suggest(const std::string& input) const {
    for (const auto& cmd : commands) {
        if (cmd.find(input) == 0) {
            std::cout << "Did you mean: " << cmd << "?\n";
        }
    }
}
