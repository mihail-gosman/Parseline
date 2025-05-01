#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <sstream>

// Structură pentru o comandă
struct Command {
    std::string name;
    std::string description;
    std::function<void(const std::vector<std::string>&)> action;
};

// Registru de comenzi
class CommandRegistry {
private:
    std::unordered_map<std::string, Command> commands;

public:
    void register_command(const Command& cmd) {
        commands[cmd.name] = cmd;
    }

    bool execute_command(const std::string& input_line) {
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
            try {
                it->second.action(args);
            } catch (const std::exception& e) {
                std::cerr << "Eroare la execuție: " << e.what() << "\n";
            }
            return true;
        } else {
            std::cerr << "Comandă necunoscută: " << cmd_name << "\n";
            return false;
        }
    }

    void print_help() const {
        std::cout << "Comenzi disponibile:\n";
        for (const auto& [name, cmd] : commands) {
            std::cout << "  " << name << " - " << cmd.description << "\n";
        }
    }
};

// Funcție REPL
void run_repl(CommandRegistry& registry, std::istream& in, std::ostream& out) {
    std::string line;
    while (out << "> ", std::getline(in, line)) {
        if (line == "exit" || line == "quit") break;
        if (line == "help") {
            registry.print_help();
        } else {
            registry.execute_command(line);
        }
    }
}

// Funcție main
int main(int argc, char* argv[]) {
    CommandRegistry registry;

    registry.register_command({
        "hello", "Afișează un mesaj de salut",
        [](const std::vector<std::string>&) {
            std::cout << "Salut! Aceasta este Parseline.\n";
        }
    });

    registry.register_command({
        "add", "Adună două numere: add 2 3",
        [](const std::vector<std::string>& args) {
            if (args.size() < 2) {
                std::cerr << "Folosire: add <num1> <num2>\n";
                return;
            }
            int a = std::stoi(args[0]);
            int b = std::stoi(args[1]);
            std::cout << "Suma este: " << (a + b) << "\n";
        }
    });

    if (argc > 1) {
        std::string cmd_line;
        for (int i = 1; i < argc; ++i) {
            cmd_line += argv[i];
            if (i < argc - 1) cmd_line += " ";
        }
        registry.execute_command(cmd_line);
    } else {
        run_repl(registry, std::cin, std::cout);
    }

    return 0;
}
