#include "CLIParser.h"
#include <stdio.h>
#include <string.h>

int parseInput(char *input, ParsedCommand *parsedCommand)
{
    int argIndex = 0;
    int charIndex = 0;
    int insideQuotes = 0;
    int escapeNext = 0;

    // Initialize the parsedCommand structure
    parsedCommand->numArgs = 0;
    memset(parsedCommand->command, 0, MAX_ARG_LENGTH);
    memset(parsedCommand->args, 0, sizeof(parsedCommand->args));

    // Parse the command (first word before a space)
    while (*input != ' ' && *input != '\0')
    {
        parsedCommand->command[charIndex++] = *input++;
    }
    parsedCommand->command[charIndex] = '\0';

    // Parse the arguments
    while (*input != '\0')
    {
        // Skip spaces
        while (*input == ' ')
        {
            input++;
        }

        // If we reach end after skipping spaces, break
        if (*input == '\0')
            break;

        // Start parsing argument
        charIndex = 0;
        insideQuotes = (*input == '"') ? 1 : 0;
        if (insideQuotes)
            input++; // Skip opening quote

        while (*input != '\0' && (insideQuotes || *input != ' '))
        {
            if (*input == '\\' && !escapeNext) // Handle escape character
            {
                escapeNext = 1;
                input++;
                continue;
            }

            if (*input == '"' && !escapeNext) // Handle closing quote
            {
                insideQuotes = 0;
                input++;
                break;
            }

            parsedCommand->args[argIndex][charIndex++] = *input++;
            escapeNext = 0;
        }
        parsedCommand->args[argIndex][charIndex] = '\0';
        argIndex++;

        // Check if the maximum number of arguments is reached
        if (argIndex >= MAX_ARGS)
        {
            return 1; // Error: Too many arguments
        }
    }

    parsedCommand->numArgs = argIndex;
    return 0; // Success
}

int executeCommand(const ParsedCommand *parsedCommand, CommandEntry *commandDictionary, size_t dictionarySize)
{
    for (size_t i = 0; i < dictionarySize; i++)
    {
        if (strcmp(parsedCommand->command, commandDictionary[i].command) == 0)
        {
            commandDictionary[i].handler(parsedCommand);
            return 0; // Command executed successfully
        }
    }

    printf("Error: Command '%s' not found!\n", parsedCommand->command);
    return 1; // Command not found
}
