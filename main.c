#include <stdio.h>
#include <stdlib.h>
#include "CLIParser.h"

int main() {
    char input[] = "<test input lol 2131>";
    ParsedCommand parsedCommand;



    parseInput(input, &parsedCommand);


    printf("Command: %s\n", parsedCommand.command);
    printf("Arguments (%d):\n", parsedCommand.numArgs);
    for (int i = 0; i < parsedCommand.numArgs; i++) {
        printf("  %d: %s\n", i + 1, parsedCommand.args[i]);
    }

    return 0;
}
