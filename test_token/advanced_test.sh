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

print_section_header "ADVANCED BUILT-IN COMMANDS TESTS"

# Category 1: Ultra Complex Command Chains
echo -e "${YELLOW}--- Ultra Complex Command Chains ---${NC}"

# Test 1: Extended pipe chain with multiple built-ins and redirections
test_name="Extended pipe chain with multiple built-ins and redirections"
input="echo -n 'Starting process' > start.log && pwd | cat | env | cat > env_output.txt && cd /tmp && echo -n 'Changed directory' || exit 1"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Starting process'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'start.log'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'pwd'
Token 7: Type = PIPE, Value = '|'
Token 8: Type = CMD, Value = 'cat'
Token 9: Type = PIPE, Value = '|'
Token 10: Type = CMD, Value = 'env'
Token 11: Type = PIPE, Value = '|'
Token 12: Type = CMD, Value = 'cat'
Token 13: Type = REDIRECT_OUT, Value = '>'
Token 14: Type = STR_LITERAL, Value = 'env_output.txt'
Token 15: Type = AND, Value = '&&'
Token 16: Type = CMD, Value = 'cd'
Token 17: Type = STR_LITERAL, Value = '/tmp'
Token 18: Type = AND, Value = '&&'
Token 19: Type = CMD, Value = 'echo'
Token 20: Type = FLAG, Value = '-n'
Token 21: Type = STR_LITERAL, Value = 'Changed directory'
Token 22: Type = OR, Value = '||'
Token 23: Type = CMD, Value = 'exit'
Token 24: Type = STR_LITERAL, Value = '1'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: Massive command chain with built-ins, redirections, and piping
test_name="Massive command chain with built-ins, redirections, and piping"
input="cd /usr && pwd > location.txt || echo -n 'Failed to change directory' && export TESTVAR=value && echo -n 'Exported variable' | cat > export.log && unset TESTVAR && env | grep PATH > path_info.txt || exit 255"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/usr'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'
Token 4: Type = REDIRECT_OUT, Value = '>'
Token 5: Type = STR_LITERAL, Value = 'location.txt'
Token 6: Type = OR, Value = '||'
Token 7: Type = CMD, Value = 'echo'
Token 8: Type = FLAG, Value = '-n'
Token 9: Type = STR_LITERAL, Value = 'Failed to change directory'
Token 10: Type = AND, Value = '&&'
Token 11: Type = CMD, Value = 'export'
Token 12: Type = STR_LITERAL, Value = 'TESTVAR=value'
Token 13: Type = AND, Value = '&&'
Token 14: Type = CMD, Value = 'echo'
Token 15: Type = FLAG, Value = '-n'
Token 16: Type = STR_LITERAL, Value = 'Exported variable'
Token 17: Type = PIPE, Value = '|'
Token 18: Type = CMD, Value = 'cat'
Token 19: Type = REDIRECT_OUT, Value = '>'
Token 20: Type = STR_LITERAL, Value = 'export.log'
Token 21: Type = AND, Value = '&&'
Token 22: Type = CMD, Value = 'unset'
Token 23: Type = STR_LITERAL, Value = 'TESTVAR'
Token 24: Type = AND, Value = '&&'
Token 25: Type = CMD, Value = 'env'
Token 26: Type = PIPE, Value = '|'
Token 27: Type = CMD, Value = 'grep'
Token 28: Type = STR_LITERAL, Value = 'PATH'
Token 29: Type = REDIRECT_OUT, Value = '>'
Token 30: Type = STR_LITERAL, Value = 'path_info.txt'
Token 31: Type = OR, Value = '||'
Token 32: Type = CMD, Value = 'exit'
Token 33: Type = STR_LITERAL, Value = '255'"
run_test "$test_name" "$input" "$expected_output"

# Category 2: Complex Quote Handling
echo -e "${YELLOW}--- Complex Quote Handling ---${NC}"

