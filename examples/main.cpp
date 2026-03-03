#include <iostream>
#include <parseline/parseline.h>

int main() {

    Parseline::Parseline parseline;

    parseline.addCommand(Parseline::Command("help", "print help"));

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        parseline.Parse(line);
    }

    return 0;
}