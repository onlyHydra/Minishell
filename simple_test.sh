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

##################################################
# BASIC COMMAND AND FLAG TESTS
##################################################

# Test 1: Simple command without flags
test_name="Simple command without flags"
input="ls"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'"
run_test "$test_name" "$input" "$expected_output"

# Test 2: Simple command with single flag
test_name="Simple command with single flag"
input="ls -l"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'"
run_test "$test_name" "$input" "$expected_output"

# Test 3: Simple command with multiple flags
test_name="Simple command with multiple flags"
input="ls -la"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-la'"
run_test "$test_name" "$input" "$expected_output"

# Test 4: Command with separated flags
test_name="Command with separated flags"
input="ls -l -a"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = FLAG, Value = '-a'"
run_test "$test_name" "$input" "$expected_output"

# Test 5: Command with argument
test_name="Command with argument"
input="cat file.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 6: Command with long flag option
test_name="Command with long flag option"
input="ls --all"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '--all'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# QUOTE HANDLING TESTS (SINGLE AND DOUBLE QUOTES)
##################################################

# Test 7: Command with single quotes
test_name="Command with single quotes"
input="echo 'hello world'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

# Test 8: Command with double quotes
test_name="Command with double quotes"
input="echo \"hello world\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

# Test 9: Command with nested quotes (double within single)
test_name="Command with nested quotes (double within single)"
input="echo 'hello \"world\"'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello \"world\"'"
run_test "$test_name" "$input" "$expected_output"

# Test 10: Command with nested quotes (single within double)
test_name="Command with nested quotes (single within double)"
input="echo \"hello 'world'\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello \\'world\\''"
run_test "$test_name" "$input" "$expected_output"

# Test 11: Command with escaped quotes in double quotes
test_name="Command with escaped quotes in double quotes"
input="echo \"hello \\\"world\\\"\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello \"world\"'"
run_test "$test_name" "$input" "$expected_output"

# Test 12: Command with multiple quoted arguments
test_name="Command with multiple quoted arguments"
input="echo \"hello\" 'world'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = STR_LITERAL, Value = 'world'"
run_test "$test_name" "$input" "$expected_output"

# Test 13: Command with spaces in quotes
test_name="Command with spaces in quotes"
input="echo \"   spaced    content   \""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '   spaced    content   '"
run_test "$test_name" "$input" "$expected_output"

# Test 14: Command with empty quotes
test_name="Command with empty quotes"
input="echo \"\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = ''"
run_test "$test_name" "$input" "$expected_output"

# Test 15: Command with quotes containing special chars
test_name="Command with quotes containing special chars"
input="echo \"$HOME | > < ;\" 'test'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$HOME | > < ;'
Token 2: Type = STR_LITERAL, Value = 'test'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# PIPE TESTS
##################################################

# Test 16: Simple pipe
test_name="Simple pipe"
input="ls | wc"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'wc'"
run_test "$test_name" "$input" "$expected_output"

# Test 17: Multiple pipes
test_name="Multiple pipes"
input="ls -l | grep 'a' | wc -l"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'grep'
Token 4: Type = STR_LITERAL, Value = 'a'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'wc'
Token 7: Type = FLAG, Value = '-l'"
run_test "$test_name" "$input" "$expected_output"

# Test 18: Pipe with redirections
test_name="Pipe with redirections"
input="cat < file.txt | grep 'pattern' > results.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'file.txt'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'grep'
Token 5: Type = STR_LITERAL, Value = 'pattern'
Token 6: Type = OUT_REDIR, Value = '>'
Token 7: Type = STR_LITERAL, Value = 'results.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 19: Pipe with spaces
test_name="Pipe with spaces"
input="ls     |     wc    -l"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = PIPE, Value = '|'
Token 2: Type = CMD, Value = 'wc'
Token 3: Type = FLAG, Value = '-l'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# REDIRECTION TESTS
##################################################

