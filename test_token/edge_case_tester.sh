#!/bin/bash

# Colors for better readability
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

MINISHELL=./minishell
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes"
LOG="tokenizer_test_results.log"

# Clear previous log
> "$LOG"

echo -e "${BLUE}===== MINISHELL TOKENIZER TESTER =====${NC}" | tee -a "$LOG"
echo -e "Started at: $(date)" | tee -a "$LOG"
echo -e "-------------------------------------\n" | tee -a "$LOG"

# Function to run a test case
run_test() {
    local test="$1"
    local expected_output="$2"
    local test_name="$3"
    
    echo -e "\n${YELLOW}[TEST ${test_name}]${NC} \"$test\"" | tee -a "$LOG"
    
    # Run the command and capture output
    # Note: Using command-line args instead of piping
    $MINISHELL "$test" > output.tmp 2>&1
    
    # Extract tokens from output
    actual_output=$(grep -A 100 "Token" output.tmp)
    
    # Check if output matches expected
    echo -e "${BLUE}[Comparing Output]${NC}" | tee -a "$LOG"
    echo "Expected:" | tee -a "$LOG"
    echo "$expected_output" | tee -a "$LOG"
    echo "Actual:" | tee -a "$LOG"
    echo "$actual_output" | tee -a "$LOG"
    
    if [ "$expected_output" == "$actual_output" ]; then
        echo -e "${GREEN}✅ Output matches${NC}" | tee -a "$LOG"
        output_result=0
    else
        echo -e "${RED}❌ Output mismatch${NC}" | tee -a "$LOG"
        output_result=1
    fi
    
    # Run with valgrind to check for memory leaks
    echo -e "${BLUE}[Memory Check]${NC}" | tee -a "$LOG"
    valgrind_output=$($VALGRIND $MINISHELL "$test" 2>&1 > /dev/null)
    
    # Check for memory leaks in valgrind output
    if echo "$valgrind_output" | grep -q "definitely lost:" && ! echo "$valgrind_output" | grep -q "definitely lost: 0 bytes"; then
        echo -e "${RED}❌ Memory leaks detected!${NC}" | tee -a "$LOG"
        echo "$valgrind_output" | grep -A 5 "LEAK SUMMARY" | tee -a "$LOG"
        memory_result=1
    else
        echo -e "${GREEN}✅ No memory leaks${NC}" | tee -a "$LOG"
        memory_result=0
    fi
    
    # Final test result
    if [ $output_result -eq 0 ] && [ $memory_result -eq 0 ]; then
        echo -e "${GREEN}✅ TEST PASSED${NC}" | tee -a "$LOG"
        return 0
    else
        echo -e "${RED}❌ TEST FAILED${NC}" | tee -a "$LOG"
        return 1
    fi
}

# Array to track test results
passed_tests=0
total_tests=0

# Basic tests
run_test "echo hello" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'" "Basic command"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "ls -la" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-la'" "Command with flag"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Quoted strings
run_test 'echo "hello world"' "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello world'" "Double quoted string"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "echo 'single quoted string'" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'single quoted string'" "Single quoted string"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Operators
run_test "ls | grep test" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'grep'
Token 3: Type = STR_LITERAL, Value = 'test'" "Pipe operator"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "cat file > output.txt" "Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file'
Token 2: Type = REDIR_OUT, Value = '>'
Token 3: Type = STR_LITERAL, Value = 'output.txt'" "Redirect output"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "cat file >> append.txt" "Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file'
Token 2: Type = APPEND_OUT, Value = '>>'
Token 3: Type = STR_LITERAL, Value = 'append.txt'" "Append output"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "cat < input.txt" "Token 0: Type = CMD, Value = 'cat'
Token 1: Type = REDIR_IN, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'" "Redirect input"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "ls && pwd" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = AND, Value = '&&'
Token 2: Type = CMD, Value = 'pwd'" "AND operator"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "ls || echo failed" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = OR, Value = '||'
Token 2: Type = CMD, Value = 'echo'
Token 3: Type = STR_LITERAL, Value = 'failed'" "OR operator"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "ls ; pwd" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = SEMICOLON, Value = ';'
Token 2: Type = CMD, Value = 'pwd'" "Semicolon operator"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Complex test (from your example)
run_test 'echo "hello there my name is john" | ls -l && cat filname >> output.txt' "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello there my name is john'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'ls'
Token 4: Type = FLAG, Value = '-l'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'cat'
Token 7: Type = STR_LITERAL, Value = 'filname'
Token 8: Type = APPEND_OUT, Value = '>>'
Token 9: Type = STR_LITERAL, Value = 'output.txt'" "Complex command" 
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Edge Cases to break the tokenizer