# Test 3: Nested quotes with special characters
test_name="Nested quotes with special characters"
input="echo -n 'This is a \"quoted\" string with special $%^&*()_+ chars' > \"output file with 'spaces'.txt\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'This is a \"quoted\" string with special $%^&*()_+ chars'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output file with \\'spaces\\'.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: Mixed quotes with escaped characters
test_name="Mixed quotes with escaped characters"
input="echo -n \"Line one\\nLine 'two'\\tTabbed\" > 'file with \"double quotes\" inside.txt'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Line one\\nLine \\'two\\'\\tTabbed'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'file with \"double quotes\" inside.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: Multiple quoted arguments with spaces
test_name="Multiple quoted arguments with spaces"
input="echo -n 'first argument with spaces' \"second argument with spaces\" 'third argument' \"fourth arg\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'first argument with spaces'
Token 3: Type = STR_LITERAL, Value = 'second argument with spaces'
Token 4: Type = STR_LITERAL, Value = 'third argument'
Token 5: Type = STR_LITERAL, Value = 'fourth arg'"
run_test "$test_name" "$input" "$expected_output"

# Category 3: Complex Redirections
echo -e "${YELLOW}--- Complex Redirections ---${NC}"

# Test 6: Multiple input/output redirections
test_name="Multiple input/output redirections"
input="cat < input1.txt < input2.txt > output1.txt > output2.txt >> append.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = REDIRECT_IN, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input1.txt'
Token 3: Type = REDIRECT_IN, Value = '<'
Token 4: Type = STR_LITERAL, Value = 'input2.txt'
Token 5: Type = REDIRECT_OUT, Value = '>'
Token 6: Type = STR_LITERAL, Value = 'output1.txt'
Token 7: Type = REDIRECT_OUT, Value = '>'
Token 8: Type = STR_LITERAL, Value = 'output2.txt'
Token 9: Type = REDIRECT_APPEND, Value = '>>'
Token 10: Type = STR_LITERAL, Value = 'append.log'"
run_test "$test_name" "$input" "$expected_output"

# Test 7: Here document with quoted delimiters
test_name="Here document with quoted delimiters"
input="cat << 'EOF' > output.txt << \"END\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC, Value = '<<'
Token 2: Type = STR_LITERAL, Value = 'EOF'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output.txt'
Token 5: Type = HEREDOC, Value = '<<'
Token 6: Type = STR_LITERAL, Value = 'END'"
run_test "$test_name" "$input" "$expected_output"

# Test 8: Complex file descriptor redirections
test_name="Complex file descriptor redirections"
input="cmd 2>&1 1>/dev/null 2> error.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cmd'
Token 1: Type = REDIRECT_FD, Value = '2>&1'
Token 2: Type = REDIRECT_OUT, Value = '>'
Token 3: Type = STR_LITERAL, Value = '/dev/null'
Token 4: Type = REDIRECT_OUT, Value = '>'
Token 5: Type = STR_LITERAL, Value = 'error.log'"
run_test "$test_name" "$input" "$expected_output"

# Category 4: Built-in Commands with Complex Arguments
echo -e "${YELLOW}--- Built-in Commands with Complex Arguments ---${NC}"

# Test 9: Echo with complex arguments and redirection
test_name="Echo with complex arguments and redirection"
input="echo -n 'Multi-line text\nWith \"escaped quotes\" and special characters: !@#$%^&*()_+' > 'complex output.txt'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Multi-line text\\nWith \"escaped quotes\" and special characters: !@#$%^&*()_+'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'complex output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 10: Export with multiple variable assignments
test_name="Export with multiple variable assignments"
input="export VAR1=value1 VAR2='value with spaces' VAR3=\"another value\" PATH=/custom/path:/usr/bin"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'VAR1=value1'
Token 2: Type = STR_LITERAL, Value = 'VAR2=value with spaces'
Token 3: Type = STR_LITERAL, Value = 'VAR3=another value'
Token 4: Type = STR_LITERAL, Value = 'PATH=/custom/path:/usr/bin'"
run_test "$test_name" "$input" "$expected_output"

