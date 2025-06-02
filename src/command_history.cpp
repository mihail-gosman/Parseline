#include "command_history.hpp"
#include <iostream>

void CommandHistory::add(const std::string& command) {
    if (!command.empty()) {
        history.push_back(command);
    }
}

void CommandHistory::show() const {
    for (const auto& cmd : history) {
        std::cout << cmd << "\n";
    }
}