# Test 20: Input redirection
test_name="Input redirection"
input="cat < input.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 21: Output redirection
test_name="Output redirection"
input="ls -l > output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = OUT_REDIR, Value = '>'
Token 3: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 22: Append output redirection
test_name="Append output redirection"
input="echo 'hello' >> log.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = APPEND_OUT, Value = '>>'
Token 3: Type = STR_LITERAL, Value = 'log.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 23: Multiple redirections in one command
test_name="Multiple redirections in one command"
input="cat < in.txt > out.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'in.txt'
Token 3: Type = OUT_REDIR, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'out.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 24: Redirection with quoted filename
test_name="Redirection with quoted filename"
input="grep 'pattern' < 'input file.txt'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'grep'
Token 1: Type = STR_LITERAL, Value = 'pattern'
Token 2: Type = IN_REDIR, Value = '<'
Token 3: Type = STR_LITERAL, Value = 'input file.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 25: Here document
test_name="Here document"
input="cat << EOF"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC, Value = '<<'
Token 2: Type = STR_LITERAL, Value = 'EOF'"
run_test "$test_name" "$input" "$expected_output"

# Test 26: Here string
test_name="Here string"
input="cat <<< 'hello world'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC_STR, Value = '<<<'
Token 2: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# LOGICAL OPERATORS TESTS
##################################################

# Test 27: Logical AND
test_name="Logical AND"
input="mkdir test && cd test"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'mkdir'
Token 1: Type = STR_LITERAL, Value = 'test'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'cd'
Token 4: Type = STR_LITERAL, Value = 'test'"
run_test "$test_name" "$input" "$expected_output"

# Test 28: Logical OR
test_name="Logical OR"
input="ls non_existent || echo 'Not found'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = STR_LITERAL, Value = 'non_existent'
Token 2: Type = OR, Value = '||'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'Not found'"
run_test "$test_name" "$input" "$expected_output"

# Test 29: Multiple logical operators
test_name="Multiple logical operators"
input="mkdir foo && cd foo || echo 'Failed'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'mkdir'
Token 1: Type = STR_LITERAL, Value = 'foo'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'cd'
Token 4: Type = STR_LITERAL, Value = 'foo'
Token 5: Type = OR, Value = '||'
Token 6: Type = CMD, Value = 'echo'
Token 7: Type = STR_LITERAL, Value = 'Failed'"
run_test "$test_name" "$input" "$expected_output"

# Test 30: Logical operators with redirections
test_name="Logical operators with redirections"
input="grep 'pattern' file.txt > results.txt && echo 'Success'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'grep'
Token 1: Type = STR_LITERAL, Value = 'pattern'
Token 2: Type = STR_LITERAL, Value = 'file.txt'
Token 3: Type = OUT_REDIR, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'results.txt'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'echo'
Token 7: Type = STR_LITERAL, Value = 'Success'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# ENVIRONMENT VARIABLE TESTS
##################################################

# Test 31: Simple environment variable
test_name="Simple environment variable"
input="echo $HOME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 32: Multiple environment variables
test_name="Multiple environment variables"
input="echo $USER $HOME $PATH"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = ENV_VAR, Value = '$HOME'
Token 3: Type = ENV_VAR, Value = '$PATH'"
run_test "$test_name" "$input" "$expected_output"

# Test 33: Environment variable in double quotes
test_name="Environment variable in double quotes"
input="echo \"Value: $HOME\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Value: $HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 34: Environment variable in single quotes (should be literal)
test_name="Environment variable in single quotes"
input="echo '$HOME'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '$HOME'"
run_test "$test_name" "$input" "$expected_output"

# Test 35: Environment variable with special characters
test_name="Environment variable with special characters"
input="echo $USER_NAME"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER_NAME'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# COMBINED AND COMPLEX COMMANDS
##################################################

# Test 36: Complex command with pipes and redirections
test_name="Complex command with pipes and redirections"
input="grep 'error' log.txt | sort | uniq > errors.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'grep'
Token 1: Type = STR_LITERAL, Value = 'error'
Token 2: Type = STR_LITERAL, Value = 'log.txt'
Token 3: Type = PIPE, Value = '|'
Token 4: Type = CMD, Value = 'sort'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'uniq'
Token 7: Type = OUT_REDIR, Value = '>'
Token 8: Type = STR_LITERAL, Value = 'errors.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 37: Command with logical operators and pipes
test_name="Command with logical operators and pipes"
input="ls -la | grep 'file' && echo 'Found' || echo 'Not found'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-la'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'grep'
Token 4: Type = STR_LITERAL, Value = 'file'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'echo'
Token 7: Type = STR_LITERAL, Value = 'Found'
Token 8: Type = OR, Value = '||'
Token 9: Type = CMD, Value = 'echo'
Token 10: Type = STR_LITERAL, Value = 'Not found'"
run_test "$test_name" "$input" "$expected_output"