# Test 11: CD with complex paths
test_name="CD with complex paths"
input="cd '/path with spaces/and \"quotes\"/inside' && pwd"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/path with spaces/and \"quotes\"/inside'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'"
run_test "$test_name" "$input" "$expected_output"

# Category 5: Multi-Command Lines
echo -e "${YELLOW}--- Multi-Command Lines ---${NC}"

# Test 12: Multi-command line with semicolons
test_name="Multi-command line with semicolons"
input="echo -n 'Start'; cd /tmp; pwd > location.txt; env | grep USER; exit 0"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Start'
Token 3: Type = SEMICOLON, Value = ';'
Token 4: Type = CMD, Value = 'cd'
Token 5: Type = STR_LITERAL, Value = '/tmp'
Token 6: Type = SEMICOLON, Value = ';'
Token 7: Type = CMD, Value = 'pwd'
Token 8: Type = REDIRECT_OUT, Value = '>'
Token 9: Type = STR_LITERAL, Value = 'location.txt'
Token 10: Type = SEMICOLON, Value = ';'
Token 11: Type = CMD, Value = 'env'
Token 12: Type = PIPE, Value = '|'
Token 13: Type = CMD, Value = 'grep'
Token 14: Type = STR_LITERAL, Value = 'USER'
Token 15: Type = SEMICOLON, Value = ';'
Token 16: Type = CMD, Value = 'exit'
Token 17: Type = STR_LITERAL, Value = '0'"
run_test "$test_name" "$input" "$expected_output"

# Test 13: Command line with mixed logical operators and semicolons
test_name="Command line with mixed logical operators and semicolons"
input="cd /home && pwd > pwd.txt; echo -n 'Step 2' || exit 1; env | grep PATH && echo -n Success || echo -n Failure > status.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/home'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'
Token 4: Type = REDIRECT_OUT, Value = '>'
Token 5: Type = STR_LITERAL, Value = 'pwd.txt'
Token 6: Type = SEMICOLON, Value = ';'
Token 7: Type = CMD, Value = 'echo'
Token 8: Type = FLAG, Value = '-n'
Token 9: Type = STR_LITERAL, Value = 'Step 2'
Token 10: Type = OR, Value = '||'
Token 11: Type = CMD, Value = 'exit'
Token 12: Type = STR_LITERAL, Value = '1'
Token 13: Type = SEMICOLON, Value = ';'
Token 14: Type = CMD, Value = 'env'
Token 15: Type = PIPE, Value = '|'
Token 16: Type = CMD, Value = 'grep'
Token 17: Type = STR_LITERAL, Value = 'PATH'
Token 18: Type = AND, Value = '&&'
Token 19: Type = CMD, Value = 'echo'
Token 20: Type = FLAG, Value = '-n'
Token 21: Type = STR_LITERAL, Value = 'Success'
Token 22: Type = OR, Value = '||'
Token 23: Type = CMD, Value = 'echo'
Token 24: Type = FLAG, Value = '-n'
Token 25: Type = STR_LITERAL, Value = 'Failure'
Token 26: Type = REDIRECT_OUT, Value = '>'
Token 27: Type = STR_LITERAL, Value = 'status.log'"
run_test "$test_name" "$input" "$expected_output"

# Category 6: Extreme Stress Tests
echo -e "${YELLOW}--- Extreme Stress Tests ---${NC}"

