#ifndef CLIPARSER_H_INCLUDED
#define CLIPARSER_H_INCLUDED

#define MAX_ARGS 10  // Maximum number of arguments allowed
#define MAX_ARG_LENGTH 50  // Maximum length of each argument
#define MAX_INPUT_LENGTH (MAX_ARGS * (MAX_ARG_LENGTH + 1))  // Maximum length of the entire input string

#include <stdio.h>

// Definition of the ParsedCommand structure
typedef struct
{
    char command[MAX_ARG_LENGTH];        // Holds the command string
    char args[MAX_ARGS][MAX_ARG_LENGTH]; // Holds the arguments as an array of strings
    int numArgs;                         // Holds the number of arguments
} ParsedCommand;

// Definition of the CommandEntry structure
typedef struct
{
    char command[MAX_ARG_LENGTH];          // Holds the command string
    void (*handler)(const ParsedCommand*); // Function pointer to the command handler
} CommandEntry;

// Function to parse input and fill the ParsedCommand structure
int parseInput(const char *input, ParsedCommand *parsedCommand)
{
    int inputIndex = 0;
    int commandIndex = 0;
    int argIndex = 0;

    // Parse the command
    while (input[inputIndex] != ' ' && input[inputIndex] != '\0')
    {
        parsedCommand->command[commandIndex++] = input[inputIndex++];
    }
    parsedCommand->command[commandIndex] = '\0';

    // Parse the arguments
    while (input[inputIndex] != '\0')
    {
        // Skip spaces
        while (input[inputIndex] == ' ')
        {
            inputIndex++;
        }

        // Parse the argument
        commandIndex = 0;
        while (input[inputIndex] != ' ' && input[inputIndex] != '\0')
        {
            parsedCommand->args[argIndex][commandIndex++] = input[inputIndex++];
        }
        parsedCommand->args[argIndex][commandIndex] = '\0';
        argIndex++;

        // Check if the maximum number of arguments is reached
        if (argIndex >= MAX_ARGS)
        {
            return 1; // Return 1 to indicate an error (too many arguments)
        }
    }

    parsedCommand->numArgs = argIndex;

    return 0; // Return 0 to indicate successful parsing
}

// Function to find and execute the command
int executeCommand(const ParsedCommand *parsedCommand, CommandEntry *commandDictionary, size_t dictionarySize)
{
    for (size_t i = 0; i < dictionarySize; ++i)
    {
        if (strcmp(parsedCommand->command, commandDictionary[i].command) == 0)
        {
            commandDictionary[i].handler(parsedCommand);
            return 0; // Return 0 to indicate successful command execution
        }
    }

    return 1; // Return 1 to indicate that the command was not found
}

#endif // CLIPARSER_H_INCLUDED