# Test 38: Command with environment variables and redirections
test_name="Command with environment variables and redirections"
input="echo $USER > username.txt && cat username.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$USER'
Token 2: Type = OUT_REDIR, Value = '>'
Token 3: Type = STR_LITERAL, Value = 'username.txt'
Token 4: Type = AND, Value = '&&'
Token 5: Type = CMD, Value = 'cat'
Token 6: Type = STR_LITERAL, Value = 'username.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 39: Very complex command
test_name="Very complex command"
input="cat file.txt | grep 'pattern' | sort -r > results.txt && echo \"Done with $USER's job\" || echo 'Failed' > error.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file.txt'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'grep'
Token 4: Type = STR_LITERAL, Value = 'pattern'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'sort'
Token 7: Type = FLAG, Value = '-r'
Token 8: Type = OUT_REDIR, Value = '>'
Token 9: Type = STR_LITERAL, Value = 'results.txt'
Token 10: Type = AND, Value = '&&'
Token 11: Type = CMD, Value = 'echo'
Token 12: Type = STR_LITERAL, Value = 'Done with $USER\\'s job'
Token 13: Type = OR, Value = '||'
Token 14: Type = CMD, Value = 'echo'
Token 15: Type = STR_LITERAL, Value = 'Failed'
Token 16: Type = OUT_REDIR, Value = '>'
Token 17: Type = STR_LITERAL, Value = 'error.log'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# SPECIAL CASES AND EDGE CASES
##################################################

# Test 40: Command with backslash escapes
test_name="Command with backslash escapes"
input="echo hello\\ world"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello world'"
run_test "$test_name" "$input" "$expected_output"

# Test 41: Command with special characters
test_name="Command with special characters"
input="echo !@#$%^&*()"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '!@#$%^&*()'"
run_test "$test_name" "$input" "$expected_output"

# Test 42: Command with multiple spaces
test_name="Command with multiple spaces"
input="echo    hello     world"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = STR_LITERAL, Value = 'world'"
run_test "$test_name" "$input" "$expected_output"

# Test 43: Empty command
test_name="Empty command"
input=""
expected_output="Tokenization successful!"
run_test "$test_name" "$input" "$expected_output"

# Test 44: Command with only spaces
test_name="Command with only spaces"
input="     "
expected_output="Tokenization successful!"
run_test "$test_name" "$input" "$expected_output"

# Test 45: Command with semicolon (command separator)
test_name="Command with semicolon"
input="echo hello ; echo world"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = SEMICOLON, Value = ';'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'world'"
run_test "$test_name" "$input" "$expected_output"

# Test 46: Command with subshell
test_name="Command with subshell"
input="echo $(ls -l)"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = SUBSHELL, Value = '$(ls -l)'"
run_test "$test_name" "$input" "$expected_output"

# Test 47: Command with nested subshell
test_name="Command with nested subshell"
input="echo $(echo $(date))"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = SUBSHELL, Value = '$(echo $(date))'"
run_test "$test_name" "$input" "$expected_output"

# Test 48: Command with backquotes
test_name="Command with backquotes"
input="echo `ls -l`"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = SUBSHELL, Value = '`ls -l`'"
run_test "$test_name" "$input" "$expected_output"

# Test 49: Command with background process
test_name="Command with background process"
input="find / -name '*.txt' &"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'find'
Token 1: Type = STR_LITERAL, Value = '/'
Token 2: Type = FLAG, Value = '-name'
Token 3: Type = STR_LITERAL, Value = '*.txt'
Token 4: Type = BACKGROUND, Value = '&'"
run_test "$test_name" "$input" "$expected_output"

# Test 50: Command with wildcard
test_name="Command with wildcard"
input="ls *.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = STR_LITERAL, Value = '*.txt'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# ADDITIONAL COMPLEX CASES
##################################################

