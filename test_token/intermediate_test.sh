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

# Test 1: echo with -n
test_name="echo with -n"
input="echo -n 'hello there'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello there'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: cd with relative path
test_name="cd with relative path"
input="cd ../Documents"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '../Documents'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: cd with absolute path
test_name="cd with absolute path"
input="cd /home/user"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/home/user'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: pwd with no options
test_name="pwd with no options"
input="pwd"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'pwd'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: export with no options
test_name="export with no options"
input="export"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: unset with no options
test_name="unset with no options"
input="unset"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'unset'"
run_test "$test_name" "$input" "$expected_output"

# Test 7: env with no options
test_name="env with no options"
input="env"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'env'"
run_test "$test_name" "$input" "$expected_output"

# Test 8: exit with no options
test_name="exit with no options"
input="exit"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'exit'"
run_test "$test_name" "$input" "$expected_output"


# Test 1: echo with pipe
test_name="echo piped to env"
input="echo -n 'hello' | env"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'hello'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'env'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: pwd with redirect to file
test_name="pwd with redirection"
input="pwd > out.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'pwd'
Token 1: Type = REDIRECT_OUT, Value = '>'
Token 2: Type = STR_LITERAL, Value = 'out.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: export with append redirect
test_name="export with append"
input="export >> file.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = APPEND_OUT, Value = '>>'
Token 2: Type = STR_LITERAL, Value = 'file.log'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: unset with input redirection
test_name="unset with input redirection"
input="unset < input.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'unset'
Token 1: Type = REDIRECT_IN, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: echo with logical AND
test_name="echo && pwd"
input="echo 'hi' && pwd"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hi'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: cd with OR operator
test_name="cd || pwd"
input="cd /not/a/path || pwd"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/not/a/path'
Token 2: Type = OR, Value = '||'
Token 3: Type = CMD, Value = 'pwd'"
run_test "$test_name" "$input" "$expected_output"

# Test 7: (grouped echo and exit) with pipe
test_name="grouped echo + pipe to exit"
input="(echo hello) | exit"
expected_output="Tokenization successful!
Token 0: Type = LPAREN, Value = '('
Token 1: Type = CMD, Value = 'echo'
Token 2: Type = STR_LITERAL, Value = 'hello'
Token 3: Type = RPAREN, Value = ')'
Token 4: Type = PIPE, Value = '|'
Token 5: Type = CMD, Value = 'exit'"
run_test "$test_name" "$input" "$expected_output"

