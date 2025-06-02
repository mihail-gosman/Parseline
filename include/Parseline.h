#ifndef PARSELINE_HPP
#define PARSELINE_HPP

#include "argparser.hpp"
#include "command_history.hpp"
#include "command_help.hpp"
#include "command_suggester.hpp"
#include <functional>
#include <regex>
#include <string>
#include <vector>

class Parseline {
public:
    void addCommand(const std::string& pattern,
                    const std::string& help_text,
                    std::function<void(const ArgParser&)> handler);

    void startREPL(const std::string& prompt = ">>> ");
    void showHelp(const std::string& pattern = "") const;
    void showHistory() const;

private:
    struct CommandEntry {
        std::regex pattern;
        std::string raw_pattern;
        std::function<void(const ArgParser&)> handler;
    };

    std::vector<CommandEntry> command_handlers;
    CommandHistory history;
    CommandHelp help;
    CommandSuggester suggester;
    ArgParser parser;

    std::vector<std::string> splitPipe(const std::string& line);
    static std::string trim(const std::string& s);
};

#endif