# Test 51: Multiple commands with semicolons and pipes
test_name="Multiple commands with semicolons and pipes"
input="echo hello ; ls -l | grep txt ; echo done"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = SEMICOLON, Value = ';'
Token 3: Type = CMD, Value = 'ls'
Token 4: Type = FLAG, Value = '-l'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'grep'
Token 7: Type = STR_LITERAL, Value = 'txt'
Token 8: Type = SEMICOLON, Value = ';'
Token 9: Type = CMD, Value = 'echo'
Token 10: Type = STR_LITERAL, Value = 'done'"
run_test "$test_name" "$input" "$expected_output"

# Test 52: Command with variable assignment
test_name="Command with variable assignment"
input="VAR=value echo $VAR"
expected_output="Tokenization successful!
Token 0: Type = ENV_ASSIGN, Value = 'VAR=value'
Token 1: Type = CMD, Value = 'echo'
Token 2: Type = ENV_VAR, Value = '$VAR'"
run_test "$test_name" "$input" "$expected_output"

# Test 53: Command with export
test_name="Command with export"
input="export VAR=value"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'export'
Token 1: Type = STR_LITERAL, Value = 'VAR=value'"
run_test "$test_name" "$input" "$expected_output"

# Test 54: Command with cd and tilde
test_name="Command with cd and tilde"
input="cd ~/Documents"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '~/Documents'"
run_test "$test_name" "$input" "$expected_output"

# Test 55: Complex multi-command line
test_name="Complex multi-command line"
input="cd ~/projects && make clean && make all > build.log ; echo 'Build complete' || echo 'Build failed' > error.log"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '~/projects'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'make'
Token 4: Type = STR_LITERAL, Value = 'clean'
Token 5: Type = AND, Value = '&&'
Token 6: Type = CMD, Value = 'make'
Token 7: Type = STR_LITERAL, Value = 'all'
Token 8: Type = OUT_REDIR, Value = '>'
Token 9: Type = STR_LITERAL, Value = 'build.log'
Token 10: Type = SEMICOLON, Value = ';'
Token 11: Type = CMD, Value = 'echo'
Token 12: Type = STR_LITERAL, Value = 'Build complete'
Token 13: Type = OR, Value = '||'
Token 14: Type = CMD, Value = 'echo'
Token 15: Type = STR_LITERAL, Value = 'Build failed'
Token 16: Type = OUT_REDIR, Value = '>'
Token 17: Type = STR_LITERAL, Value = 'error.log'"
run_test "$test_name" "$input" "$expected_output"

# Test 56: Command with arithmetic expansion
test_name="Command with arithmetic expansion"
input="echo $((2 + 2))"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ARITHMETIC, Value = '$((2 + 2))'"
run_test "$test_name" "$input" "$expected_output"

# Test 57: Command with history expansion
test_name="Command with history expansion"
input="!ls"
expected_output="Tokenization successful!
Token 0: Type = HISTORY, Value = '!ls'"
run_test "$test_name" "$input" "$expected_output"

# Test 58: Command with file descriptors
test_name="Command with file descriptors"
input="ls -l 2>/dev/null"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = FD_REDIR, Value = '2>'
Token 3: Type = STR_LITERAL, Value = '/dev/null'"
run_test "$test_name" "$input" "$expected_output"

# Test 59: Command with redirecting both stdout and stderr
test_name="Command with redirecting both stdout and stderr"
input="ls -l > output.txt 2>&1"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = OUT_REDIR, Value = '>'
Token 3: Type = STR_LITERAL, Value = 'output.txt'
Token 4: Type = FD_REDIR, Value = '2>&1'"
run_test "$test_name" "$input" "$expected_output"

# Test 60: Command with process substitution
test_name="Command with process substitution"
input="diff <(ls dir1) <(ls dir2)"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'diff'
Token 1: Type = PROC_SUB, Value = '<(ls dir1)'
Token 2: Type = PROC_SUB, Value = '<(ls dir2)'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH SPECIAL SHELL BUILT-INS
##################################################

# Test 61: Command with cd built-in
test_name="Command with cd built-in"
input="cd /usr/local/bin"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '/usr/local/bin'"
run_test "$test_name" "$input" "$expected_output"