# Test 1: Full built-in madness
test_name="All built-ins chained with pipes and logical ops"
input="export VAR=42 && echo -n \"The value is: \$VAR\" | unset VAR || env | cd /tmp && pwd > log.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'VAR=42'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = FLAG, Value = '-n'
Token 5: Type = STR_LITERAL, Value = 'The value is: \$VAR'
Token 6: Type = PIPE, Value = '|'
Token 7: Type = CMD, Value = 'unset'
Token 8: Type = STR_LITERAL, Value = 'VAR'
Token 9: Type = OR, Value = '||'
Token 10: Type = CMD, Value = 'env'
Token 11: Type = PIPE, Value = '|'
Token 12: Type = CMD, Value = 'cd'
Token 13: Type = STR_LITERAL, Value = '/tmp'
Token 14: Type = AND, Value = '&&'
Token 15: Type = CMD, Value = 'pwd'
Token 16: Type = REDIRECT_OUT, Value = '>'
Token 17: Type = FILE_NAME, Value = 'log.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: Insane nesting and quoting
test_name="Nesting, quoting, and ops"
input="(((echo 'Start') && export PATH='/my path' || unset PATH) | env) && cd ~/folder && (pwd >> results.log || exit)"
expected_output="Tokenization successful!
Token 0: Type = LPAREN, Value = '('
Token 1: Type = LPAREN, Value = '('
Token 2: Type = LPAREN, Value = '('
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'Start'
Token 5: Type = RPAREN, Value = ')'
Token 6: Type = AND, Value = '&&'
Token 7: Type = CMD, Value = 'export'
Token 8: Type = STR_LITERAL, Value = 'PATH=/my path'
Token 9: Type = OR, Value = '||'
Token 10: Type = CMD, Value = 'unset'
Token 11: Type = STR_LITERAL, Value = 'PATH'
Token 12: Type = RPAREN, Value = ')'
Token 13: Type = PIPE, Value = '|'
Token 14: Type = CMD, Value = 'env'
Token 15: Type = RPAREN, Value = ')'
Token 16: Type = AND, Value = '&&'
Token 17: Type = CMD, Value = 'cd'
Token 18: Type = STR_LITERAL, Value = '~/folder'
Token 19: Type = AND, Value = '&&'
Token 20: Type = LPAREN, Value = '('
Token 21: Type = CMD, Value = 'pwd'
Token 22: Type = APPEND_OUT, Value = '>>'
Token 23: Type = FILE_NAME, Value = 'results.log'
Token 24: Type = OR, Value = '||'
Token 25: Type = CMD, Value = 'exit'
Token 26: Type = RPAREN, Value = ')'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: Quoting hell
test_name="Quote-inside-quote madness"
input="echo \"She said: 'It\\'s fine' and left\" && echo 'Back to \"normal\" now' | exit"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'She said: 'It\\'s fine' and left'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'Back to \"normal\" now'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'exit'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: Mixed logic, redirection, pipe, quotes
test_name="echo and export with redirects and pipes"
input="echo -n 'logging in...' > log.txt && export SESSION='active' || echo 'failed' | unset SESSION"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'logging in...'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = FILE_NAME, Value = 'log.txt'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'export'
Token 7: Type = STR_LITERAL, Value = 'SESSION=active'
Token 8: Type = OR, Value = '||'
Token 9: Type = CMD, Value = 'echo'
Token 10: Type = STR_LITERAL, Value = 'failed'
Token 11: Type = PIPE, Value = '|'
Token 12: Type = CMD, Value = 'unset'
Token 13: Type = STR_LITERAL, Value = 'SESSION'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: export, cd, and pwd in logic chain with grouping
test_name="grouped built-ins with logic chain"
input="(export USER=guest && cd /tmp) || (pwd > /dev/null && exit)"
expected_output="Tokenization successful!
Token 0: Type = LPAREN, Value = '('
Token 1: Type = CMD, Value = 'export'
Token 2: Type = STR_LITERAL, Value = 'USER=guest'
Token 3: Type = AND, Value = '&&'
Token 4: Type = CMD, Value = 'cd'
Token 5: Type = STR_LITERAL, Value = '/tmp'
Token 6: Type = RPAREN, Value = ')'
Token 7: Type = OR, Value = '||'
Token 8: Type = LPAREN, Value = '('
Token 9: Type = CMD, Value = 'pwd'
Token 10: Type = REDIRECT_OUT, Value = '>'
Token 11: Type = FILE_NAME, Value = '/dev/null'
Token 12: Type = AND, Value = '&&'
Token 13: Type = CMD, Value = 'exit'
Token 14: Type = RPAREN, Value = ')'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: env + crazy pathing and redirect chaining
test_name="env and pwd with mixed paths and appends"
input="env | cd ./folder/../folder && pwd >> /tmp/output.log || exit"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'env'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'cd'
Token 3: Type = STR_LITERAL, Value = './folder/../folder'
Token 4: Type = AND, Value = '&&'
Token 5: Type = CMD, Value = 'pwd'
Token 6: Type = APPEND_OUT, Value = '>>'
Token 7: Type = FILE_NAME, Value = '/tmp/output.log'
Token 8: Type = OR, Value = '||'
Token 9: Type = CMD, Value = 'exit'"
run_test "$test_name" "$input" "$expected_output"

# Test 7: mix of single/double quotes, redirect and AND
test_name="quotes + redirection + logic"
input="echo \"status: 'ok'\" > result.txt && echo 'done'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'status: 'ok''
Token 2: Type = REDIRECT_OUT, Value = '>'
Token 3: Type = FILE_NAME, Value = 'result.txt'
Token 4: Type = AND, Value = '&&'
Token 5: Type = CMD, Value = 'echo'
Token 6: Type = STR_LITERAL, Value = 'done'"
run_test "$test_name" "$input" "$expected_output"

# Test 8: full export/unset madness
test_name="export + unset chaos with quoting"
input="export VAR1='value1' && export VAR2=\"val 2\" && unset VAR1 VAR2 || echo 'cleanup failed'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'VAR1=value1'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'export'
Token 4: Type = STR_LITERAL, Value = 'VAR2=val 2'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'unset'
Token 7: Type = STR_LITERAL, Value = 'VAR1'
Token 8: Type = STR_LITERAL, Value = 'VAR2'
Token 9: Type = OR, Value = '||'
Token 10: Type = CMD, Value = 'echo'
Token 11: Type = STR_LITERAL, Value = 'cleanup failed'"
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
