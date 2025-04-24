#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

# Path to your minishell executable
MINISHELL="./minishell"

# Counter for passed and failed tests
PASSED=0
FAILED=0
TOTAL=0

# Create a temporary directory for diff files
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

# Function to run a test and check the output
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_output="$3"
    
    ((TOTAL++))
    echo -e "${BLUE}[$TOTAL] Running test: ${test_name}${NC}"
    echo -e "${CYAN}Input: ${input}${NC}"
    
    # Run the minishell with the input
    actual_output=$($MINISHELL "$input" 2>&1)
    
    # Extract just the tokenization part
    actual_tokens=$(echo "$actual_output" | grep "Token" | sort)
    expected_tokens=$(echo "$expected_output" | grep "Token" | sort)
    
    # Compare the tokens
    if [ "$actual_tokens" = "$expected_tokens" ]; then
        echo -e "${GREEN}✓ Test passed!${NC}"
        ((PASSED++))
    else
        echo -e "${RED}✗ Test failed!${NC}"
        
        # Create temp files for expected and actual output for diff
        local expected_file="$TEMP_DIR/expected_$TOTAL.txt"
        local actual_file="$TEMP_DIR/actual_$TOTAL.txt"
        
        echo "$expected_tokens" > "$expected_file"
        echo "$actual_tokens" > "$actual_file"
        
        # Show detailed differences
        echo -e "${RED}Token differences (Expected → Actual):${NC}"
        
        # Using a more readable diff format
        diff_output=$(diff -y --suppress-common-lines "$expected_file" "$actual_file")
        if [ -n "$diff_output" ]; then
            echo -e "${YELLOW}$diff_output${NC}"
            
            # Also show missing and extra tokens
            echo -e "${RED}Missing tokens (in expected but not in actual):${NC}"
            diff --changed-group-format='%<' --unchanged-group-format='' "$expected_file" "$actual_file" | grep -v "^$" | sed 's/^/  /'
            
            echo -e "${RED}Extra tokens (in actual but not in expected):${NC}"
            diff --changed-group-format='%>' --unchanged-group-format='' "$expected_file" "$actual_file" | grep -v "^$" | sed 's/^/  /'
        else
            echo -e "${YELLOW}Token order or whitespace differences detected${NC}"
        fi
        
        # Show token counts
        expected_count=$(echo "$expected_tokens" | wc -l)
        actual_count=$(echo "$actual_tokens" | wc -l)
        echo -e "${CYAN}Expected token count: ${expected_count}${NC}"
        echo -e "${CYAN}Actual token count: ${actual_count}${NC}"
        
        ((FAILED++))
    fi
    echo -e "${MAGENTA}----------------------------------------${NC}"
}

print_section_header() {
    echo -e "${BLUE}===================================================${NC}"
    echo -e "${BLUE}              $1               ${NC}"
    echo -e "${BLUE}===================================================${NC}"
}

print_section_header "INTERMEDIATE BUILT-IN COMMANDS TESTS"

# Commands with single quotes
echo -e "${BLUE}--- Commands with Single Quotes ---${NC}"

# Test 1: echo with -n and single quotes
test_name="echo with -n and single quotes"
input="echo -n 'hello world'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: cd with relative path in single quotes
test_name="cd with relative path in single quotes"
input="cd '../my documents'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '../my documents'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: cd with absolute path in single quotes
test_name="cd with absolute path in single quotes"
input="cd '/home/user/my files'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/home/user/my files'"
run_test "$test_name" "$input" "$expected_output"

# Commands with double quotes
echo -e "${BLUE}--- Commands with Double Quotes ---${NC}"

# Test 4: echo with -n and double quotes
test_name="echo with -n and double quotes"
input="echo -n \"hello world\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: cd with relative path in double quotes
test_name="cd with relative path in double quotes"
input="cd \"../my documents\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '../my documents'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: cd with absolute path in double quotes
test_name="cd with absolute path in double quotes"
input="cd \"/home/user/my files\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/home/user/my files'"
run_test "$test_name" "$input" "$expected_output"

