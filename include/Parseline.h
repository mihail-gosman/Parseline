#ifndef PARSELINE_H
#define PARSELINE_H

#include <string>
#include <vector>
#include <functional>
#include <regex>
#include <iostream>

class CommandPattern
{
public:
    using Callback = std::function<void(const std::vector<std::string>& args)>;

    CommandPattern(std::string regexPattern,
                   std::string description,
                   Callback callback);

    bool matches(const std::string& input, std::vector<std::string>& extractedArgs) const;

    void execute(const std::vector<std::string>& args) const;

    const std::string& getDescription() const;
    const std::string& getRegexPattern() const;

private:
    std::string _regexPattern;
    std::string _description;
    Callback _callback;
    std::regex _regex;
};

class CommandDispatcher
{
public:
    void registerCommand(const CommandPattern& command);

    bool dispatch(const std::string& input);

    void printHelp() const;

private:
    std::vector<CommandPattern> _commands;
};

class CommandREPL
{
public:
    CommandREPL(CommandDispatcher& dispatcher,
                std::string prompt = "> ");

    void run();

private:
    CommandDispatcher& _dispatcher;
    std::string _prompt;
};

#endif // PARSELINE_H