# Test 14: Long command with all built-ins and redirections
test_name="Long command with all built-ins and redirections"
input="cd /var && pwd > pwd.txt && echo -n 'Current directory' >> log.txt && export TEST_VAR='test value' && echo -n 'Exported variable' | cat > export_log.txt && env | grep TEST > vars.txt && unset TEST_VAR && echo -n 'Unset variable' || exit 1"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/var'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'
Token 4: Type = REDIRECT_OUT, Value = '>'
Token 5: Type = STR_LITERAL, Value = 'pwd.txt'
Token 6: Type = AND, Value = '&&'
Token 7: Type = CMD, Value = 'echo'
Token 8: Type = FLAG, Value = '-n'
Token 9: Type = STR_LITERAL, Value = 'Current directory'
Token 10: Type = REDIRECT_APPEND, Value = '>>'
Token 11: Type = STR_LITERAL, Value = 'log.txt'
Token 12: Type = AND, Value = '&&'
Token 13: Type = CMD, Value = 'export'
Token 14: Type = STR_LITERAL, Value = 'TEST_VAR=test value'
Token 15: Type = AND, Value = '&&'
Token 16: Type = CMD, Value = 'echo'
Token 17: Type = FLAG, Value = '-n'
Token 18: Type = STR_LITERAL, Value = 'Exported variable'
Token 19: Type = PIPE, Value = '|'
Token 20: Type = CMD, Value = 'cat'
Token 21: Type = REDIRECT_OUT, Value = '>'
Token 22: Type = STR_LITERAL, Value = 'export_log.txt'
Token 23: Type = AND, Value = '&&'
Token 24: Type = CMD, Value = 'env'
Token 25: Type = PIPE, Value = '|'
Token 26: Type = CMD, Value = 'grep'
Token 27: Type = STR_LITERAL, Value = 'TEST'
Token 28: Type = REDIRECT_OUT, Value = '>'
Token 29: Type = STR_LITERAL, Value = 'vars.txt'
Token 30: Type = AND, Value = '&&'
Token 31: Type = CMD, Value = 'unset'
Token 32: Type = STR_LITERAL, Value = 'TEST_VAR'
Token 33: Type = AND, Value = '&&'
Token 34: Type = CMD, Value = 'echo'
Token 35: Type = FLAG, Value = '-n'
Token 36: Type = STR_LITERAL, Value = 'Unset variable'
Token 37: Type = OR, Value = '||'
Token 38: Type = CMD, Value = 'exit'
Token 39: Type = STR_LITERAL, Value = '1'"
run_test "$test_name" "$input" "$expected_output"

# Test 15: Command with lots of quotes and special characters
test_name="Command with lots of quotes and special characters"
input="echo -n 'This is a \"very complex\" string with special \$\`\\\"'\\'\\n\\t chars' > \"output file with 'lots of' \\\"special\\\" characters!@#\$%^&*().txt\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'This is a \"very complex\" string with special \$\`\\\"'\\'\\n\\t chars'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output file with \\'lots of\\' \\\"special\\\" characters!@#\$%^&*().txt'"
run_test "$test_name" "$input" "$expected_output"

# Category 7: Special Case Testing
echo -e "${YELLOW}--- Special Case Testing ---${NC}"

# Test 16: Empty quotes and whitespace
test_name="Empty quotes and whitespace"
input="echo -n '' \"\" '   ' \"   \" > empty.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = ''
Token 3: Type = STR_LITERAL, Value = ''
Token 4: Type = STR_LITERAL, Value = '   '
Token 5: Type = STR_LITERAL, Value = '   '
Token 6: Type = REDIRECT_OUT, Value = '>'
Token 7: Type = STR_LITERAL, Value = 'empty.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 17: Command with Unicode characters
test_name="Command with Unicode characters"
input="echo -n 'Unicode: 你好, こんにちは, привет' > unicode.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Unicode: 你好, こんにちは, привет'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'unicode.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 18: Multiple sequential redirections of different types
test_name="Multiple sequential redirections of different types"
input="cmd < in1.txt << EOF > out1.txt >> out2.txt 2> err.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cmd'
Token 1: Type = REDIRECT_IN, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'in1.txt'
Token 3: Type = HEREDOC, Value = '<<'
Token 4: Type = STR_LITERAL, Value = 'EOF'
Token 5: Type = REDIRECT_OUT, Value = '>'
Token 6: Type = STR_LITERAL, Value = 'out1.txt'
Token 7: Type = REDIRECT_APPEND, Value = '>>'
Token 8: Type = STR_LITERAL, Value = 'out2.txt'
Token 9: Type = REDIRECT_OUT, Value = '>'
Token 10: Type = STR_LITERAL, Value = 'err.log'"
run_test "$test_name" "$input" "$expected_output"