# Commands with redirections
echo -e "${BLUE}--- Commands with Redirections ---${NC}"

# Test 7: echo with output redirection
test_name="echo with output redirection"
input="echo -n hello > output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 8: pwd with output redirection
test_name="pwd with output redirection"
input="pwd > current_dir.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'pwd'
Token 1: Type = REDIRECT_OUT, Value = '>'
Token 2: Type = STR_LITERAL, Value = 'current_dir.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 9: env with output redirection
test_name="env with output redirection"
input="env > environment.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'env'
Token 1: Type = REDIRECT_OUT, Value = '>'
Token 2: Type = STR_LITERAL, Value = 'environment.txt'"
run_test "$test_name" "$input" "$expected_output"

# Commands with pipes
echo -e "${BLUE}--- Commands with Pipes ---${NC}"

# Test 10: echo piped to another command
test_name="echo piped to another command"
input="echo -n hello | env"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'env'"
run_test "$test_name" "$input" "$expected_output"

# Test 11: pwd piped to another command
test_name="pwd piped to another command"
input="pwd | echo -n"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'pwd'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'echo'
Token 3: Type = FLAG, Value = '-n'"
run_test "$test_name" "$input" "$expected_output"

# Complex combinations
echo -e "${BLUE}--- Complex Command Combinations ---${NC}"

# Test 12: Multiple pipes with built-ins
test_name="Multiple pipes with built-ins"
input="env | pwd | echo -n 'Directory:'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'env'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'pwd'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'echo'
Token 5: Type = FLAG, Value = '-n'
Token 6: Type = STR_LITERAL, Value = 'Directory:'"
run_test "$test_name" "$input" "$expected_output"

# Test 13: Quotes and redirection
test_name="Quotes and redirection"
input="echo -n 'Hello \"World\"' > greeting.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Hello \"World\"'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'greeting.txt'"
run_test "$test_name" "$input" "$expected_output"

# Commands with logical operators
echo -e "${BLUE}--- Commands with Logical Operators ---${NC}"

# Test 14: AND operator with built-ins
test_name="AND operator with built-ins"
input="cd /tmp && pwd"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/tmp'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'"
run_test "$test_name" "$input" "$expected_output"

# Test 15: OR operator with built-ins
test_name="OR operator with built-ins"
input="cd /nonexistent || echo -n 'Not found'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/nonexistent'
Token 2: Type = OR, Value = '||'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = FLAG, Value = '-n'
Token 5: Type = STR_LITERAL, Value = 'Not found'"
run_test "$test_name" "$input" "$expected_output"

# Test 16: Complex logical chain
test_name="Complex logical chain"
input="cd /home && pwd || echo -n 'Failed' && exit"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/home'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'
Token 4: Type = OR, Value = '||'
Token 5: Type = CMD, Value = 'echo'
Token 6: Type = FLAG, Value = '-n'
Token 7: Type = STR_LITERAL, Value = 'Failed'
Token 8: Type = AND, Value = '&&'
Token 9: Type = CMD, Value = 'exit'"
run_test "$test_name" "$input" "$expected_output"

# Additional tests for builtin commands
echo -e "${BLUE}--- Additional Tests for Built-in Commands ---${NC}"

# Test 17: Echo with multiple arguments
test_name="Echo with multiple arguments"
input="echo -n hello world 'quoted text' \"double quoted\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello'
Token 3: Type = STR_LITERAL, Value = 'world'
Token 4: Type = STR_LITERAL, Value = 'quoted text'
Token 5: Type = STR_LITERAL, Value = 'double quoted'"
run_test "$test_name" "$input" "$expected_output"