# Test 62: Command with echo -n (no newline)
test_name="Command with echo -n"
input="echo -n Hello"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = FLAG, Value = '-n'
Token 2: Type = STR_LITERAL, Value = 'Hello'"
run_test "$test_name" "$input" "$expected_output"

# Test 63: Command with unset
test_name="Command with unset"
input="unset VAR1 VAR2"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'unset'
Token 1: Type = STR_LITERAL, Value = 'VAR1'
Token 2: Type = STR_LITERAL, Value = 'VAR2'"
run_test "$test_name" "$input" "$expected_output"

# Test 64: Command with exit status
test_name="Command with exit status"
input="echo $?"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$?'"
run_test "$test_name" "$input" "$expected_output"

# Test 65: Command with exit
test_name="Command with exit"
input="exit 0"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'exit'
Token 1: Type = STR_LITERAL, Value = '0'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH UNUSUAL SPACING AND FORMATTING
##################################################

# Test 66: Command with tabs
test_name="Command with tabs"
input="ls	-l	file.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = STR_LITERAL, Value = 'file.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 67: Command with mix of spaces and tabs
test_name="Command with mix of spaces and tabs"
input="echo	hello  	world"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = STR_LITERAL, Value = 'world'"
run_test "$test_name" "$input" "$expected_output"

# Test 68: Command with unusual spacing around operators
test_name="Command with unusual spacing around operators"
input="ls -l|wc -l>output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-l'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'wc'
Token 4: Type = FLAG, Value = '-l'
Token 5: Type = OUT_REDIR, Value = '>'
Token 6: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 69: Command with unusual spacing around redirections
test_name="Command with unusual spacing around redirections"
input="cat<input.txt>output.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input.txt'
Token 3: Type = OUT_REDIR, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output.txt'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH QUOTED SPECIAL CHARACTERS
##################################################

# Test 70: Command with quoted pipe
test_name="Command with quoted pipe"
input="echo '|'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '|'"
run_test "$test_name" "$input" "$expected_output"

# Test 71: Command with quoted redirections
test_name="Command with quoted redirections"
input="echo '<' '>' '>>'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '<'
Token 2: Type = STR_LITERAL, Value = '>'
Token 3: Type = STR_LITERAL, Value = '>>'"
run_test "$test_name" "$input" "$expected_output"

# Test 72: Command with quoted logical operators
test_name="Command with quoted logical operators"
input="echo '&&' '||'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '&&'
Token 2: Type = STR_LITERAL, Value = '||'"
run_test "$test_name" "$input" "$expected_output"

# Test 73: Command with quoted semicolon
test_name="Command with quoted semicolon"
input="echo ';'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = ';'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH COMBINATIONS OF QUOTES AND ESCAPES
##################################################

# Test 74: Command with escaped quotes in single quotes
test_name="Command with escaped quotes in single quotes"
input="echo 'Hello \\'world\\''"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Hello \\\\'world\\\\''"
run_test "$test_name" "$input" "$expected_output"

# Test 75: Command with escaped characters
test_name="Command with escaped characters"
input="echo \"Hello\\nWorld\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Hello\\nWorld'"
run_test "$test_name" "$input" "$expected_output"

# Test 76: Command with escaped spaces
test_name="Command with escaped spaces"
input="echo Hello\\ World"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Hello World'"
run_test "$test_name" "$input" "$expected_output"

# Test 77: Command with escaped special characters
test_name="Command with escaped special characters"
input="echo \\| \\> \\< \\& \\;"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = '|'
Token 2: Type = STR_LITERAL, Value = '>'
Token 3: Type = STR_LITERAL, Value = '<'
Token 4: Type = STR_LITERAL, Value = '&'
Token 5: Type = STR_LITERAL, Value = ';'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH EXECUTABLE PATHS
##################################################

# Test 78: Command with absolute path
test_name="Command with absolute path"
input="/bin/ls -l"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = '/bin/ls'
Token 1: Type = FLAG, Value = '-l'"
run_test "$test_name" "$input" "$expected_output"

