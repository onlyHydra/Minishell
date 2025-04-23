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

print_section_header "ENVIROMENTAL BUILT-IN COMMANDS TESTS"

# Basic environment variable tests
echo -e "${BLUE}--- Basic Environment Variable Tests ---${NC}"

# Test 1: Simple environment variable
test_name="Simple environment variable"
input="echo $HOME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: Environment variable with text
test_name="Environment variable with text"
input="echo My home is $HOME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'My'
Token 2: Type = STR_LITERAL, Value = 'home'
Token 3: Type = STR_LITERAL, Value = 'is'
Token 4: Type = ENV_VAR, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: Multiple environment variables
test_name="Multiple environment variables"
input="echo $USER is using $SHELL"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = STR_LITERAL, Value = 'is'
Token 3: Type = STR_LITERAL, Value = 'using'
Token 4: Type = ENV_VAR, Value = '$SHELL'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: Environment variable with underscore
test_name="Environment variable with underscore"
input="echo $USER_NAME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER_NAME'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: Environment variable with numbers
test_name="Environment variable with numbers"
input="echo $VAR123"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$VAR123'"
run_test "$test_name" "$input" "$expected_output"

# Exit status tests
echo -e "${BLUE}--- Exit Status ($?) Tests ---${NC}"

# Test 6: Simple exit status
test_name="Simple exit status"
input="echo $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = EXIT_STATUS, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 7: Exit status with text
test_name="Exit status with text"
input="echo Exit status: $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Exit'
Token 2: Type = STR_LITERAL, Value = 'status:'
Token 3: Type = EXIT_STATUS, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Environment variables with quotes
echo -e "${BLUE}--- Environment Variables with Quotes ---${NC}"

# Test 8: Environment variable in double quotes
test_name="Environment variable in double quotes"
input="echo \"$HOME is my home\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$HOME is my home'"
run_test "$test_name" "$input" "$expected_output"

# Test 9: Environment variable in single quotes
test_name="Environment variable in single quotes"
input="echo '$HOME is not expanded'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$HOME is not expanded'"
run_test "$test_name" "$input" "$expected_output"

# Test 10: Mixed quotes with environment variables
test_name="Mixed quotes with environment variables"
input="echo \"$USER's home is '$HOME'\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$USER's home is '$HOME''"
run_test "$test_name" "$input" "$expected_output"

# Environment variables with other commands
echo -e "${BLUE}--- Environment Variables with Other Commands ---${NC}"

# Test 11: cd with environment variable
test_name="cd with environment variable"
input="cd $HOME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = ENV_VAR, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 12: pwd with exit status
test_name="pwd with exit status"
input="pwd && echo $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'pwd'
Token 1: Type = AND, Value = '&&'
Token 2: Type = CMD, Value = 'echo'
Token 3: Type = EXIT_STATUS, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 13: export with environment variable
test_name="export with environment variable"
input="export NEW_VAR=$HOME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'NEW_VAR=$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 14: unset with environment variable reference
test_name="unset with environment variable reference"
input="unset $VARNAME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'unset'
Token 1: Type = ENV_VAR, Value = '$VARNAME'"
run_test "$test_name" "$input" "$expected_output"

# Environment variables with redirections and pipes
echo -e "${BLUE}--- Environment Variables with Redirections and Pipes ---${NC}"

# Test 15: Environment variable with redirection
test_name="Environment variable with redirection"
input="echo $USER > user.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = REDIRECT_OUT, Value = '>'
Token 3: Type = STR_LITERAL, Value = 'user.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 16: Environment variable in redirection path
test_name="Environment variable in redirection path"
input="echo hello > $HOME/output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = REDIRECT_OUT, Value = '>'
Token 3: Type = ENV_VAR, Value = '$HOME/output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 17: Environment variable with pipe
test_name="Environment variable with pipe"
input="echo $USER | env"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'env'"
run_test "$test_name" "$input" "$expected_output"

# Complex environment variable combinations
echo -e "${BLUE}--- Complex Environment Variable Combinations ---${NC}"

# Test 18: Multiple environment variables and exit status
test_name="Multiple environment variables and exit status"
input="echo $USER:$HOME:$?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = STR_LITERAL, Value = ':'
Token 3: Type = ENV_VAR, Value = '$HOME'
Token 4: Type = STR_LITERAL, Value = ':'
Token 5: Type = EXIT_STATUS, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 19: Environment variables with logical operators
test_name="Environment variables with logical operators"
input="echo $HOME && echo $USER || echo $SHELL"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$HOME'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = ENV_VAR, Value = '$USER'
Token 5: Type = OR, Value = '||'
Token 6: Type = CMD, Value = 'echo'
Token 7: Type = ENV_VAR, Value = '$SHELL'"
run_test "$test_name" "$input" "$expected_output"

# Test 20: Mixed quotes, environment variables and operators
test_name="Mixed quotes, environment variables and operators"
input="echo \"$USER's home\" && echo '$HOME is literal' || echo $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$USER's home'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = '$HOME is literal'
Token 5: Type = OR, Value = '||'
Token 6: Type = CMD, Value = 'echo'
Token 7: Type = EXIT_STATUS, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Super complex combinations without parentheses
echo -e "${BLUE}--- Super Complex Combinations (No Parentheses) ---${NC}"

# Test 21: Complex command with multiple environment variables
test_name="Complex command with multiple env vars"
input="cd $HOME && echo $USER is at $PWD || echo Error: $? > $HOME/error.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = ENV_VAR, Value = '$HOME'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = ENV_VAR, Value = '$USER'
Token 5: Type = STR_LITERAL, Value = 'is'
Token 6: Type = STR_LITERAL, Value = 'at'
Token 7: Type = ENV_VAR, Value = '$PWD'
Token 8: Type = OR, Value = '||'
Token 9: Type = CMD, Value = 'echo'
Token 10: Type = STR_LITERAL, Value = 'Error:'
Token 11: Type = EXIT_STATUS, Value = '$?'
Token 12: Type = REDIRECT_OUT, Value = '>'
Token 13: Type = ENV_VAR, Value = '$HOME/error.log'"
run_test "$test_name" "$input" "$expected_output"

# Test 22: Multiple commands with environment variables and pipes
test_name="Multiple commands with env vars and pipes"
input="echo $SHELL | echo $USER && pwd > $HOME/pwd.txt || echo Exit code: $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$SHELL'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = ENV_VAR, Value = '$USER'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'pwd'
Token 7: Type = REDIRECT_OUT, Value = '>'
Token 8: Type = ENV_VAR, Value = '$HOME/pwd.txt'
Token 9: Type = OR, Value = '||'
Token 10: Type = CMD, Value = 'echo'
Token 11: Type = STR_LITERAL, Value = 'Exit'
Token 12: Type = STR_LITERAL, Value = 'code:'
Token 13: Type = EXIT_STATUS, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 23: Environment variables with special characters in values
test_name="Env vars with special chars in values"
input="export VAR=\"Special $USER:$HOME\" && echo $VAR"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'VAR=Special $USER:$HOME'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = ENV_VAR, Value = '$VAR'"
run_test "$test_name" "$input" "$expected_output"

# Test 24: Environment variables with double quotes and pipes
test_name="Env vars with double quotes and pipes"
input="echo \"Path is $PATH\" | echo \"User is $USER\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Path is $PATH'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'User is $USER'"
run_test "$test_name" "$input" "$expected_output"

# Test 25: Exit status in different positions
test_name="Exit status in different positions"
input="echo Status: $? && echo More $USER $? || echo Even more $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Status:'
Token 2: Type = EXIT_STATUS, Value = '$?'
Token 3: Type = AND, Value = '&&'
Token 4: Type = CMD, Value = 'echo'
Token 5: Type = STR_LITERAL, Value = 'More'
Token 6: Type = ENV_VAR, Value = '$USER'
Token 7: Type = EXIT_STATUS, Value = '$?'
Token 8: Type = OR, Value = '||'
Token 9: Type = CMD, Value = 'echo'
Token 10: Type = STR_LITERAL, Value = 'Even'
Token 11: Type = STR_LITERAL, Value = 'more'
Token 12: Type = EXIT_STATUS, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Edge cases
echo -e "${BLUE}--- Edge Cases ---${NC}"

# Test 26: Adjacent environment variables
test_name="Adjacent environment variables"
input="echo $USER$HOME$PATH"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = ENV_VAR, Value = '$HOME'
Token 3: Type = ENV_VAR, Value = '$PATH'"
run_test "$test_name" "$input" "$expected_output"

# Test 27: Environment variable with curly braces
test_name="Environment variable with curly braces"
input="echo ${HOME}"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '${HOME}'"
run_test "$test_name" "$input" "$expected_output"

# Test 28: Environment variable with text adjacent
test_name="Environment variable with text adjacent"
input="echo $USERname"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = STR_LITERAL, Value = 'name'"
run_test "$test_name" "$input" "$expected_output"

# Test 29: Environment variable with quotes and operators
test_name="Environment variable with quotes and operators"
input="echo \"$HOME\" > $USER.txt && env | echo $? > status.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$HOME'
Token 2: Type = REDIRECT_OUT, Value = '>'
Token 3: Type = ENV_VAR, Value = '$USER'
Token 4: Type = STR_LITERAL, Value = '.txt'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'env'
Token 7: Type = PIPE, Value = '|'
Token 8: Type = CMD, Value = 'echo'
Token 9: Type = EXIT_STATUS, Value = '$?'
Token 10: Type = REDIRECT_OUT, Value = '>'
Token 11: Type = STR_LITERAL, Value = 'status.log'"
run_test "$test_name" "$input" "$expected_output"

# Test 30: The ultimate environment variable test
test_name="Ultimate environment variable test"
input="export PATH=$HOME/bin:$PATH && echo \"$USER's path is $PATH\" || cd $HOME && pwd > $HOME/pwd_$USER.txt | echo Exit code: $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'PATH=$HOME/bin:$PATH'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = '$USER's path is $PATH'
Token 5: Type = OR, Value = '||'
Token 6: Type = CMD, Value = 'cd'
Token 7: Type = ENV_VAR, Value = '$HOME'
Token 8: Type = AND, Value = '&&'
Token 9: Type = CMD, Value = 'pwd'
Token 10: Type = REDIRECT_OUT, Value = '>'
Token 11: Type = ENV_VAR, Value = '$HOME/pwd_'
Token 12: Type = ENV_VAR, Value = '$USER'
Token 13: Type = STR_LITERAL, Value = '.txt'
Token 14: Type = PIPE, Value = '|'
Token 15: Type = CMD, Value = 'echo'
Token 16: Type = STR_LITERAL, Value = 'Exit'
Token 17: Type = STR_LITERAL, Value = 'code:'
Token 18: Type = EXIT_STATUS, Value = '$?'"
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
    echo -e "${GREEN}All environment variable tests passed! Your tokenizer handles environment variables correctly.${NC}"
    exit 0
else
    echo -e "${RED}Some environment variable tests failed! Your tokenizer needs improvement.${NC}"
    exit 1
fi