# Category 8: Edge Cases with Whitespace
echo -e "${YELLOW}--- Edge Cases with Whitespace ---${NC}"

# Test 19: Command with excessive whitespace
test_name="Command with excessive whitespace"
input="   echo    -n    'test   with    spaces'   >    output.txt   "
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'test   with    spaces'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 20: Command with tab characters
test_name="Command with tab characters"
input="echo\t-n\t'test\twith\ttabs'\t>\toutput.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'test\twith\ttabs'
Token 3: Type = REDIRECT_OUT, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Category 9: Ultra Long Command Lines
echo -e "${YELLOW}--- Ultra Long Command Lines ---${NC}"

# Test 21: Ultra long command with all built-ins in sequence
test_name="Ultra long command with all built-ins in sequence"
input="cd /usr && pwd > dir.txt && echo -n 'Current directory' >> log.txt && cd /var && pwd >> dir.txt && echo -n 'Changed directory' >> log.txt && cd /tmp && pwd >> dir.txt && echo -n 'Final directory' >> log.txt && export TEST1=val1 && export TEST2=val2 && export TEST3='Complex Value' && env | grep TEST > env.txt && unset TEST1 && unset TEST2 && unset TEST3 && env | grep -v TEST > final_env.txt && echo -n 'Finished' || exit 1"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/usr'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'pwd'
Token 4: Type = REDIRECT_OUT, Value = '>'
Token 5: Type = STR_LITERAL, Value = 'dir.txt'
Token 6: Type = AND, Value = '&&'
Token 7: Type = CMD, Value = 'echo'
Token 8: Type = FLAG, Value = '-n'
Token 9: Type = STR_LITERAL, Value = 'Current directory'
Token 10: Type = REDIRECT_APPEND, Value = '>>'
Token 11: Type = STR_LITERAL, Value = 'log.txt'
Token 12: Type = AND, Value = '&&'
Token 13: Type = CMD, Value = 'cd'
Token 14: Type = STR_LITERAL, Value = '/var'
Token 15: Type = AND, Value = '&&'
Token 16: Type = CMD, Value = 'pwd'
Token 17: Type = REDIRECT_APPEND, Value = '>>'
Token 18: Type = STR_LITERAL, Value = 'dir.txt'
Token 19: Type = AND, Value = '&&'
Token 20: Type = CMD, Value = 'echo'
Token 21: Type = FLAG, Value = '-n'
Token 22: Type = STR_LITERAL, Value = 'Changed directory'
Token 23: Type = REDIRECT_APPEND, Value = '>>'
Token 24: Type = STR_LITERAL, Value = 'log.txt'
Token 25: Type = AND, Value = '&&'
Token 26: Type = CMD, Value = 'cd'
Token 27: Type = STR_LITERAL, Value = '/tmp'
Token 28: Type = AND, Value = '&&'
Token 29: Type = CMD, Value = 'pwd'
Token 30: Type = REDIRECT_APPEND, Value = '>>'
Token 31: Type = STR_LITERAL, Value = 'dir.txt'
Token 32: Type = AND, Value = '&&'
Token 33: Type = CMD, Value = 'echo'
Token 34: Type = FLAG, Value = '-n'
Token 35: Type = STR_LITERAL, Value = 'Final directory'
Token 36: Type = REDIRECT_APPEND, Value = '>>'
Token 37: Type = STR_LITERAL, Value = 'log.txt'
Token 38: Type = AND, Value = '&&'
Token 39: Type = CMD, Value = 'export'
Token 40: Type = STR_LITERAL, Value = 'TEST1=val1'
Token 41: Type = AND, Value = '&&'
Token 42: Type = CMD, Value = 'export'
Token 43: Type = STR_LITERAL, Value = 'TEST2=val2'
Token 44: Type = AND, Value = '&&'
Token 45: Type = CMD, Value = 'export'
Token 46: Type = STR_LITERAL, Value = 'TEST3=Complex Value'
Token 47: Type = AND, Value = '&&'
Token 48: Type = CMD, Value = 'env'
Token 49: Type = PIPE, Value = '|'
Token 50: Type = CMD, Value = 'grep'
Token 51: Type = STR_LITERAL, Value = 'TEST'
Token 52: Type = REDIRECT_OUT, Value = '>'
Token 53: Type = STR_LITERAL, Value = 'env.txt'
Token 54: Type = AND, Value = '&&'
Token 55: Type = CMD, Value = 'unset'
Token 56: Type = STR_LITERAL, Value = 'TEST1'
Token 57: Type = AND, Value = '&&'
Token 58: Type = CMD, Value = 'unset'
Token 59: Type = STR_LITERAL, Value = 'TEST2'
Token 60: Type = AND, Value = '&&'
Token 61: Type = CMD, Value = 'unset'
Token 62: Type = STR_LITERAL, Value = 'TEST3'
Token 63: Type = AND, Value = '&&'
Token 64: Type = CMD, Value = 'env'
Token 65: Type = PIPE, Value = '|'
Token 66: Type = CMD, Value = 'grep'
Token 67: Type = FLAG, Value = '-v'
Token 68: Type = STR_LITERAL, Value = 'TEST'
Token 69: Type = REDIRECT_OUT, Value = '>'
Token 70: Type = STR_LITERAL, Value = 'final_env.txt'
Token 71: Type = AND, Value = '&&'
Token 72: Type = CMD, Value = 'echo'
Token 73: Type = FLAG, Value = '-n'
Token 74: Type = STR_LITERAL, Value = 'Finished'
Token 75: Type = OR, Value = '||'
Token 76: Type = CMD, Value = 'exit'
Token 77: Type = STR_LITERAL, Value = '1'"
run_test "$test_name" "$input" "$expected_output"