# Test 79: Command with relative path
test_name="Command with relative path"
input="./script.sh arg1 arg2"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = './script.sh'
Token 1: Type = STR_LITERAL, Value = 'arg1'
Token 2: Type = STR_LITERAL, Value = 'arg2'"
run_test "$test_name" "$input" "$expected_output"

# Test 80: Command with parent directory path
test_name="Command with parent directory path"
input="../bin/program --option value"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = '../bin/program'
Token 1: Type = FLAG, Value = '--option'
Token 2: Type = STR_LITERAL, Value = 'value'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# VERY COMPLEX TESTS
##################################################

# Test 81: Complex command with quoted sections containing operators
test_name="Complex command with quoted sections containing operators"
input="echo \"This | has > pipes && and || other < operators\" > file.txt"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'This | has > pipes && and || other < operators'
Token 2: Type = OUT_REDIR, Value = '>'
Token 3: Type = STR_LITERAL, Value = 'file.txt'"
run_test "$test_name" "$input" "$expected_output"

# Test 82: Command with mixed quotes and environment variables
test_name="Command with mixed quotes and environment variables"
input="echo \"HOME=$HOME\" 'USER=$USER'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'HOME=$HOME'
Token 2: Type = STR_LITERAL, Value = 'USER=$USER'"
run_test "$test_name" "$input" "$expected_output"

# Test 83: Complex command with pipes, redirections, and environment variables
test_name="Complex command with pipes, redirections, and environment variables"
input="cd $HOME && ls -la | grep \".txt\" > result.txt || echo \"Not found\" > /dev/null 2>&1"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = ENV_VAR, Value = '$HOME'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'ls'
Token 4: Type = FLAG, Value = '-la'
Token 5: Type = PIPE, Value = '|'
Token 6: Type = CMD, Value = 'grep'
Token 7: Type = STR_LITERAL, Value = '.txt'
Token 8: Type = OUT_REDIR, Value = '>'
Token 9: Type = STR_LITERAL, Value = 'result.txt'
Token 10: Type = OR, Value = '||'
Token 11: Type = CMD, Value = 'echo'
Token 12: Type = STR_LITERAL, Value = 'Not found'
Token 13: Type = OUT_REDIR, Value = '>'
Token 14: Type = STR_LITERAL, Value = '/dev/null'
Token 15: Type = FD_REDIR, Value = '2>&1'"
run_test "$test_name" "$input" "$expected_output"

# Test 84: Command with multiple semicolons and logical operators
test_name="Command with multiple semicolons and logical operators"
input="mkdir test && cd test || echo 'Failed' ; touch file.txt && echo 'Created file' ; ls -la"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'mkdir'
Token 1: Type = STR_LITERAL, Value = 'test'
Token 2: Type = AND, Value = '&&'
Token 3: Type = CMD, Value = 'cd'
Token 4: Type = STR_LITERAL, Value = 'test'
Token 5: Type = OR, Value = '||'
Token 6: Type = CMD, Value = 'echo'
Token 7: Type = STR_LITERAL, Value = 'Failed'
Token 8: Type = SEMICOLON, Value = ';'
Token 9: Type = CMD, Value = 'touch'
Token 10: Type = STR_LITERAL, Value = 'file.txt'
Token 11: Type = AND, Value = '&&'
Token 12: Type = CMD, Value = 'echo'
Token 13: Type = STR_LITERAL, Value = 'Created file'
Token 14: Type = SEMICOLON, Value = ';'
Token 15: Type = CMD, Value = 'ls'
Token 16: Type = FLAG, Value = '-la'"
run_test "$test_name" "$input" "$expected_output"

# Test 85: Command with multiple redirections and quotes
test_name="Command with multiple redirections and quotes"
input="cat < 'input file.txt' > \"output file.txt\" 2> 'error.log'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = 'input file.txt'
Token 3: Type = OUT_REDIR, Value = '>'
Token 4: Type = STR_LITERAL, Value = 'output file.txt'
Token 5: Type = FD_REDIR, Value = '2>'
Token 6: Type = STR_LITERAL, Value = 'error.log'"
run_test "$test_name" "$input" "$expected_output"

