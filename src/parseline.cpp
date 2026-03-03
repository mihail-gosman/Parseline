#include <iostream>
#include <ostream>
#include <parseline/parseline.h>

namespace Parseline {
    Parseline::Parseline() {}

    void Parseline::addCommand(Command command) {
        commands.push_back(command);
    }
    void Parseline::Parse(std::string line) {
        if (line.empty()) {
            std::cerr << "Empty line\n";
        } else {
            std::string buffer;
            std::string command;
            std::vector<std::string> arguments;

            bool is_command = true;

            for (auto &ch : line) {
                if (ch == ' ') {
                    if (buffer.empty()) continue;

                    if (is_command) {
                        command = buffer;
                        is_command = false;
                    } else {
                        arguments.push_back(buffer);
                    }
                    buffer.clear();
                } else {
                    buffer += ch;
                }
            }

            if (!buffer.empty()) {
                if (is_command) {
                    command = buffer;
                } else {
                    arguments.push_back(buffer);
                }
            }
            std::cout << "Command: " << command << std::endl;
            std::cout << "Arguments: ";
            for (auto &arg : arguments) { std::cout << arg << ' '; }
        }
    }
}