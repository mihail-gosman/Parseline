#include "parseline.h"

void CommandRegistry::register_command(const Command& cmd) {
    commands[cmd.name] = cmd;
}

bool CommandRegistry::execute_command(const std::string& input_line) {
    std::istringstream iss(input_line);
    std::string cmd_name;
    iss >> cmd_name;

    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    auto it = commands.find(cmd_name);
    if (it != commands.end()) {
        it->second.action(args);
        return true;
    } else {
        std::cerr << "Unknown command: " << cmd_name << "\n";
        return false;
    }
}

void CommandRegistry::print_help() const {
    std::cout << "Available commands:\n";
    for (const auto& [name, cmd] : commands) {
        std::cout << "  " << name << " - " << cmd.description << "\n";
    }
}

void run_repl(CommandRegistry& registry) {
    std::string line;
    std::cout << "Welcome to the command line. Type 'help' or 'exit'.\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line == "exit") break;
        if (line == "help") {
            registry.print_help();
        } else {
            registry.execute_command(line);
        }
    }
}