# Test 86: Super complex command
test_name="Super complex command"
input="cd \"$HOME/projects\" && (make clean || echo \"Clean failed\") && make all > build.log 2>&1 ; cat build.log | grep -v \"warning\" | sort -r > filtered.log && echo \"Done!\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cd'
Token 1: Type = STR_LITERAL, Value = '$HOME/projects'
Token 2: Type = AND, Value = '&&'
Token 3: Type = PAREN_OPEN, Value = '('
Token 4: Type = CMD, Value = 'make'
Token 5: Type = STR_LITERAL, Value = 'clean'
Token 6: Type = OR, Value = '||'
Token 7: Type = CMD, Value = 'echo'
Token 8: Type = STR_LITERAL, Value = 'Clean failed'
Token 9: Type = PAREN_CLOSE, Value = ')'
Token 10: Type = AND, Value = '&&'
Token 11: Type = CMD, Value = 'make'
Token 12: Type = STR_LITERAL, Value = 'all'
Token 13: Type = OUT_REDIR, Value = '>'
Token 14: Type = STR_LITERAL, Value = 'build.log'
Token 15: Type = FD_REDIR, Value = '2>&1'
Token 16: Type = SEMICOLON, Value = ';'
Token 17: Type = CMD, Value = 'cat'
Token 18: Type = STR_LITERAL, Value = 'build.log'
Token 19: Type = PIPE, Value = '|'
Token 20: Type = CMD, Value = 'grep'
Token 21: Type = FLAG, Value = '-v'
Token 22: Type = STR_LITERAL, Value = 'warning'
Token 23: Type = PIPE, Value = '|'
Token 24: Type = CMD, Value = 'sort'
Token 25: Type = FLAG, Value = '-r'
Token 26: Type = OUT_REDIR, Value = '>'
Token 27: Type = STR_LITERAL, Value = 'filtered.log'
Token 28: Type = AND, Value = '&&'
Token 29: Type = CMD, Value = 'echo'
Token 30: Type = STR_LITERAL, Value = 'Done!'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH UNCOMMON OR EDGE CASES
##################################################

# Test 87: Command with only special characters
test_name="Command with only special characters"
input=">><<!@#$"
expected_output="Tokenization successful!
Token 0: Type = APPEND_OUT, Value = '>>'
Token 1: Type = IN_REDIR, Value = '<'
Token 2: Type = STR_LITERAL, Value = '!@#$'"
run_test "$test_name" "$input" "$expected_output"

# Test 88: Command with Unicode characters
test_name="Command with Unicode characters"
input="echo 'Hello, 世界!'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Hello, 世界!'"
run_test "$test_name" "$input" "$expected_output"

# Test 89: Command with very long string
test_name="Command with very long string"
input="echo 'This is a very long string that goes on and on and on and on and on and should still be tokenized correctly as a single string literal token despite its considerable length which might cause issues with buffers or other implementation details if not handled properly'"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'This is a very long string that goes on and on and on and on and on and should still be tokenized correctly as a single string literal token despite its considerable length which might cause issues with buffers or other implementation details if not handled properly'"
run_test "$test_name" "$input" "$expected_output"

# Test 90: Command with multiple operations of the same type
test_name="Command with multiple operations of the same type"
input="cat file1.txt file2.txt file3.txt | grep pattern | sort | uniq | wc -l"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file1.txt'
Token 2: Type = STR_LITERAL, Value = 'file2.txt'
Token 3: Type = STR_LITERAL, Value = 'file3.txt'
Token 4: Type = PIPE, Value = '|'
Token 5: Type = CMD, Value = 'grep'
Token 6: Type = STR_LITERAL, Value = 'pattern'
Token 7: Type = PIPE, Value = '|'
Token 8: Type = CMD, Value = 'sort'
Token 9: Type = PIPE, Value = '|'
Token 10: Type = CMD, Value = 'uniq'
Token 11: Type = PIPE, Value = '|'
Token 12: Type = CMD, Value = 'wc'
Token 13: Type = FLAG, Value = '-l'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH COMMAND SUBSTITUTION
##################################################

# Test 91: Command with command substitution using $()
test_name="Command with command substitution using $()"
input="echo $(date)"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = SUBSHELL, Value = '$(date)'"
run_test "$test_name" "$input" "$expected_output"

