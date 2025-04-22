#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Path to your minishell executable
MINISHELL="./minishell"

# Counter for passed and failed tests
PASSED=0
FAILED=0
TOTAL=0

# Function to run a test and check the output
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_output="$3"
    
    ((TOTAL++))
    echo -e "${BLUE}[$TOTAL] Running test: ${test_name}${NC}"
    echo -e "Input: ${input}"
    
    # Run the minishell with the input
    actual_output=$($MINISHELL "$input" 2>&1)
    
    # Extract just the tokenization part
    actual_tokens=$(echo "$actual_output" | grep "Token" | sort)
    expected_tokens=$(echo "$expected_output" | grep "Token" | sort)
    
    # Compare the tokens
    if [ "$actual_tokens" = "$expected_tokens" ]; then
        echo -e "${GREEN}Test passed!${NC}"
        ((PASSED++))
    else
        echo -e "${RED}Test failed!${NC}"
        echo -e "${RED}Expected tokens:${NC}"
        echo "$expected_tokens"
        echo -e "${RED}Actual tokens:${NC}"
        echo "$actual_tokens"
        ((FAILED++))
    fi
    echo "----------------------------------------"
}

echo -e "${BLUE}===================================================${NC}"
echo -e "${BLUE}           INTERMEDIATE TOKENIZER TESTS           ${NC}"
echo -e "${BLUE}===================================================${NC}"

##################################################
# REDIRECTION TESTS
##################################################

# Test 1: Input redirection
test_name="Input redirection"
input="cat < input.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: Output redirection
test_name="Output redirection"
input="ls > output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = REDIRECT_OUT, Value = '>'
Token 2: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: Append output redirection
test_name="Append output redirection"
input="echo hello >> log.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = APPEND_OUT, Value = '>>'
Token 3: Type = STR_LITERAL, Value = 'log.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: Here document
test_name="Here document"
input="cat << EOF"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC, Value = '<<'
Token 2: Type = STR_LITERAL, Value = 'EOF'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: Multiple redirections
test_name="Multiple redirections"
input="cat < in.txt > out.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'in.txt'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'out.txt'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# PIPE TESTS
##################################################

# Test 6: Simple pipe
test_name="Simple pipe"
input="ls | grep test"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'grep'
Token 3: Type = STR_LITERAL, Value = 'test'"
run_test "$test_name" "$input" "$expected_output"

# Test 7: Multiple pipes
test_name="Multiple pipes"
input="ls -la | grep test | wc -l"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-la'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'grep'
Token 4: Type = STR_LITERAL, Value = 'test'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'wc'
Token 7: Type = FLAG, Value = '-l'"
run_test "$test_name" "$input" "$expected_output"

# Test 8: Pipe with redirections
test_name="Pipe with redirections"
input="cat file.txt | grep pattern > results.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file.txt'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'grep'
Token 4: Type = STR_LITERAL, Value = 'pattern'
Token 5: Type = REDIRECT_OUT, Value = '>'
Token 6: Type = STR_LITERAL, Value = 'results.txt'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# ENVIRONMENT VARIABLE TESTS
##################################################

# Test 9: Complex environment variable
test_name="Complex environment variable"
input="echo $USER_NAME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER_NAME'"
run_test "$test_name" "$input" "$expected_output"

# Test 10: Multiple environment variables
test_name="Multiple environment variables"
input="echo $USER is using $SHELL"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = STR_LITERAL, Value = 'is'
Token 3: Type = STR_LITERAL, Value = 'using'
Token 4: Type = ENV_VAR, Value = '$SHELL'"
run_test "$test_name" "$input" "$expected_output"

# Test 11: Environment variable with quotes
test_name="Environment variable with quotes"
input="echo \"User: $USER\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'User: $USER'"
run_test "$test_name" "$input" "$expected_output"

# Test 12: Environment variable expansion in paths
test_name="Environment variable expansion in paths"
input="ls $HOME/Documents"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = ENV_VAR, Value = '$HOME'
Token 2: Type = STR_LITERAL, Value = '/Documents'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# BUILT-IN COMMAND TESTS
##################################################

# Test 13: Echo with -n option
test_name="Echo with -n option"
input="echo -n Hello World"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Hello'
Token 3: Type = STR_LITERAL, Value = 'World'"
run_test "$test_name" "$input" "$expected_output"

# Test 14: Cd with relative path
test_name="Cd with relative path"
input="cd ./Documents"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = './Documents'"
run_test "$test_name" "$input" "$expected_output"

# Test 15: Export command
test_name="Export command"
input="export VAR=value"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'VAR=value'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# COMPLEX SPACING TESTS
##################################################

# Test 16: Extra spaces between commands and arguments
test_name="Extra spaces between commands and arguments"
input="echo    hello    world"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = STR_LITERAL, Value = 'world'"
run_test "$test_name" "$input" "$expected_output"

# Test 17: Extra spaces around pipes and redirections
test_name="Extra spaces around pipes and redirections"
input="ls  -l   |   grep   test   >   output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'grep'
Token 4: Type = STR_LITERAL, Value = 'test'
Token 5: Type = REDIRECT_OUT, Value = '>'
Token 6: Type = STR_LITERAL, Value = 'output.txt'"
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
    echo -e "${GREEN}All intermediate tests passed! Your tokenizer handles pipes, redirections, and environment variables correctly.${NC}"
    exit 0
else
    echo -e "${RED}Some intermediate tests failed! Your tokenizer needs improvement.${NC}"
    exit 1
fi
