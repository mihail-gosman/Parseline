# CLIParser

CLIParser is a lightweight command-line argument parser for C programs. It processes user input, extracts commands and arguments, and executes predefined command handlers.

## Features
- Parses commands and arguments from user input.
- Supports quoted arguments (e.g., `"argument with spaces"`).
- Handles escape sequences (e.g., `\"` for quotes inside arguments).
- Matches commands with a predefined list.
- Executes registered command handlers.

## Installation
Clone the repository:
```sh
git clone https://github.com/yourusername/CLIParser.git
cd CLIParser
```

## Usage
### 1. Include the Header File
Include `CLIParser.h` in your project:
```c
#include "CLIParser.h"
```

### 2. Define Command Handlers
Implement functions to handle specific commands:
```c
void sampleCommandHandler(const ParsedCommand *cmd)
{
    printf("Executing command: %s\n", cmd->command);
    for (int i = 0; i < cmd->numArgs; i++)
    {
        printf("Arg %d: %s\n", i + 1, cmd->args[i]);
    }
}
```

### 3. Initialize Commands in `example.c`
```c
#include "CLIParser.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char input[MAX_INPUT_LENGTH];
    ParsedCommand parsedCommand;
    CommandEntry commands[] = {
        {"test", sampleCommandHandler},
        {"run", sampleCommandHandler}
    };
    size_t commandCount = sizeof(commands) / sizeof(commands[0]);

    while (1)
    {
        printf("\nEnter command: ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;

        if (parseInput(input, &parsedCommand) != 0)
        {
            printf("Error: Too many arguments!\n");
            continue;
        }
        if (executeCommand(&parsedCommand, commands, commandCount) != 0)
        {
            printf("Error: Command not found!\n");
        }
    }
    return 0;
}
```

### 4. Compile and Run
```sh
gcc example.c CLIParser.c -o cli_parser
./cli_parser
```

## License
This project is licensed under the MIT License.