# Test 92: Command with complex command substitution
test_name="Command with complex command substitution"
input="echo $(ls -l | grep \".txt\")"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = SUBSHELL, Value = '$(ls -l | grep \".txt\")'"
run_test "$test_name" "$input" "$expected_output"

# Test 93: Command with multiple command substitutions
test_name="Command with multiple command substitutions"
input="echo $(date) $(whoami) $(pwd)"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = SUBSHELL, Value = '$(date)'
Token 2: Type = SUBSHELL, Value = '$(whoami)'
Token 3: Type = SUBSHELL, Value = '$(pwd)'"
run_test "$test_name" "$input" "$expected_output"

# Test 94: Command substitution with quotes
test_name="Command substitution with quotes"
input="echo \"Today is $(date)\""
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'Today is $(date)'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# TESTS WITH PARENTHESES
##################################################

# Test 95: Command with subshell using parentheses
test_name="Command with subshell using parentheses"
input="(cd /tmp && ls -l)"
expected_output="Tokenization successful!
Token 0: Type = PAREN_OPEN, Value = '('
Token 1: Type = CMD, Value = 'cd'
Token 2: Type = STR_LITERAL, Value = '/tmp'
Token 3: Type = AND, Value = '&&'
Token 4: Type = CMD, Value = 'ls'
Token 5: Type = FLAG, Value = '-l'
Token 6: Type = PAREN_CLOSE, Value = ')'"
run_test "$test_name" "$input" "$expected_output"

# Test 96: Command with nested parentheses
test_name="Command with nested parentheses"
input="(cd /tmp && (ls -l | grep txt))"
expected_output="Tokenization successful!
Token 0: Type = PAREN_OPEN, Value = '('
Token 1: Type = CMD, Value = 'cd'
Token 2: Type = STR_LITERAL, Value = '/tmp'
Token 3: Type = AND, Value = '&&'
Token 4: Type = PAREN_OPEN, Value = '('
Token 5: Type = CMD, Value = 'ls'
Token 6: Type = FLAG, Value = '-l'
Token 7: Type = PIPE, Value = '|'
Token 8: Type = CMD, Value = 'grep'
Token 9: Type = STR_LITERAL, Value = 'txt'
Token 10: Type = PAREN_CLOSE, Value = ')'
Token 11: Type = PAREN_CLOSE, Value = ')'"
run_test "$test_name" "$input" "$expected_output"

##################################################
# ADDITIONAL MISCELLANEOUS TESTS
##################################################

# Test 97: Command with function definition syntax
test_name="Command with function definition syntax"
input="function say_hello() { echo 'Hello World'; }"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'function'
Token 1: Type = STR_LITERAL, Value = 'say_hello()'
Token 2: Type = BRACE_OPEN, Value = '{'
Token 3: Type = CMD, Value = 'echo'
Token 4: Type = STR_LITERAL, Value = 'Hello World'
Token 5: Type = SEMICOLON, Value = ';'
Token 6: Type = BRACE_CLOSE, Value = '}'"
run_test "$test_name" "$input" "$expected_output"

# Test 98: Command with multiline input (heredoc-like)
test_name="Command with multiline input"
input="cat << EOF
Line 1
Line 2
EOF"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'cat'
Token 1: Type = HEREDOC, Value = '<<'
Token 2: Type = STR_LITERAL, Value = 'EOF'"
run_test "$test_name" "$input" "$expected_output"

# Test 99: Command with comments
test_name="Command with comments"
input="echo hello # this is a comment"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = COMMENT, Value = '# this is a comment'"
run_test "$test_name" "$input" "$expected_output"

# Test 100: Test with special script variables
test_name="Test with special script variables"
input="echo $0 $1 $2 $#"
expected_output="Tokenization successful!
Token 0: Type = CMD, Value = 'echo'
Token 1: Type = ENV_VAR, Value = '$0'
Token 2: Type = ENV_VAR, Value = '$1'
Token 3: Type = ENV_VAR, Value = '$2'
Token 4: Type = ENV_VAR, Value = '$#'"
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
    echo -e "${GREEN}All tests passed! Your minishell tokenization is working correctly.${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed! Your minishell tokenization needs improvement.${NC}"
    exit 1
fi
