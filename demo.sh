#!/bin/bash

# Minishell Demo Script
# This script demonstrates the key features of minishell

echo "🐚 Minishell Demo"
echo "================="
echo ""

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Function to run demo command
run_demo() {
    local description="$1"
    local command="$2"
    
    echo -e "${BLUE}📝 $description${NC}"
    echo -e "${YELLOW}Command: $command${NC}"
    echo "$command" | ./minishell
    echo ""
    sleep 1
}

# Check if minishell exists
if [ ! -f "./minishell" ]; then
    echo "❌ minishell not found. Please compile first with 'make'"
    exit 1
fi

echo -e "${GREEN}Starting Minishell Demo...${NC}"
echo ""

# Demo 1: Basic commands
echo "1️⃣ Basic Commands"
echo "------------------"
run_demo "Echo command" "echo 'Hello, Minishell!'"
run_demo "PWD command" "pwd"
run_demo "LS command" "ls -la | head -5"

# Demo 2: Environment variables
echo "2️⃣ Environment Variables"
echo "-------------------------"
run_demo "Show USER variable" "echo \$USER"
run_demo "Show HOME variable" "echo \$HOME"
run_demo "Export new variable" "export DEMO_VAR='Hello from Minishell'"
run_demo "Use exported variable" "echo \$DEMO_VAR"

# Demo 3: Built-in commands
echo "3️⃣ Built-in Commands"
echo "--------------------"
run_demo "CD command" "cd /tmp && pwd"
run_demo "ENV command" "env | head -3"
run_demo "Export command" "export TEST_VAR=42"
run_demo "Unset command" "unset TEST_VAR"

# Demo 4: Redirections
echo "4️⃣ Redirections"
echo "---------------"
run_demo "Output redirection" "echo 'Hello World' > demo.txt"
run_demo "Read redirected file" "cat demo.txt"
run_demo "Append redirection" "echo 'Second line' >> demo.txt"
run_demo "Read appended file" "cat demo.txt"

# Demo 5: Pipes
echo "5️⃣ Pipes"
echo "--------"
run_demo "Simple pipe" "echo 'Hello World' | wc -c"
run_demo "Multiple pipes" "ls -la | grep '.c' | wc -l"
run_demo "Pipe with grep" "echo -e 'apple\nbanana\ncherry' | grep a"

# Demo 6: Quotes
echo "6️⃣ Quote Handling"
echo "-----------------"
run_demo "Single quotes (no expansion)" "echo '\$USER'"
run_demo "Double quotes (with expansion)" "echo \"Current user: \$USER\""
run_demo "Mixed quotes" "echo \"Hello 'World'\""

# Demo 7: Error handling
echo "7️⃣ Error Handling"
echo "-----------------"
run_demo "Invalid command" "nonexistentcommand"
run_demo "Invalid path" "cd /nonexistent/path"
run_demo "Permission error" "./demo.txt"

# Cleanup
echo "🧹 Cleaning up demo files..."
rm -f demo.txt

echo ""
echo -e "${GREEN}✅ Demo completed!${NC}"
echo "For more comprehensive testing, run: ./test_minishell.sh"
