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
echo -e "${BLUE}             ADVANCED TOKENIZER TESTS             ${NC}"
echo -e "${BLUE}===================================================${NC}"

##################################################
# COMPLEX QUOTE HANDLING TESTS
##################################################

# Test 1: Nested quotes
test_name="Nested quotes"
input="echo \"This is 'nested' quote\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = \"This is 'nested' quote\""
run_test "$test_name" "$input" "$expected_output"

# Test 2: Quotes with escape sequences inside
test_name="Quotes with escape sequences inside"
input="echo \"This has a \\\" inside\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'This has a \" inside'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: Quotes with variables inside
test_name="Quotes with variables inside"
input="echo \"HOME=$HOME and USER=$USER\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'HOME=$HOME and USER=$USER'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# COMPLEX REDIRECTION TESTS
##################################################

# Test 4: Multiple redirections of different types
test_name="Multiple redirections of different types"
input="cat < input.txt > output.txt 2> error.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output.txt'
Token 5: Type = REDIRECT_ERR, Value = '2>'
Token 6: Type = STR_LITERAL, Value = 'error.log'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: Here document with quoted delimiter
test_name="Here document with quoted delimiter"
input="cat << \"EOF\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC, Value = '<<'
Token 2: Type = STR_LITERAL, Value = 'EOF'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: Here document with single quoted delimiter
test_name="Here document with single quoted delimiter"
input="cat << 'LIMIT'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC, Value = '<<'
Token 2: Type = STR_LITERAL, Value = 'LIMIT'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# COMPLEX PIPE TESTS
##################################################

# Test 7: Pipeline with multiple commands and redirections
test_name="Pipeline with multiple commands and redirections"
input="cat < file.txt | grep pattern | sort -r > sorted.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'file.txt'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'grep'
Token 5: Type = STR_LITERAL, Value = 'pattern'
Token 6: Type = PIPE, Value = '|'
Token 7: Type = CMD, Value = 'sort'
Token 8: Type = FLAG, Value = '-r'
Token 9: Type = REDIRECT_OUT, Value = '>'
Token 10: Type = STR_LITERAL, Value = 'sorted.txt'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# ADVANCED ENVIRONMENT VARIABLE TESTS
##################################################

# Test 8: Variable with special characters
test_name="Variable with special characters"
input="echo $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 9: Variable with braces
test_name="Variable with braces"
input="echo ${HOME}"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '${HOME}'"
run_test "$test_name" "$input" "$expected_output"

# Test 10: Complex variable expansion with adjacent text
test_name="Complex variable expansion with adjacent text"
input="echo $USER_name"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = STR_LITERAL, Value = '_name'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# BONUS FEATURE TESTS (if you're implementing them)
##################################################

# Test 11: Logical AND
test_name="Logical AND"
input="mkdir test && cd test"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'mkdir'
Token 1: Type = STR_LITERAL, Value = 'test'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'cd'
Token 4: Type = STR_LITERAL, Value = 'test'"
run_test "$test_name" "$input" "$expected_output"

# Test 12: Logical OR
test_name="Logical OR"
input="ls nonexistent || echo 'Not found'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = STR_LITERAL, Value = 'nonexistent'
Token 2: Type = OR, Value = '||'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'Not found'"
run_test "$test_name" "$input" "$expected_output"

# Test 13: Parentheses for priority
test_name="Parentheses for priority"
input="(ls && echo success) || echo failure"
expected_output="Tokenization successful!
Token 0: Type = OPEN_PAREN, Value = '('
Token 1: Type = CMD, Value = 'ls'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'success'
Token 5: Type = CLOSE_PAREN, Value = ')'
Token 6: Type = OR, Value = '||'
Token 7: Type = CMD, Value = 'echo'
Token 8: Type = STR_LITERAL, Value = 'failure'"
run_test "$test_name" "$input" "$expected_output"

# Test 14: Wildcard
test_name="Wildcard"
input="ls *.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = STR_LITERAL, Value = '*.txt'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# EDGE CASE TESTS
##################################################

# Test 15: Empty command
test_name="Empty command"
input=""
expected_output="Tokenization successful!"
run_test "$test_name" "$input" "$expected_output"

# Test 16: Command with only whitespace
test_name="Command with only whitespace"
input="     "
expected_output="Tokenization successful!"
run_test "$test_name" "$input" "$expected_output"

# Test 17: Unclosed quotes (should be handled according to your implementation)
test_name="Unclosed quotes"
input="echo \"unclosed"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ERROR, Value = 'Unclosed quotes'"
run_test "$test_name" "$input" "$expected_output"

# Test 18: Complex combined command
test_name="Complex combined command"
input="cat file.txt | grep 'pattern with spaces' | sort -r > \"$HOME/sorted_$(date +%Y%m%d).txt\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file.txt'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'grep'
Token 4: Type = STR_LITERAL, Value = 'pattern with spaces'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'sort'
Token 7: Type = FLAG, Value = '-r'
Token 8: Type = REDIRECT_OUT, Value = '>'
Token 9: Type = STR_LITERAL, Value = '$HOME/sorted_$(date +%Y%m%d).txt'"
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
    echo -e "${GREEN}All advanced tests passed! Your tokenizer is robust