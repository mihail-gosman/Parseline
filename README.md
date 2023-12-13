# CLIParser - Command Line Parser Library

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Description

CLIParser is a simple C library for parsing command-line input. It provides functionality to parse commands and their arguments, offering a convenient way to extract information from user input.

## Features

- Parses commands and their arguments from user input.
- Supports a maximum number of arguments per command.
- Provides a clear structure for storing parsed command information.

## Table of Contents

- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Include in Your Project](#include-in-your-project)
  - [Examples](#examples)
- [License](#license)

## Getting Started

### Prerequisites

Make sure you have a C compiler installed on your system.

### Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/mihail-gosman/CLIParser.git
```

## Usage

### Include in your project
```c
#include "CLIParser.h"
```

### Examples
Here is a simple example demonstrating how to use CLIParser to parse a command:
```c
#include "CLIParser.h"
#include <stdio.h>

int main() {
    char input[MAX_INPUT_LENGTH];
    ParsedCommand parsedCommand;

    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);

    // Remove the newline character at the end of the input
    input[strcspn(input, "\n")] = '\0';

    parseInput(input, &parsedCommand);

    // Display parsed command and arguments
    printf("Command: %s\n", parsedCommand.command);
    printf("Arguments (%d):\n", parsedCommand.numArgs);
    for (int i = 0; i < parsedCommand.numArgs; i++) {
        printf("  %d: %s\n", i + 1, parsedCommand.args[i]);
    }

    return 0;
}
```
## Licence
This project is licensed under the MIT License - see the LICENSE file for details.
