# Minishell

Welcome to the Minishell project, part of the curriculum at School 42. This project is a collaborative effort aimed at building a simple shell from scratch, implementing key features of a Unix-like command-line interface.

## Team

- **Lexing, Parsing, and Execution:** Hussien Kanaan
- **Builtin Commands:** Mohammad Assi

## Overview

Minishell is designed to replicate the functionalities of a basic shell. It reads input from the user, parses and executes commands, and handles built-in functions. The project is structured to ensure modularity and clarity in code.

## Features

- **Lexing and Parsing:** The shell uses a lexer to tokenize input commands and a parser to build an Abstract Syntax Tree (AST) for command execution.
- **Execution:** Commands are executed based on the parsed AST, allowing for efficient handling of complex command sequences.
- **Builtin Commands:** A set of built-in commands is implemented to handle common shell tasks like `cd`, `echo`, `exit`, and more.

## Implementation Details

### Lexing and Parsing

The lexer is responsible for converting the input string into a list of tokens. These tokens are then fed into the parser, which constructs an Abstract Syntax Tree (AST). The AST is used to represent the hierarchical structure of commands and their arguments, facilitating efficient execution.

### Execution

Commands are executed by traversing the AST. This approach allows the shell to handle nested commands and complex pipelines effectively.

### Builtin Commands

Builtin commands are handled separately to optimize performance and ensure the shell can handle essential operations internally.

## Getting Started

To build and run the Minishell, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/hussienK/minishell.git
   cd minishell
2. Build the project:
   ```sh
   make
3. Run the shell:
   ```sh
   ./minishell

## Usage

Once the shell is running, you can enter commands just like you would in a standard Unix shell. The shell supports:

- Running executable files from the PATH
- Piping (|)
- Input and output redirection (<, >, >>)
- Builtin commands (cd, echo, exit, etc.)

## Contribution

Contributions are welcome! If you have suggestions or improvements, feel free to open an issue or submit a pull request.
