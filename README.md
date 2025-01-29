# Infinity Compiler Project

This project implements a compiler for an imaginary programming language called **Infinity**. The compiler is written in **C** and consists of three main components:

- **Reader**: Reads the source code written in Infinity language.
- **Parser**: Parses the source code and checks for syntax errors.
- **Scanner**: Scans the source code and tokenizes it into recognizable components.

## Features

- **Compiler written in C** for the Infinity programming language.
- Includes a **Reader**, **Parser**, and **Scanner** to process Infinity source code.
- Supports running the Infinity programs using the command-line argument.

## Requirements

To run this project, you will need:

- **C Compiler** (GCC recommended)
- **Makefile** (for easy compilation)
  
## Installation

To download and set up the compiler, follow these steps:

1. Clone this repository to your local machine:
    ```bash
    git clone https://github.com/yourusername/infinity-compiler.git
    cd infinity-compiler
    ```

2. Compile the project:
    ```bash
    make
    ```

## Running the Compiler

After a successful build, you will have an executable file (e.g., `compiler.exe`). To run the compiler, use the following command:

```bash
./compiler.exe p Input_Hello.inf
