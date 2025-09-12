# 🐚 Minishell

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C](https://img.shields.io/badge/Language-C-0052CC?style=flat&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Code Style](https://img.shields.io/badge/Code%20Style-42%20Norminette-blue)](https://github.com/42School/norminette)

A minimal shell implementation in C that replicates core functionality of bash, built as part of the 42 curriculum.

## 📋 Table of Contents

- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Built-in Commands](#-built-in-commands)
- [Supported Features](#-supported-features)
- [Testing](#-testing)
- [Project Structure](#-project-structure)

## ✨ Features

- **Interactive Shell**: Full interactive mode with prompt and command history
- **Built-in Commands**: Complete implementation of essential shell commands
- **Environment Variables**: Full support for environment variable expansion
- **Redirections**: Input/output redirection with `<`, `>`, `>>`, and heredoc `<<`
- **Pipes**: Command chaining with `|` operator
- **Signal Handling**: Proper handling of Ctrl+C, Ctrl+D, and Ctrl+\\
- **Quote Handling**: Support for single and double quotes with proper expansion
- **Memory Management**: Careful memory allocation and cleanup
- **Error Handling**: Comprehensive error messages and status codes

## 🚀 Installation

### Prerequisites

- GCC compiler
- Make
- Readline library
- Valgrind (for testing)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/minishell.git
cd minishell

# Compile the project
make

# Run the shell
./minishell
```

### Dependencies

On Ubuntu/Debian:
```bash
sudo apt-get install libreadline-dev valgrind
```

On macOS:
```bash
brew install readline valgrind
```

## 💻 Usage

### Interactive Mode
```bash
./minishell
minishell$ echo "Hello, World!"
Hello, World!
minishell$ ls -la
total 24
drwxr-xr-x  5 user  user  160 Dec 15 10:30 .
drwxr-xr-x  3 user  user   96 Dec 15 10:29 ..
-rw-r--r--  1 user  user 1234 Dec 15 10:30 README.md
minishell$ exit
```

### Non-Interactive Mode
```bash
echo "ls -la" | ./minishell
```

## 🔧 Built-in Commands

| Command | Description | Example |
|---------|-------------|---------|
| `echo` | Print text to stdout | `echo "Hello World"` |
| `cd` | Change directory | `cd /home/user` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variable | `export VAR=value` |
| `unset` | Unset environment variable | `unset VAR` |
| `env` | Print environment variables | `env` |
| `exit` | Exit the shell | `exit 0` |

## 🎯 Supported Features

### Redirections
```bash
# Output redirection
echo "Hello" > file.txt

# Append redirection
echo "World" >> file.txt

# Input redirection
cat < file.txt

# Heredoc
cat << EOF
Line 1
Line 2
EOF
```

### Pipes
```bash
# Simple pipe
ls -la | grep ".c"

# Multiple pipes
echo "hello world" | tr ' ' '\n' | sort
```

### Environment Variables
```bash
# Variable expansion
echo $HOME
echo "Current user: $USER"

# In single quotes (no expansion)
echo '$HOME'
```

### Quotes
```bash
# Single quotes (literal)
echo 'Hello $USER'

# Double quotes (with expansion)
echo "Hello $USER"
```

## 🧪 Testing

The project includes a comprehensive test suite:

```bash
# Run all tests
./test_minishell.sh

# Run specific test categories
./test_minishell.sh builtin    # Test built-in commands
./test_minishell.sh pipes      # Test pipe functionality
./test_minishell.sh leaks      # Test memory leaks with valgrind
```

### Test Categories
- **Compilation**: Build verification
- **Simple Commands**: Basic command execution
- **Built-in Commands**: All built-in functionality
- **Environment Variables**: Variable expansion and management
- **Redirections**: Input/output redirection
- **Pipes**: Command chaining
- **Quotes**: Quote handling and expansion
- **Error Handling**: Error cases and edge conditions
- **Memory Leaks**: Valgrind leak detection

## 📁 Project Structure

```
minishell/
├── srcs/
│   ├── main.c                 # Main entry point
│   ├── signals.c              # Signal handling
│   ├── built_ins/             # Built-in commands
│   │   ├── built_ins.c
│   │   └── exit.c
│   ├── parser/                # Command parsing
│   ├── prompt/                # Prompt management
│   ├── utils/                 # Utility functions
│   └── geral_commands/        # External command execution
├── libft/                     # Custom C library
├── minishell.h                # Main header file
├── Makefile                   # Build configuration
├── test_minishell.sh          # Test suite
├── suppress_readline.supp     # Valgrind suppressions
└── README.md                  # This file
```

## 🏗️ Architecture

The project follows a modular architecture:

- **Main Loop**: Handles input and command execution
- **Parser**: Tokenizes and parses command input
- **Built-ins**: Implements shell built-in commands
- **External Commands**: Executes external programs
- **Signal Handler**: Manages shell signals
- **Memory Manager**: Handles dynamic memory allocation

## 🔍 Code Quality

- **42 Norminette**: Follows 42 coding standards
- **Memory Management**: No memory leaks (verified with Valgrind)
- **Error Handling**: Comprehensive error checking
- **Documentation**: Well-documented code with clear function names

## 🚨 Known Issues

- Heredoc parsing needs improvement
- Some edge cases in quote handling
- File descriptor management could be optimized


## 👨‍💻 Author

**Laher Maciel**
- GitHub: [@LaherMaciel](https://github.com/LaherMaciel)
- 42 Profile: [@lawences](https://profile-v3.intra.42.fr/users/lawences)

## 🙏 Acknowledgments

- 42 School for the project requirements
- The C programming community
- Contributors and testers

---

<div align="center">
  <strong>Made with ❤️ at 42 School</strong>
</div>