#ifndef CLIPARSER_H_INCLUDED
#define CLIPARSER_H_INCLUDED

#include <stdio.h>

#define MAX_ARGS 10            // Maximum number of arguments allowed
#define MAX_ARG_LENGTH 50      // Maximum length of each argument
#define MAX_INPUT_LENGTH 512   // Maximum length of the entire input string

// Structure for parsed command
typedef struct
{
    char command[MAX_ARG_LENGTH];        // Holds the command string
    char args[MAX_ARGS][MAX_ARG_LENGTH]; // Holds arguments as an array of strings
    int numArgs;                         // Number of arguments
} ParsedCommand;

// Structure for command entry (command mapping)
typedef struct
{
    char command[MAX_ARG_LENGTH];          // Holds the command name
    void (*handler)(const ParsedCommand*); // Function pointer for command execution
} CommandEntry;

// Function prototypes
int parseInput(char *input, ParsedCommand *parsedCommand);
int executeCommand(const ParsedCommand *parsedCommand, CommandEntry *commandDictionary, size_t dictionarySize);

#endif // CLIPARSER_H_INCLUDED
