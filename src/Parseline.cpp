#include "Parseline.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void Parseline::addCommand(const std::string& pattern,
                           const std::string& help_text,
                           std::function<void(const ArgParser&)> handler) {
    command_handlers.push_back({std::regex("^" + pattern + "$"), pattern, handler});
    help.add(pattern, help_text);
    suggester.addCommand(pattern);
}

void Parseline::startREPL(const std::string& prompt) {
    std::string input_line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input_line)) break;

        history.add(input_line);
        if (input_line == "exit") break;

        auto commands = splitPipe(input_line);
        for (const auto& command_str : commands) {
            parser.parse(command_str);
            const auto& args = parser.getArgs();
            if (args.empty()) continue;

            const std::string& command = args[0];
            bool matched = false;
            for (const auto& entry : command_handlers) {
                if (std::regex_match(command, entry.pattern)) {
                    entry.handler(parser);
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                std::cout << "Unknown command: " << command << "\n";
                suggester.suggest(command);
            }
        }
    }
}

void Parseline::showHelp(const std::string& pattern) const {
    help.show(pattern);
}

void Parseline::showHistory() const {
    history.show();
}

std::vector<std::string> Parseline::splitPipe(const std::string& line) {
    std::vector<std::string> parts;
    std::string part;
    std::istringstream stream(line);
    while (std::getline(stream, part, '|')) {
        parts.push_back(trim(part));
    }
    return parts;
}

std::string Parseline::trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}