# Test 18: Multiple redirections
test_name="Multiple redirections"
input="echo -n test > file1.txt > file2.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'test'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'file1.txt'
Token 5: Type = REDIRECT_OUT, Value = '>'
Token 6: Type = STR_LITERAL, Value = 'file2.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 19: Input redirection
test_name="Input redirection"
input="cat < input.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = REDIRECT_IN, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 20: Combined input and output redirection
test_name="Combined input and output redirection"
input="cat < input.txt > output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = REDIRECT_IN, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 21: Append redirection
test_name="Append redirection"
input="echo -n log >> logfile.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'log'
Token 3: Type = APPEND_OUT, Value = '>>'
Token 4: Type = STR_LITERAL, Value = 'logfile.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 22: Here document
test_name="Here document"
input="cat << EOF"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC, Value = '<<'
Token 2: Type = STR_LITERAL, Value = 'EOF'"
run_test "$test_name" "$input" "$expected_output"

# Test 23: Exit with numeric argument
test_name="Exit with numeric argument"
input="exit 42"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'exit'
Token 1: Type = STR_LITERAL, Value = '42'"
run_test "$test_name" "$input" "$expected_output"

# Test 24: Export with variable assignment
test_name="Export with variable assignment"
input="export PATH=/usr/bin"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'PATH=/usr/bin'"
run_test "$test_name" "$input" "$expected_output"

# Test 25: Unset with variable name
test_name="Unset with variable name"
input="unset TESTVAR"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'unset'
Token 1: Type = STR_LITERAL, Value = 'TESTVAR'"
run_test "$test_name" "$input" "$expected_output"

# Test 26: Echo with special characters
test_name="Echo with special characters"
input="echo -n 'special !@#$%^&*()_+'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'special !@#$%^&*()_+'"
run_test "$test_name" "$input" "$expected_output"

# Test 27: Complex pipe chain
test_name="Complex pipe chain"
input="echo -n hello | cat | wc -l | cat > result.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'cat'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'wc'
Token 7: Type = FLAG, Value = '-l'
Token 8: Type = PIPE, Value = '|'
Token 9: Type = CMD, Value = 'cat'
Token 10: Type = REDIRECT_OUT, Value = '>'
Token 11: Type = STR_LITERAL, Value = 'result.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 28: Multiple commands with complex operators
test_name="Multiple commands with complex operators"
input="cd /tmp && pwd > loc.txt || echo -n 'Error' >> error.log && exit 1"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/tmp'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'
Token 4: Type = REDIRECT_OUT, Value = '>'
Token 5: Type = STR_LITERAL, Value = 'loc.txt'
Token 6: Type = OR, Value = '||'
Token 7: Type = CMD, Value = 'echo'
Token 8: Type = FLAG, Value = '-n'
Token 9: Type = STR_LITERAL, Value = 'Error'
Token 10: Type = APPEND_OUT, Value = '>>'
Token 11: Type = STR_LITERAL, Value = 'error.log'
Token 12: Type = AND, Value = '&&'
Token 13: Type = CMD, Value = 'exit'
Token 14: Type = STR_LITERAL, Value = '1'"
run_test "$test_name" "$input" "$expected_output"

# Test 29: Echo with escape sequences
test_name="Echo with escape sequences"
input="echo -n \"hello\\nworld\\t!\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello\\nworld\\t!'"
run_test "$test_name" "$input" "$expected_output"

# Test 30: Command with multiple flags
test_name="Command with multiple flags"
input="ls -la /home"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-la'
Token 2: Type = STR_LITERAL, Value = '/home'"
run_test "$test_name" "$input" "$expected_output"

# Display test results summary
echo -e "${BLUE}===================================================${NC}"
echo -e "${BLUE}               TEST RESULTS SUMMARY               ${NC}"
echo -e "${BLUE}===================================================${NC}"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "${YELLOW}Total: $TOTAL${NC}"

# Calculate percentage of passed tests
if [ $TOTAL -ne 0 ]; then
    PERCENTAGE=$((PASSED * 100 / TOTAL))
    echo -e "${BLUE}Pass Rate: $PERCENTAGE%${NC}"
else
    echo -e "${YELLOW}No tests run.${NC}"
fi

# Exit with appropriate status code
if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed! Your tokenizer handles built-in commands correctly.${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed! Your tokenizer needs improvement.${NC}"
    exit 1
fi