# Test 22: Ultra long command with mixed operators
test_name="Ultra long command with mixed operators"
input="cd /usr || echo 'Failed cd 1' && pwd > out.txt || echo 'Failed pwd 1' && cd /var || echo 'Failed cd 2' && pwd >> out.txt || echo 'Failed pwd 2' && echo 'Success' || exit 1"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/usr'
Token 2: Type = OR, Value = '||'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'Failed cd 1'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'pwd'
Token 7: Type = REDIRECT_OUT, Value = '>'
Token 8: Type = STR_LITERAL, Value = 'out.txt'
Token 9: Type = OR, Value = '||'
Token 10: Type = CMD, Value = 'echo'
Token 11: Type = STR_LITERAL, Value = 'Failed pwd 1'
Token 12: Type = AND, Value = '&&'
Token 13: Type = CMD, Value = 'cd'
Token 14: Type = STR_LITERAL, Value = '/var'
Token 15: Type = OR, Value = '||'
Token 16: Type = CMD, Value = 'echo'
Token 17: Type = STR_LITERAL, Value = 'Failed cd 2'
Token 18: Type = AND, Value = '&&'
Token 19: Type = CMD, Value = 'pwd'
Token 20: Type = REDIRECT_APPEND, Value = '>>'
Token 21: Type = STR_LITERAL, Value = 'out.txt'
Token 22: Type = OR, Value = '||'
Token 23: Type = CMD, Value = 'echo'
Token 24: Type = STR_LITERAL, Value = 'Failed pwd 2'
Token 25: Type = AND, Value = '&&'
Token 26: Type = CMD, Value = 'echo'
Token 27: Type = STR_LITERAL, Value = 'Success'
Token 28: Type = OR, Value = '||'
Token 29: Type = CMD, Value = 'exit'
Token 30: Type = STR_LITERAL, Value = '1'"
run_test "$test_name" "$input" "$expected_output"

# Display final results
print_section_header "TEST RESULTS"
echo -e "${CYAN}Total tests: $TOTAL${NC}"
echo -e "${GREEN}Tests passed: $PASSED${NC}"
echo -e "${RED}Tests failed: $FAILED${NC}"

# Set exit code based on test results
if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed successfully!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi