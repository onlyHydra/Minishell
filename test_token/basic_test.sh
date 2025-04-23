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
echo -e "${BLUE}              BASIC TOKENIZER TESTS               ${NC}"
echo -e "${BLUE}===================================================${NC}"

##################################################
# SIMPLE COMMAND TESTS
##################################################

# Test 1: Simple command
test_name="Simple command"
input="ls"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: Command with single flag
test_name="Command with single flag"
input="ls -l"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: Command with argument
test_name="Command with argument"
input="cat file.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: Command with multiple arguments
test_name="Command with multiple arguments"
input="echo hello world"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = STR_LITERAL, Value = 'world'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# QUOTE HANDLING TESTS
##################################################

# Test 5: Command with single quotes
test_name="Command with single quotes"
input="echo 'hello world'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: Command with double quotes
test_name="Command with double quotes"
input="echo \"hello world\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

# Test 7: Command with mixed quotes
test_name="Command with mixed quotes"
input="echo 'hello' \"world\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = STR_LITERAL, Value = 'world'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# BASIC ENVIRONMENT VARIABLE TESTS
##################################################

# Test 8: Simple environment variable
test_name="Simple environment variable"
input="echo $HOME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 9: Exit status variable
test_name="Exit status variable"
input="echo $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 10: Variable in double quotes - should be treated as a variable
test_name="Variable in double quotes"
input="echo \"$HOME\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 11: Variable in single quotes - should be literal text
test_name="Variable in single quotes"
input="echo '$HOME'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# PATH TESTS
##################################################

# Test 12: Absolute path
test_name="Absolute path"
input="/bin/ls"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = '/bin/ls'"
run_test "$test_name" "$input" "$expected_output"

# Test 13: Relative path
test_name="Relative path"
input="./script.sh"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = './script.sh'"
run_test "$test_name" "$input" "$expected_output"

# Test 14: Parent directory path
test_name="Parent directory path"
input="../bin/program"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = '../bin/program'"
run_test "$test_name" "$input" "$expected_output"

# Test 15: Command with spaces in path (quoted)
test_name="Command with spaces in path"
input="'/path with spaces/prog'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = '/path with spaces/prog'"
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
    echo -e "${GREEN}All basic tests passed! Your tokenizer handles basic commands correctly.${NC}"
    exit 0
else
    echo -e "${RED}Some basic tests failed! Your tokenizer needs improvement.${NC}"
    exit 1
fi