# Nested quotes (fixed syntax)
run_test "echo \"This has a 'nested' quote\"" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'This has a \'nested\' quote'" "Nested quotes"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Escaped special characters
run_test "echo This\\ has\\ spaces" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'This has spaces'" "Escaped spaces"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Unclosed quotes (potential segfault check)
run_test "echo \"unclosed quote" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'unclosed quote'" "Unclosed quotes"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Multiple consecutive operators (potential parsing errors) - fixed syntax
run_test "ls | | | grep test" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'grep'
Token 5: Type = STR_LITERAL, Value = 'test'" "Multiple consecutive operators"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Command with quoted operators
run_test "echo \"|\" && echo \">\"" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '|'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = '>'" "Quoted operators"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Command with backslash-escaped operators
run_test "echo \\| && echo \\>" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '|'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = '>'" "Escaped operators"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Mixed backslashes and quotes
run_test "echo \"hello\\\"world\"" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello\"world'" "Backslash in quotes"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Empty quotes
run_test "echo \"\"" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = ''" "Empty double quotes"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

run_test "echo ''" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = ''" "Empty single quotes"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Special cases from your initial tester
run_test "'ls ; pwd'" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = SEMICOLON, Value = ';'
Token 2: Type = CMD, Value = 'pwd'" "Quoted command with semicolon"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# More edge cases

# Very long input (potential buffer issues)
long_input=""
for i in {1..50}; do
    long_input+="echo argument$i "
done
run_test "$long_input" "" "Very long input"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Command with lots of operators
run_test "ls | grep a > out.txt && cat out.txt | wc -l || echo 'not found' > error.log" "Token 0: Type = CMD, Value = 'ls'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'grep'
Token 3: Type = STR_LITERAL, Value = 'a'
Token 4: Type = REDIR_OUT, Value = '>'
Token 5: Type = STR_LITERAL, Value = 'out.txt'
Token 6: Type = AND, Value = '&&'
Token 7: Type = CMD, Value = 'cat'
Token 8: Type = STR_LITERAL, Value = 'out.txt'
Token 9: Type = PIPE, Value = '|'
Token 10: Type = CMD, Value = 'wc'
Token 11: Type = FLAG, Value = '-l'
Token 12: Type = OR, Value = '||'
Token 13: Type = CMD, Value = 'echo'
Token 14: Type = STR_LITERAL, Value = 'not found'
Token 15: Type = REDIR_OUT, Value = '>'
Token 16: Type = STR_LITERAL, Value = 'error.log'" "Multiple operators"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Mixed quote types with special characters
run_test "echo \"single 'quote' inside\" 'double \"quote\" inside'" "Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'single \'quote\' inside'
Token 2: Type = STR_LITERAL, Value = 'double \"quote\" inside'" "Mixed quotes"
[ $? -eq 0 ] && ((passed_tests++))
((total_tests++))

# Results summary
echo -e "\n${BLUE}===== TEST RESULTS =====${NC}" | tee -a "$LOG"
echo -e "Passed: ${GREEN}$passed_tests${NC} / ${total_tests}" | tee -a "$LOG"
echo -e "Failed: ${RED}$((total_tests - passed_tests))${NC} / ${total_tests}" | tee -a "$LOG"
echo -e "\nDetailed log saved to: ${LOG}" | tee -a "$LOG"

# Clean up
rm -f output.tmp

if [ $passed_tests -eq $total_tests ]; then
    echo -e "\n${GREEN}All tests passed!${NC}" | tee -a "$LOG"
    exit 0
else
    echo -e "\n${RED}Some tests failed. Check the log for details.${NC}" | tee -a "$LOG"
    exit 1
fi
