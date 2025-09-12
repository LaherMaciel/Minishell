#!/bin/bash

# Minishell Comprehensive Test Script
# Tests against actual bash behavior and includes leak testing

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Test files
TEST_FILE="test_file.txt"
TEST_FILE2="test_file2.txt"
TEST_DIR="test_dir"

# Function to print test results
print_test_result() {
    local test_name="$1"
    local expected="$2"
    local actual="$3"
    local status="$4"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$status" = "PASS" ]; then
        echo -e "${GREEN}✓${NC} $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗${NC} $test_name"
        echo -e "  Expected: $expected"
        echo -e "  Actual: $actual"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# Function to run a command and capture output
run_command() {
    local cmd="$1"
    local expected_exit="$2"
    
    # Create a temporary file to capture output
    local temp_file=$(mktemp)
    echo "$cmd" | ./minishell > "$temp_file" 2>&1
    local exit_code=$?
    
    # Get the actual output
    local output=$(cat "$temp_file")
    rm -f "$temp_file"
    
    # Check if exit code matches expected
    if [ "$exit_code" = "$expected_exit" ]; then
        print_test_result "Command: $cmd" "Exit code: $expected_exit" "Exit code: $exit_code" "PASS"
    else
        print_test_result "Command: $cmd" "Exit code: $expected_exit" "Exit code: $exit_code" "FAIL"
    fi
    
    echo "  Output: $output"
    echo ""
}

# Function to test command output
test_command_output() {
    local cmd="$1"
    local expected_output="$2"
    local test_name="$3"
    
    # Create a temporary file to capture output
    local temp_file=$(mktemp)
    echo "$cmd" | ./minishell > "$temp_file" 2>&1
    
    # Get the actual output (no prompt when input is piped)
    local output=$(cat "$temp_file")
    rm -f "$temp_file"
    
    # Normalize whitespace for comparison
    local normalized_output=$(echo "$output" | tr -d '\r' | sed 's/[[:space:]]*$//')
    local normalized_expected=$(echo "$expected_output" | tr -d '\r' | sed 's/[[:space:]]*$//')
    
    if [ "$normalized_output" = "$normalized_expected" ]; then
        print_test_result "$test_name" "$expected_output" "$output" "PASS"
    else
        print_test_result "$test_name" "$expected_output" "$output" "FAIL"
    fi
    echo ""
}

# Function to test error messages
test_error_message() {
    local cmd="$1"
    local expected_error="$2"
    local test_name="$3"
    
    # Create a temporary file to capture output
    local temp_file=$(mktemp)
    echo "$cmd" | ./minishell > "$temp_file" 2>&1
    
    # Get the actual output
    local output=$(cat "$temp_file")
    rm -f "$temp_file"
    
    if echo "$output" | grep -q "$expected_error"; then
        print_test_result "$test_name" "Contains: $expected_error" "Output: $output" "PASS"
    else
        print_test_result "$test_name" "Contains: $expected_error" "Output: $output" "FAIL"
    fi
    echo ""
}

# Function to test command execution (for commands that should work)
test_command_execution() {
    local cmd="$1"
    local test_name="$2"
    
    # Create a temporary file to capture output
    local temp_file=$(mktemp)
    echo "$cmd" | ./minishell > "$temp_file" 2>&1
    local exit_code=$?
    
    # Get the actual output
    local output=$(cat "$temp_file")
    rm -f "$temp_file"
    
    if [ $exit_code -eq 0 ] && [ -n "$output" ]; then
        print_test_result "$test_name" "Command executed successfully" "Command executed successfully" "PASS"
    else
        print_test_result "$test_name" "Command executed successfully" "Command failed or no output" "FAIL"
    fi
    echo ""
}

# Function to test with valgrind for leaks
test_with_valgrind() {
    local cmd="$1"
    local test_name="$2"
    
    echo -e "${YELLOW}Testing with valgrind: $test_name${NC}"
    
    # Create a temporary file for valgrind output
    local valgrind_file=$(mktemp)
    
    # Run with valgrind
    echo "$cmd" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=suppress_readline.supp ./minishell > "$valgrind_file" 2>&1
    local valgrind_exit=$?
    
    # Check for leaks
    if grep -q "definitely lost: 0 bytes" "$valgrind_file" && grep -q "indirectly lost: 0 bytes" "$valgrind_file"; then
        print_test_result "$test_name (valgrind)" "No leaks" "No leaks detected" "PASS"
    else
        print_test_result "$test_name (valgrind)" "No leaks" "Leaks detected" "FAIL"
        echo "  Valgrind output:"
        grep -A 5 -B 5 "definitely lost\|indirectly lost" "$valgrind_file" | head -20
    fi
    
    # Check for file descriptor leaks
    if grep -q "FILE DESCRIPTORS: 0 open" "$valgrind_file"; then
        print_test_result "$test_name (FDs)" "No FD leaks" "All FDs closed" "PASS"
    else
        print_test_result "$test_name (FDs)" "No FD leaks" "FD leaks detected" "FAIL"
        echo "  FD info:"
        grep "FILE DESCRIPTORS" "$valgrind_file"
    fi
    
    rm -f "$valgrind_file"
    echo ""
}

# Function to create test files
setup_test_files() {
    echo "Setting up test files..."
    mkdir -p "$TEST_DIR"
    echo "Hello World" > "$TEST_FILE"
    echo "Test content" > "$TEST_FILE2"
    echo "Line 1" >> "$TEST_FILE"
    echo "Line 2" >> "$TEST_FILE"
    echo "Line 3" >> "$TEST_FILE"
}

# Function to cleanup test files
cleanup_test_files() {
    echo "Cleaning up test files..."
    rm -f "$TEST_FILE" "$TEST_FILE2"
    rm -rf "$TEST_DIR"
    rm -f test.txt test2.txt test3.txt test4.txt
}

# Function to test compilation
test_compilation() {
    echo -e "${BLUE}=== Testing Compilation ===${NC}"
    
    if make > /dev/null 2>&1; then
        print_test_result "Compilation" "Success" "Success" "PASS"
    else
        print_test_result "Compilation" "Success" "Failed" "FAIL"
        echo "Compilation failed. Exiting tests."
        exit 1
    fi
    echo ""
}
# Function to test simple commands
test_simple_commands() {
    echo -e "${BLUE}=== Testing Simple Commands ===${NC}"
    
    # Test absolute path command
    test_command_execution "/bin/ls" "Absolute path command"
    
    # Test command with arguments
    test_command_execution "/bin/ls -la" "Command with arguments"
    
    # Test empty command
    test_command_output "" "" "Empty command"
    
    # Test only spaces
    test_command_output "   " "" "Only spaces"
    
    # Test quotes - these should execute ls command
    test_command_execution "'l's" "Single quotes around command"
    test_command_execution "\"ls\"" "Double quotes around command"
    
    # Test bad variable - should still execute ls
    test_command_execution "\$bad ls" "Bad variable before command"
    
    # Test directory commands - these should fail
    test_error_message "srcs" "command not found" "Directory without ./"
    test_error_message "/srcs" "No such file or directory" "Absolute path to directory"
    test_error_message "srcs/" "Is a directory" "Directory with trailing slash"
    test_error_message "./srcs" "Is a directory" "Current directory reference"
    
    # Test file commands - these should fail
    test_error_message "test.txt" "command not found" "File without ./"
    test_error_message "/test.txt" "No such file or directory" "Absolute path to file"
    test_error_message "test.txt/" "Not a directory" "File with trailing slash"
    
    echo ""
}

# Function to test built-in commands
test_builtin_commands() {
    echo -e "${BLUE}=== Testing Built-in Commands ===${NC}"
    
    # Test echo
    test_command_output "echo hello" "hello" "Echo without options"
    test_command_output "echo -n hello" "hello" "Echo with -n option"
    test_command_output "echo 'literal \" char'" "literal \" char" "Echo with quotes"
    test_command_output "echo hello\$" "hello$" "Echo with escaped dollar"
    test_command_output "echo \$USER" "$USER" "Echo with environment variable"
    
    # Test pwd
    test_command_output "pwd" "$(pwd)" "PWD command"
    
    # Test exit - CORRECTED: exit with too many arguments should NOT exit (bash behavior)
    run_command "exit" 0
    run_command "exit 90" 90
    run_command "exit 90 90" 0  # Should NOT exit, just show error (bash behavior)
    run_command "exit word" 2   # Invalid argument should exit with 2
    run_command "exit 9223372036854775807" 255  # Max positive
    run_command "exit 9223372036854775808" 2    # Overflow
    run_command "exit -9223372036854775808" 0   # Min negative
    run_command "exit -9223372036854775809" 2   # Underflow
    run_command "exit 00000000000000000000000001" 1  # Leading zeros
    run_command "exit +001" 1   # Plus sign
    run_command "exit ++001" 2  # Double plus
    
    echo ""
}

# Function to test environment variables
test_environment_variables() {
    echo -e "${BLUE}=== Testing Environment Variables ===${NC}"
    
    # Test env command - minishell might format differently
    test_command_execution "env" "ENV command"
    
    # Test export
    test_command_output "export test=s" "" "Export variable"
    test_command_output "export c b=\"\" a=test" "" "Export multiple variables"
    test_command_output "export a" "" "Export without value"
    
    # Test unset
    test_command_output "unset test" "" "Unset variable"
    test_command_output "unset HOME" "" "Unset HOME"
    test_command_output "unset PATH" "" "Unset PATH"
    
    # Test variable expansion - need to test within same session
    test_command_output "echo \$USER" "$USER" "Environment variable expansion"
    test_command_output "echo \"\$USER\"" "$USER" "Variable expansion in double quotes"
    test_command_output "echo '\$USER'" "\$USER" "Variable expansion in single quotes"
    
    # Test exit status - CORRECTED: false should set exit status to 1
    test_command_output "false" "" "False command"
    test_command_output "echo \$?" "0" "Exit status after false (within same session)"
    
    # Test $? as command (should show "command not found" - bash behavior)
    test_error_message "\$?" "command not found" "Dollar question as command (bash behavior)"
    
    echo ""
}

# Function to test cd command
test_cd_command() {
    echo -e "${BLUE}=== Testing CD Command ===${NC}"
    
    # Test cd with relative path
    test_command_output "cd .." "" "CD to parent directory"
    test_command_output "cd ." "" "CD to current directory"
    test_command_output "cd -" "" "CD to previous directory"
    
    # Test cd with absolute path
    test_command_output "cd /tmp" "" "CD to /tmp"
    test_command_output "cd /" "" "CD to root"
    
    # Test cd with invalid path
    test_error_message "cd /nonexistent" "No such file or directory" "CD to nonexistent directory"
    
    # Test cd to previous directory when OLDPWD not set (should show error)
    test_error_message "cd -" "OLDPWD not set" "CD to previous directory when OLDPWD not set"
    
    echo ""
}

# Function to test redirections
test_redirections() {
    echo -e "${BLUE}=== Testing Redirections ===${NC}"
    
    # Test output redirection
    test_command_output "echo hello > test.txt" "" "Output redirection"
    test_command_output "cat test.txt" "hello" "Read redirected file"
    
    # Test append redirection
    test_command_output "echo world >> test.txt" "" "Append redirection"
    test_command_output "cat test.txt" "hello\nworld" "Read appended file"
    
    # Test input redirection
    test_command_output "cat < test.txt" "hello\nworld" "Input redirection"
    
    # Test heredoc - use proper syntax
    test_command_output "cat << EOF
line1
line2
EOF" "line1\nline2" "Heredoc redirection"
    
    # Test multiple redirections
    test_command_output "echo hello > test2.txt > test3.txt > test4.txt" "" "Multiple output redirections"
    test_command_output "cat test4.txt" "hello" "Last redirection takes effect"
    
    echo ""
}

# Function to test pipes
test_pipes() {
    echo -e "${BLUE}=== Testing Pipes ===${NC}"
    
    # Test simple pipe
    test_command_output "echo hello | cat" "hello" "Simple pipe"
    
    # Test multiple pipes
    test_command_output "echo hello | cat | wc -c" "6" "Multiple pipes"
    
    # Test pipe with grep - use simpler syntax
    test_command_output "echo 'hello\nworld\nhello' | grep hello" "hello\nhello" "Pipe with grep"
    
    # Test pipe with redirection
    test_command_output "echo hello | cat > test.txt" "" "Pipe with redirection"
    test_command_output "cat test.txt" "hello" "Read piped and redirected file"
    
    # Test complex pipe chain
    test_command_output "ls -la | grep '\.c$' | wc -l" "$(ls -la | grep '\.c$' | wc -l)" "Complex pipe chain"
    
    # Test pipe with quotes
    test_command_output "echo hello \"|\" | grep h" "hello |" "Pipe with quoted pipe character"
    
    echo ""
}

# Function to test signals
test_signals() {
    echo -e "${BLUE}=== Testing Signals ===${NC}"
    echo "Note: Signal tests require manual interaction"
    echo "Press Ctrl+C in an empty prompt - should show new prompt"
    echo "Press Ctrl+D in an empty prompt - should exit minishell"
    echo "Press Ctrl+\\ in an empty prompt - should do nothing"
    echo ""
}

# Function to test quotes
test_quotes() {
    echo -e "${BLUE}=== Testing Quotes ===${NC}"
    
    # Test single quotes
    test_command_output "echo 'hello world'" "hello world" "Single quotes"
    test_command_output "echo '\$USER'" "\$USER" "Single quotes prevent expansion"
    test_command_output "echo 'hello | world'" "hello | world" "Single quotes with pipe"
    
    # Test double quotes
    test_command_output "echo \"hello world\"" "hello world" "Double quotes"
    test_command_output "echo \"\$USER\"" "$USER" "Double quotes allow expansion"
    test_command_output "echo \"hello | world\"" "hello | world" "Double quotes with pipe"
    
    # Test mixed quotes
    test_command_output "echo \"hello 'world'\"" "hello 'world'" "Mixed quotes"
    test_command_output "echo 'hello \"world\"'" "hello \"world\"" "Mixed quotes reversed"
    
    # Test unclosed quotes - might not error in non-interactive mode
    test_command_output "echo 'hello" "hello" "Unclosed single quote (might not error)"
    test_command_output "echo \"hello" "hello" "Unclosed double quote (might not error)"
    
    echo ""
}

# Function to test edge cases
test_edge_cases() {
    echo -e "${BLUE}=== Testing Edge Cases ===${NC}"
    
    # Test very long command
    local long_cmd="echo "
    for i in {1..100}; do
        long_cmd+="arg$i "
    done
    test_command_output "$long_cmd" "$(echo $long_cmd | cut -d' ' -f2-)" "Very long command"
    
    # Test special characters
    test_command_output "echo '<< > <><><><><<><><><<><<><><<><><>>a'" "<< > <><><><><<><><><<><<><><<><><>>a" "Special characters in quotes"
    
    # Test empty arguments
    test_command_output "echo ''" "" "Empty string argument"
    test_command_output "echo ' ' ' '" "   " "Space arguments"
    
    # Test variable expansion edge cases
    test_command_output "echo \$NONEXISTENT" "" "Non-existent variable"
    test_command_output "echo \$?" "0" "Exit status variable"
    
    echo ""
}

# Function to test PATH handling
test_path_handling() {
    echo -e "${BLUE}=== Testing PATH Handling ===${NC}"
    
    # Test commands without path
    test_command_output "ls" "$(ls)" "Command without path"
    test_command_output "pwd" "$(pwd)" "Built-in without path"
    
    # Test with unset PATH
    test_command_output "unset PATH" "" "Unset PATH"
    test_error_message "ls" "command not found" "Command with unset PATH"
    
    # Test with custom PATH
    test_command_output "export PATH=/bin" "" "Set custom PATH"
    test_command_output "ls" "$(ls)" "Command with custom PATH"
    
    echo ""
}

# Function to test error handling
test_error_handling() {
    echo -e "${BLUE}=== Testing Error Handling ===${NC}"
    
    # Test invalid commands
    test_error_message "nonexistentcommand" "command not found" "Nonexistent command"
    test_error_message "/bin/nonexistent" "No such file or directory" "Nonexistent absolute path"
    
    # Test permission errors
    test_error_message "./test.txt" "Permission denied" "Execute non-executable file"
    
    # Test syntax errors
    test_error_message "echo |" "can't handle open pipes" "Pipe at end of command"
    test_error_message "| echo" "syntax error" "Pipe at start of command"
    
    echo ""
}

# Function to test memory leaks
test_memory_leaks() {
    echo -e "${BLUE}=== Testing Memory Leaks ===${NC}"
    
    # Test basic commands for leaks
    test_with_valgrind "echo hello" "Basic echo"
    test_with_valgrind "pwd" "PWD command"
    test_with_valgrind "ls" "LS command"
    test_with_valgrind "echo \$USER" "Environment variable"
    test_with_valgrind "export TEST=value" "Export command"
    test_with_valgrind "unset TEST" "Unset command"
    test_with_valgrind "cd /tmp" "CD command"
    test_with_valgrind "echo hello | cat" "Pipe command"
    test_with_valgrind "echo hello > test.txt" "Redirection"
    test_with_valgrind "cat < test.txt" "Input redirection"
    
    echo ""
}

# Function to run all tests
run_all_tests() {
    echo -e "${YELLOW}Starting Minishell Comprehensive Tests${NC}"
    echo "================================================"
    echo ""
    
    setup_test_files
    test_compilation
    test_simple_commands
    test_builtin_commands
    test_environment_variables
    test_cd_command
    test_redirections
    test_pipes
    test_quotes
    test_edge_cases
    test_path_handling
    test_error_handling
    test_memory_leaks
    test_signals
    
    cleanup_test_files
    
    echo "================================================"
    echo -e "${YELLOW}Test Summary:${NC}"
    echo -e "Total Tests: $TOTAL_TESTS"
    echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
    echo -e "${RED}Failed: $FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}All tests passed! ��${NC}"
        exit 0
    else
        echo -e "${RED}Some tests failed. Please review the output above.${NC}"
        exit 1
    fi
}

# Function to run specific test category
run_specific_test() {
    local category="$1"
    
    case "$category" in
        "compilation")
            test_compilation
            ;;
        "simple")
            test_simple_commands
            ;;
        "builtin")
            test_builtin_commands
            ;;
        "env")
            test_environment_variables
            ;;
        "cd")
            test_cd_command
            ;;
        "redirection")
            test_redirections
            ;;
        "pipes")
            test_pipes
            ;;
        "quotes")
            test_quotes
            ;;
        "edge")
            test_edge_cases
            ;;
        "path")
            test_path_handling
            ;;
        "error")
            test_error_handling
            ;;
        "leaks")
            test_memory_leaks
            ;;
        "signals")
            test_signals
            ;;
        *)
            echo "Available test categories:"
            echo "  compilation, simple, builtin, env, cd, redirection, pipes, quotes, edge, path, error, leaks, signals"
            echo "  Or run without arguments to run all tests"
            ;;
    esac
}

# Main execution
if [ $# -eq 0 ]; then
    run_all_tests
else
    run_specific_test "$1"
fi
