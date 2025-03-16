#include <stdio.h>
#include <string.h>
#include "CLIParser.h"

// Example command handlers
void sampleCommandHandler(const ParsedCommand *cmd)
{
    printf("Executing command: %s\n", cmd->command);
    printf("Arguments (%d):\n", cmd->numArgs);
    for (int i = 0; i < cmd->numArgs; i++)
    {
        printf("  Arg %d: %s\n", i + 1, cmd->args[i]);
    }
}

int main()
{
    char input[MAX_INPUT_LENGTH];
    ParsedCommand parsedCommand;

    // Define available commands
    CommandEntry commands[] = {
        {"test", sampleCommandHandler}, // Example command "test"
        {"run", sampleCommandHandler}   // Example command "run"
    };

    size_t commandCount = sizeof(commands) / sizeof(commands[0]);

    // Main loop to accept user input
    while (1)
    {
        printf("\nEnter command: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break; // Exit on input failure
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Parse input
        if (parseInput(input, &parsedCommand) != 0)
        {
            printf("Error: Too many arguments!\n");
            continue;
        }

        // Execute command
        if (executeCommand(&parsedCommand, commands, commandCount) != 0)
        {
            printf("Error: Command not found!\n");
        }
    }

    return 0;
}
