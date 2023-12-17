#include <stdio.h>
#include <stdlib.h>
#include "CLIParser.h"


// Forward declarations of command handlers
void helpCommandHandler(const ParsedCommand *command);
void printCommandHandler(const ParsedCommand *command);
void exitCommandHandler(const ParsedCommand *command);

// Command dictionary
CommandEntry commandDictionary[] = {
    {"help", helpCommandHandler},
    {"print", printCommandHandler},
    {"exit", exitCommandHandler},
    // Add more entries as needed
};

// Command handlers
void helpCommandHandler(const ParsedCommand *command)
{
    printf("Help command executed\n");
    // Add your help command logic here
}

void printCommandHandler(const ParsedCommand *command)
{
     printf("Print command executed\n");
    // Add your print command logic here
}

void exitCommandHandler(const ParsedCommand *command)
{
    printf("Exit command executed\n");
    // Add your exit command logic here
}

int main()
{
    char input[MAX_INPUT_LENGTH];

    while (1)
    {
        // Get input from the user
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove the newline character from input

        // Parse the input
        ParsedCommand parsedCommand;
        if (parseInput(input, &parsedCommand) != 0)
        {
            printf("Error parsing input\n");
            continue;
        }

        // Find and execute the command using the external function
        if (executeCommand(&parsedCommand, commandDictionary, sizeof(commandDictionary) / sizeof(commandDictionary[0])) != 0)
        {
            printf("Command not found: %s\n", parsedCommand.command);
        }
    }

    return 0;
}
