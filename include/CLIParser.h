#ifndef CLIPARSER_H_INCLUDED
#define CLIPARSER_H_INCLUDED

#include <stdio.h>

#define MAX_ARGS 10
#define MAX_ARG_LENGTH 50
#define MAX_INPUT_LENGTH (MAX_ARGS * (MAX_ARG_LENGTH + 1))


typedef struct {
    char command[MAX_ARG_LENGTH];
    char args[MAX_ARGS][MAX_ARG_LENGTH];
    int numArgs;
} ParsedCommand;

// Function to parse input and fill the ParsedCommand structure
int parseInput(const char *input, ParsedCommand *parsedCommand){
    int inputIndex = 0;
    int commandIndex = 0;
    int argIndex = 0;

    // Parse the command
    while (input[inputIndex] != ' ' && input[inputIndex] != '\0') {
        parsedCommand->command[commandIndex++] = input[inputIndex++];
    }
    parsedCommand->command[commandIndex] = '\0';

    // Parse the arguments
    while (input[inputIndex] != '\0') {
        // Skip spaces
        while (input[inputIndex] == ' ') {
            inputIndex++;
        }

        // Parse the argument
        commandIndex = 0;
        while (input[inputIndex] != ' ' && input[inputIndex] != '\0') {
            parsedCommand->args[argIndex][commandIndex++] = input[inputIndex++];
        }
        parsedCommand->args[argIndex][commandIndex] = '\0';
        argIndex++;

        // Check if the maximum number of arguments is reached
        if (argIndex >= MAX_ARGS) {
            return 1;
        }
    }

    parsedCommand->numArgs = argIndex;

    return 0;
}


#endif // CLIPARSER_H_INCLUDED
