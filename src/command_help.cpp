#include "command_help.hpp"
#include <iostream>

void CommandHelp::add(const std::string& pattern, const std::string& help_text) {
    help_messages[pattern] = help_text;
}

void CommandHelp::show(const std::string& pattern) const {
    if (pattern.empty()) {
        std::cout << "Available commands:\n";
        for (const auto& [cmd, help] : help_messages) {
            std::cout << "  " << cmd << " - " << help << "\n";
        }
    } else if (help_messages.count(pattern)) {
        std::cout << pattern << " - " << help_messages.at(pattern) << "\n";
    } else {
        std::cout << "No help available for '" << pattern << "'\n";
    }
}
