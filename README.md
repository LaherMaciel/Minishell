# minishell

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C](https://img.shields.io/badge/Language-C-green)](https://en.wikipedia.org/wiki/C_(programming_language))

> A minimal shell implementation replicating core bash behaviour.

## Overview

`minishell` is a 42 School Rank 3 project, built in collaboration. The goal is to implement a functional interactive shell in C, supporting pipes, redirections, environment variables, signals, and a set of built-in commands.

## Usage

```bash
make
./minishell
```

## Built-in commands

| Command | Description |
|---------|-------------|
| `echo` | Print to stdout (`-n` flag supported) |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Set environment variable |
| `unset` | Unset environment variable |
| `env` | Print environment |
| `exit` | Exit the shell |

## Supported features

- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion: `$VAR`, `$?`
- Single and double quotes with correct expansion rules
- Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- Command history via readline

## Project structure

```
minishell/
├── srcs/
│   ├── main.c
│   ├── signals.c
│   ├── minishell.h
│   ├── built_ins/       # echo, cd, pwd, export, unset, env, exit
│   ├── parser/          # Tokenizer, quote handling, list utils
│   ├── prompt/          # Prompt display, path resolution
│   ├── geral_commands/  # Pipes, redirections, heredoc, execution
│   └── utils/           # Error handling, memory, cleanup
├── libft/
├── Makefile
├── test_minishell.sh    # Test suite
└── suppress_readline.supp
```

## Make targets

| Target | Description |
|--------|-------------|
| `make` | Build the binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Rebuild from scratch |
| `make norm` | Run norminette |
| `make val` | Run with valgrind |
| `make test` | Run the test suite |

## Authors

**Laher Maciel**
- GitHub: [@LaherMaciel](https://github.com/LaherMaciel)
- 42 Login: lawences

**Kayki Rocha**
- GitHub: [@UnderOfAll](https://github.com/UnderOfAll)
- 42 Login: karocha-
