# Minishell Tokenizer Test Suite - Usage Guide

This document explains how to use the tokenizer test scripts to validate your minishell tokenizer implementation.

## Overview

The test suite consists of three separate scripts that test your tokenizer at different complexity levels:

1. `basic-tokenizer-tests.sh` - Tests simple commands, quotes, and basic features
2. `intermediate-tokenizer-tests.sh` - Tests redirections, pipes, and environment variables
3. `advanced-tokenizer-tests.sh` - Tests complex cases, edge conditions, and bonus features

## Prerequisites

Before running the tests, ensure:

1. Your `minishell` executable is built and in the current directory
2. Your tokenizer outputs results in the expected format:
   ```
   Tokenization successful!
   Token 0: Type = CMD, Value = 'command'
   Token 1: Type = FLAG, Value = '-flag'
   ...
   ```

## Running the Tests

Make the test scripts executable:

```bash
chmod +x basic-tokenizer-tests.sh
chmod +x intermediate-tokenizer-tests.sh
chmod +x advanced-tokenizer-tests.sh
```

Run the tests in sequence:

```bash
./basic-tokenizer-tests.sh
./intermediate-tokenizer-tests.sh
./advanced-tokenizer-tests.sh
```

## Test Results

Each test script:
- Displays each test case and its input
- Shows passed/failed status for each test
- Displays a summary with total pass percentage
- Returns exit code 0 if all tests pass, 1 otherwise

## Customizing Tests

- If your token format differs, modify the `run_test()` function in each script
- Add new test cases by following the existing test pattern:
  ```bash
  test_name="Description"
  input="command to test"
  expected_output="Expected tokens"
  run_test "$test_name" "$input" "$expected_output"
  ```

## Troubleshooting

If tests fail:
1. Check that your token format matches the expected format
2. Verify your executable handles all the required parsing cases
3. Look at the specific tests that failed to identify the issue
