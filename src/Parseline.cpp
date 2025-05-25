#include "Parseline.h"

CommandPattern::CommandPattern(std::string regexPattern,
                             std::string description,
                             Callback callback)
    : _regexPattern(std::move(regexPattern)),
      _description(std::move(description)),
      _callback(std::move(callback)),
      _regex(_regexPattern)
{}

bool CommandPattern::matches(const std::string& input, std::vector<std::string>& extractedArgs) const
{
    std::smatch matchResults;
    if (std::regex_match(input, matchResults, _regex))
    {
        extractedArgs.clear();
        for (size_t i = 1; i < matchResults.size(); ++i)
        {
            extractedArgs.push_back(matchResults[i].str());
        }
        return true;
    }
    return false;
}

void CommandPattern::execute(const std::vector<std::string>& args) const
{
    _callback(args);
}

const std::string& CommandPattern::getDescription() const
{
    return _description;
}

const std::string& CommandPattern::getRegexPattern() const
{
    return _regexPattern;
}

void CommandDispatcher::registerCommand(const CommandPattern& command)
{
    _commands.push_back(command);
}

bool CommandDispatcher::dispatch(const std::string& input)
{
    for (const auto& cmd : _commands)
    {
        std::vector<std::string> args;
        if (cmd.matches(input, args))
        {
            cmd.execute(args);
            return true;
        }
    }
    std::cerr << "Error: Unrecognized command: '" << input << "'\n";
    return false;
}

void CommandDispatcher::printHelp() const
{
    std::cout << "Available commands:\n";
    for (const auto& cmd : _commands)
    {
        std::cout << "  Pattern: " << cmd.getRegexPattern() << "\n"
                  << "  Description: " << cmd.getDescription() << "\n\n";
    }
}

CommandREPL::CommandREPL(CommandDispatcher& dispatcher, std::string prompt)
    : _dispatcher(dispatcher), _prompt(std::move(prompt))
{}

void CommandREPL::run()
{
    std::string inputLine;
    while (true)
    {
        std::cout << _prompt;
        if (!std::getline(std::cin, inputLine))
            break;

        if (!_dispatcher.dispatch(inputLine))
            std::cout << "Try 'help' for a list of commands.\n";
    }
}
