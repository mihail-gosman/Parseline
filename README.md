# CLIParser

CLIParser is a simple C library for parsing command-line input. It provides a header file, `CLIParser.h`, that defines structures and functions for parsing and handling command-line input in a modular way.

## Features

- Parse command strings into a structured format.
- Define command handlers for easy extensibility.
- Simple and lightweight design.

## Usage

1. **Clone the repository:**

    ```bash
    git clone https://github.com/yourusername/CLIParser.git
    ```

2. **Include `CLIParser.h` in your C source code:**

    ```c
    #include "CLIParser.h"
    ```

3. **Define command handlers and create a command dictionary:**

    ```c
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
    ```

4. **Implement your command handlers:**

    ```c
    // Command handlers
    void helpCommandHandler(const ParsedCommand *command) {
        // Your help command logic here
    }

    void printCommandHandler(const ParsedCommand *command) {
        // Your print command logic here
    }

    void exitCommandHandler(const ParsedCommand *command) {
        // Your exit command logic here
    }
    ```

5. **Use the library in your main loop:**

    ```c
    int main() {
        // Your main code here

        while (1) {
            // Get input from the user and parse it
            // ...

            // Find and execute the command
            if (executeCommand(&parsedCommand, commandDictionary, sizeof(commandDictionary) / sizeof(commandDictionary[0])) != 0) {
                printf("Command not found: %s\n", parsedCommand.command);
            }
        }

        return 0;
    }
    ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by [your-inspiration](https://github.com/your-inspiration)'s awesome projects.
