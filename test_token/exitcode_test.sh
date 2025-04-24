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

print_section_header "EXIT CODE TESTS + ENVIROMENTAL"

# Test 1: Simple environment variable
test_name="Simple environment variable"
input="echo \$HOME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '\$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: Check last exit status with $?
test_name="Check last exit code with \$?"
input="echo \$?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = EXIT_CODE, Value = '\$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: Set exit status using `false` and check it
test_name="false command followed by echo \$?"
input="false; echo \$?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'false'
Token 1: Type = SEPARATOR, Value = ';'
Token 2: Type = CMD, Value = 'echo'
Token 3: Type = EXIT_CODE, Value = '\$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: Use `exit 42` and check value with \$?
test_name="exit 42 and echo \$?"
input="exit 42; echo \$?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'exit'
Token 1: Type = ARG, Value = '42'
Token 2: Type = SEPARATOR, Value = ';'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = EXIT_CODE, Value = '\$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: Invalid exit argument (non-numeric)
test_name="Invalid exit argument"
input="exit abc"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'exit'
Token 1: Type = ARG, Value = 'abc'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: exit without arguments
test_name="exit without arguments"
input="exit"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'exit'"
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
