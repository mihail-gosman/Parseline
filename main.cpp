#include <iostream>
#include <string>
#include <cstdio>

class Command {
public:
    std::string name;
    std::string description;

    Command(const std::string& n, const std::string& d) : name(n), description(d) {}
    virtual void execute(const std::string& args) = 0;
    virtual ~Command() {}
};

class GreetCommand : public Command {
public:
    GreetCommand() : Command("greet", "Greets the user") {}

    void execute(const std::string& args) override {
        if (!args.empty())
            std::cout << "Hello, " << args << "!\n";
        else
            std::cout << "Hello!\n";
    }
};

class AddCommand : public Command {
public:
    AddCommand() : Command("add", "Adds two numbers") {}

    void execute(const std::string& args) override {
        int a = 0, b = 0;
        if (std::sscanf(args.c_str(), "%d %d", &a, &b) == 2)
            std::cout << "Sum: " << (a + b) << "\n";
        else
            std::cout << "Usage: add <num1> <num2>\n";
    }
};

class SimpleCLI {
public:
    Command* commands[2];

    SimpleCLI() {
        commands[0] = new GreetCommand();
        commands[1] = new AddCommand();
    }

    ~SimpleCLI() {
        delete commands[0];
        delete commands[1];
    }

    void run() {
        std::string line;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, line);
            if (line == "exit") break;
            if (line == "help") {
                printHelp();
                continue;
            }

            std::string cmd, args;
            size_t space = line.find(' ');
            if (space != std::string::npos) {
                cmd = line.substr(0, space);
                args = line.substr(space + 1);
            } else {
                cmd = line;
            }

            bool found = false;
            for (int i = 0; i < 2; ++i) {
                if (commands[i]->name == cmd) {
                    commands[i]->execute(args);
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "Unknown command: " << cmd << "\n";
        }
    }

    void printHelp() {
        std::cout << "Available commands:\n";
        for (int i = 0; i < 2; ++i)
            std::cout << "  " << commands[i]->name << " - " << commands[i]->description << "\n";
        std::cout << "  help - Show this message\n";
        std::cout << "  exit - Exit the CLI\n";
    }
};

int main() {
    SimpleCLI cli;
    cli.run();
    return 0;
}
