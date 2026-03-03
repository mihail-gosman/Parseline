//
// Created by mgosman on 3/3/26.
//

#ifndef PARSELINE_PARSELINE_H
#define PARSELINE_PARSELINE_H
#include <string>
#include <utility>
#include <vector>

namespace Parseline {
    class Command {
    public:
        Command(std::string name, std::string description) : m_name(std::move(name)), m_description(std::move(description)) {};

    private:
        std::string m_name;
        std::string m_description;
    };

    class Parseline {
    public:
        Parseline();
        void Parse(std::string line);
        void addCommand(Command command);
    private:
        std::vector<Command> commands;
    };


}

#endif //PARSELINE_PARSELINE_H