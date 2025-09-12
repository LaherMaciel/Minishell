# Minishell Documentation

## 📚 Technical Documentation

### Architecture Overview

Minishell is built using a modular architecture that separates concerns and makes the code maintainable and extensible.

```
┌─────────────────┐
│   Main Loop     │ ← Entry point and command processing
└─────────┬───────┘
          │
┌─────────▼───────┐
│    Parser       │ ← Command tokenization and parsing
└─────────┬───────┘
          │
┌─────────▼───────┐
│  Command Router │ ← Determines built-in vs external
└─────────┬───────┘
          │
    ┌─────┴─────┐
    │           │
┌───▼───┐   ┌───▼───┐
│Builtin│   │External│
│Commands│   │Commands│
└───────┘   └───────┘
```

### Core Components

#### 1. Main Loop (`main.c`)
- Handles input reading
- Manages the shell lifecycle
- Coordinates between components

#### 2. Parser (`parser/`)
- Tokenizes input strings
- Handles quotes and special characters
- Builds command structures

#### 3. Built-in Commands (`built_ins/`)
- `echo`: Print text with options
- `cd`: Change directory
- `pwd`: Print working directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: List environment variables
- `exit`: Exit the shell

#### 4. External Commands (`geral_commands/`)
- Command execution via `execve`
- PATH resolution
- Process management

#### 5. Signal Handling (`signals.c`)
- Ctrl+C (SIGINT) handling
- Ctrl+D (EOF) handling
- Ctrl+\ (SIGQUIT) handling

### Data Structures

#### `t_mshell` - Main Shell Structure
```c
typedef struct s_mshell {
    char        **env;
    t_export    *export_list;
    t_child_pid *child_pids;
    int         exit_status;
    // ... other fields
} t_mshell;
```

#### `t_export` - Environment Variable
```c
typedef struct s_export {
    char    *name;
    char    *value;
    int     is_exported;
    struct s_export *next;
} t_export;
```

### Memory Management

The project follows strict memory management practices:

1. **Allocation**: Every `malloc` has a corresponding `free`
2. **Error Handling**: Memory allocation failures are handled gracefully
3. **Cleanup**: All resources are freed on exit
4. **Leak Detection**: Valgrind is used to verify no memory leaks

### Error Handling

Comprehensive error handling is implemented throughout:

- **System Errors**: Proper handling of system call failures
- **Memory Errors**: Graceful handling of allocation failures
- **Command Errors**: Clear error messages for invalid commands
- **Syntax Errors**: Proper parsing error reporting

### Testing Strategy

#### Unit Testing
- Individual function testing
- Edge case validation
- Error condition testing

#### Integration Testing
- Command pipeline testing
- Redirection testing
- Environment variable testing

#### Memory Testing
- Valgrind leak detection
- File descriptor leak detection
- Memory corruption detection

### Performance Considerations

1. **Efficient Parsing**: Minimal string operations
2. **Memory Usage**: Careful allocation and deallocation
3. **Process Management**: Efficient child process handling
4. **Signal Handling**: Non-blocking signal processing

### Security Considerations

1. **Input Validation**: All user input is validated
2. **Path Resolution**: Safe PATH handling
3. **Command Execution**: Secure external command execution
4. **Memory Safety**: Buffer overflow prevention

### Code Style

The project follows 42 School's Norminette standards:

- **Line Length**: Maximum 80 characters
- **Function Length**: Maximum 25 lines
- **Variable Naming**: snake_case
- **Function Naming**: Descriptive and clear
- **Comments**: Clear and concise

### Build System

The project uses a custom Makefile with:

- **Modular Compilation**: Separate object files for each module
- **Dependency Management**: Proper header dependencies
- **Clean Targets**: Complete cleanup options
- **Testing Integration**: Built-in test running
- **Valgrind Integration**: Memory leak detection

### Dependencies

- **libft**: Custom C library with utility functions
- **readline**: Line editing and history
- **termcap**: Terminal capabilities

### Future Improvements

1. **Heredoc Parsing**: Improve heredoc implementation
2. **Signal Handling**: Enhanced signal management
3. **Error Messages**: More descriptive error messages
4. **Performance**: Optimize command execution
5. **Features**: Additional built-in commands

### Troubleshooting

#### Common Issues

1. **Compilation Errors**
   - Check readline installation
   - Verify libft compilation
   - Check compiler flags

2. **Runtime Errors**
   - Check PATH environment variable
   - Verify file permissions
   - Check memory allocation

3. **Test Failures**
   - Run individual test categories
   - Check valgrind output
   - Verify expected behavior

#### Debug Tips

1. **Use Valgrind**: Always test with valgrind
2. **Check Logs**: Review error messages carefully
3. **Test Incrementally**: Test small changes
4. **Use GDB**: Debug complex issues with GDB

### Contributing Guidelines

1. **Code Style**: Follow Norminette standards
2. **Testing**: Add tests for new features
3. **Documentation**: Update documentation
4. **Memory**: Ensure no memory leaks
5. **Error Handling**: Handle all error cases
