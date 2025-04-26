#!/bin/bash

MINISHELL_PATH=./minishell

echo "===== MINISHELL NO-QUOTE TOKENIZER TESTER ====="
echo "Started at: $(date)"
echo "-----------------------------------------------"
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Define tests
declare -a TEST_INPUTS=(
    "echo hello"
    "ls -la"
    "cat file.txt"
    "echo hello world this is a test"
    "grep something file.txt"
    "mkdir new_folder"
    "rm -rf some_folder"
    "touch file1 file2 file3"
    "cp file1 file2"
    "echo hello | wc -l"
	
)

declare -a EXPECTED_OUTPUTS=(
"Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'"

"Token 0: Type = CMD, Value = 'ls'
Token 1: Type = FLAG, Value = '-la'"

"Token 0: Type = CMD, Value = 'cat'
Token 1: Type = STR_LITERAL, Value = 'file.txt'"

"Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = STR_LITERAL, Value = 'world'
Token 3: Type = STR_LITERAL, Value = 'this'
Token 4: Type = STR_LITERAL, Value = 'is'
Token 5: Type = STR_LITERAL, Value = 'a'
Token 6: Type = STR_LITERAL, Value = 'test'"

"Token 0: Type = CMD, Value = 'grep'
Token 1: Type = STR_LITERAL, Value = 'something'
Token 2: Type = STR_LITERAL, Value = 'file.txt'"

"Token 0: Type = CMD, Value = 'mkdir'
Token 1: Type = STR_LITERAL, Value = 'new_folder'"

"Token 0: Type = CMD, Value = 'rm'
Token 1: Type = FLAG, Value = '-rf'
Token 2: Type = STR_LITERAL, Value = 'some_folder'"

"Token 0: Type = CMD, Value = 'touch'
Token 1: Type = STR_LITERAL, Value = 'file1'
Token 2: Type = STR_LITERAL, Value = 'file2'
Token 3: Type = STR_LITERAL, Value = 'file3'"

"Token 0: Type = CMD, Value = 'cp'
Token 1: Type = STR_LITERAL, Value = 'file1'
Token 2: Type = STR_LITERAL, Value = 'file2'"

"Token 0: Type = CMD, Value = 'echo'
Token 1: Type = STR_LITERAL, Value = 'hello'
Token 2: Type = PIPE, Value = '|'
Token 3: Type = CMD, Value = 'wc'
Token 4: Type = FLAG, Value = '-l'"
)

# Run tests
for i in "${!TEST_INPUTS[@]}"; do
    TEST="${TEST_INPUTS[$i]}"
    EXPECTED="${EXPECTED_OUTPUTS[$i]}"

    echo "[TEST $((i+1))] \"$TEST\""

    # Capture output
    ACTUAL=$($MINISHELL_PATH $TEST 2>/dev/null)

    echo "[Comparing Output]"
    echo "Expected:"
    echo "$EXPECTED"
    echo "Actual:"
    echo "$ACTUAL"

    if [[ "$ACTUAL" == "$EXPECTED" ]]; then
        echo -e "${GREEN}✅ TEST PASSED${NC}"
    else
        echo -e "${RED}❌ TEST FAILED${NC}"
    fi

    echo ""
done

echo "===== NO-QUOTE MINISHELL TOKENIZER TESTER ====="
echo "Started at: $(date)"
echo "-------------------------------------"

# Path to your minishell binary
MINISHELL=./minishell

# Define test inputs (no quotes anywhere)
TEST_INPUTS=(
    "echo hello there my name is john | cat looooooong_filleeeeeeeeeeeeeeeeeeename.txt"
    "echo this is a very very very very long message with multiple parts and lots of words | wc -w"
    "ls -l /usr /bin /etc | grep conf"
    "cat input.txt | sort | uniq | tee output.txt"
    "ping google.com -c 4 && echo done"
    "mkdir folder1 folder2 folder3 && ls"
    "rm -rf test_folder && echo removed test_folder"
    "grep pattern file1 file2 file3 | wc -l"
    "touch fileA fileB fileC ; ls -l"
    "cd .. && pwd || echo failed"
    "cp fileA.txt backup_fileA.txt && echo backup complete"
    "echo warning this is not a drill && echo this is a test"
    "cat < input.txt > output.txt"
    "echo 1 2 3 4 5 6 7 8 9 10 | awk '{print \$NF}'"
    "head -n 5 looooooong_filleeeeeeeeeeeeeeeeeeename.txt"
    "echo hello | grep h | wc -l"
    "yes this should be enough to stress test the token stream | head -n 100"
    "echo this    has      weird         spacing         and     it    keeps    going"
    "echo okay now test averyveryveryveryverylongwordfollowedbyanotherlongwordinthisline"
    "command_that_doesnt_exist arg1 arg2 arg3"
)

# Loop through all test inputs
i=1
for input in "${TEST_INPUTS[@]}"; do
    echo
    echo "[TEST $i:] $input"
    
    # Run minishell with input
    OUTPUT=$($MINISHELL $input 2>&1)
    
    # Show result
    echo "[Output]"
    echo "$OUTPUT"
    
    # Check for memory leaks with valgrind (optional, remove if you don't need it)
    # valgrind --leak-check=full --error-exitcode=1 $MINISHELL $input > /dev/null 2>&1
    # if [ $? -eq 0 ]; then
    #     echo "✅ No memory leaks"
    # else
    #     echo "❌ Memory leak detected"
    # fi

    i=$((i + 1))
done

echo
echo "========== TESTING COMPLETE =========="

#!/bin/bash

echo "===== QUOTE-COMBO MINISHELL TESTER ====="
echo "Started at: $(date)"
echo "----------------------------------------"

MINISHELL=./minishell

TEST_INPUTS=(
    "echo 'hello there' | cat \"filename\" && echo 'HEEELLLOOOOOOOOOOOOO TEH DIUKJJUDBHUIUIHWB RAAAAAAAAAAAAAAMDDDDDDDDDDOOOOOOOM________\$\$\$\$\$\$\$\$NSVARRRRRRR'"
    "echo 'a quick brown fox' | grep quick && echo 'PASS' || echo 'FAIL'"
    "echo 'string with symbols !@#%&*()_+' | cat \"somefile.txt\""
    "echo 'START' | grep 'S' && echo \"Processing Done\" ; echo 'Cleanup done'"
    "echo 'multi     spaced     words' | tr -s ' ' && echo \"Done\""
    "echo '1 2 3 4' | awk '{print \$3}' && echo \"Extracted\""
    "echo 'pipe test' | cat -e | grep '\\\$' && echo 'final step'"
    "echo 'a' 'b' 'c' 'd' | wc -w && echo 'Word count complete'"
    "echo 'just \"nested\" quotes test' | cat \"logfile.txt\""
    "echo 'END START' | rev && echo \"REVERSED\""
)

i=1
for input in "${TEST_INPUTS[@]}"; do
    echo
    echo "[TEST $i:] $input"
    OUTPUT=$($MINISHELL $input 2>&1)
    echo "[Output]"
    echo "$OUTPUT"
    i=$((i + 1))
done

echo
echo "========== COMBO TESTS COMPLETE =========="

