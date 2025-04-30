# Minishell Environmental Variables Guide

## Introduction

Environmental variables are key-value pairs that are part of the shell's environment. They affect the behavior of programs and provide a way to store and share configuration information between processes. This guide explains how environmental variables work in a shell and provides test cases for your Minishell implementation.

## Core Concepts

### What are Environmental Variables?

Environmental variables are dynamic named values that can affect the behavior of running processes on a computer. They exist in an environment and are inherited by child processes from their parent. In a shell:

- They are typically represented as `NAME=VALUE` pairs
- They can be accessed using the `$NAME` syntax
- They are passed to commands that are executed
- They can be manipulated with shell commands like `export`, `unset`, and `env`

### Key Operations

Your Minishell implementation needs to handle these operations:

1. **Initialization**: Load environment variables from `envp` when your shell starts
2. **Storage**: Store variables in an appropriate data structure (linked list or hash map)
3. **Access**: Allow expansion of variables in command input (e.g., `$HOME`, `$USER`)
4. **Modification**: Support the `export` command to create or modify variables
5. **Removal**: Support the `unset` command to remove variables
6. **Display**: Support the `env` command to display the current environment
7. **Passing**: Pass the current environment to executed commands
8.

## How Environment Variables Work in a Shell

### Initial Environment

When your shell starts, it receives the current environment from its parent process via the `envp` parameter of `main()`. This is an array of strings, each with format `NAME=VALUE`, terminated by a NULL pointer.

### Variable Types

In a standard shell, there are two types of variables:

1. **Environment Variables**: Exported to child processes
2. **Shell Variables**: Local to the shell, not exported

In your Minishell, you'll need to track which variables should be passed to child processes.

### Expansion

When a command contains a variable reference like `$HOME`, the shell replaces it with the variable's value before executing the command. This is called "expansion."

- `echo $HOME` should print the value of HOME, not the string "$HOME"
- `echo "$HOME"` should also print the value (with quotes preserved if needed)
- `echo '$HOME'` should print the literal string "$HOME" (single quotes prevent expansion)

### Special Variables

Some variables have special meaning:

- `$?` - Contains the exit status of the last executed command
- `$$` - Contains the process ID of the shell

Your implementation should handle these correctly.

## Built-in Commands for Environment Variables

### `export`

The `export` command creates a new environment variable or modifies an existing one.

Syntax:
- `export` (displays all exported variables)
- `export NAME=VALUE` (sets a variable and marks it for export)
- `export NAME` (marks an existing variable for export)

Multiple assignments can be specified: `export NAME1=VALUE1 NAME2=VALUE2`

### `unset`

The `unset` command removes variables from the environment.

Syntax:
- `unset NAME` (removes the variable)
- `unset NAME1 NAME2` (removes multiple variables)

### `env`

The `env` command displays all environment variables (exported variables).

Syntax:
- `env` (displays all environment variables)

## Test Cases and Expected Outputs

Here are test cases for your Minishell implementation with expected outputs:

### Test 1: Basic Variable Access

```
minishell> echo $HOME
/home/username
```

### Test 2: Setting and Accessing a Variable

```
minishell> export TEST=hello
minishell> echo $TEST
hello
```

### Test 3: Variable Expansion in Strings

```
minishell> export NAME=World
minishell> echo "Hello $NAME!"
Hello World!
```

### Test 4: Single Quotes Prevent Expansion

```
minishell> export NAME=World
minishell> echo 'Hello $NAME!'
Hello $NAME!
```

### Test 5: Multiple Variable Expansion

```
minishell> export FIRST=Hello
minishell> export SECOND=World
minishell> echo "$FIRST $SECOND!"
Hello World!
```

### Test 6: Variable Modification

```
minishell> export PATH=/usr/bin
minishell> echo $PATH
/usr/bin
minishell> export PATH=/usr/local/bin:$PATH
minishell> echo $PATH
/usr/local/bin:/usr/bin
```

### Test 7: Unsetting Variables

```
minishell> export TEMP=value
minishell> echo $TEMP
value
minishell> unset TEMP
minishell> echo $TEMP

```

### Test 8: Environment Display

```
minishell> export TEST1=value1
minishell> export TEST2=value2
minishell> env | grep TEST
TEST1=value1
TEST2=value2
```

### Test 9: Exit Status Variable

```
minishell> ls /nonexistent_directory
ls: cannot access '/nonexistent_directory': No such file or directory
minishell> echo $?
2
minishell> ls /home
[directory contents]
minishell> echo $?
0
```

### Test 10: Variable in Command Execution

```
minishell> export DIR=/tmp
minishell> cd $DIR
minishell> pwd
/tmp
```

### Test 11: Multiple Exports at Once

```
minishell> export A=1 B=2 C=3
minishell> echo $A $B $C
1 2 3
```

### Test 12: Export Without Value

```
minishell> TEST=hidden
minishell> export | grep TEST
[no output]
minishell> export TEST
minishell> export | grep TEST
declare -x TEST="hidden"
```

### Test 13: Variable with Spaces

```
minishell> export MESSAGE="Hello World"
minishell> echo $MESSAGE
Hello World
```

### Test 14: Nested Variable Expansion

```
minishell> export A=B
minishell> export B=C
minishell> echo ${!A}
C
```
(Note: This kind of nested expansion is advanced and may not be required for basic implementation)

### Test 15: Commands Using Environment

```
minishell> export GREP_OPTIONS="--color=auto"
minishell> grep "something" file.txt
[results with colorized output]
```

## Edge Cases to Handle

1. **Empty Variables**
```
minishell> export EMPTY=
minishell> echo "Value: '$EMPTY'"
Value: ''
```

2. **Variable Not Found**
```
minishell> echo $NONEXISTENT

```

3. **Partial Expansion**
```
minishell> export PART=value
minishell> echo $PART_EXTRA
[empty line - as PART_EXTRA doesn't exist]
```

4. **Preserving Quotes in Values**
```
minishell> export MSG="Hello \"World\""
minishell> echo $MSG
Hello "World"
```

5. **Variable at End of String**
```
minishell> export END=end
minishell> echo "The $END"
The end
```

## Implementation Checklist

- [ ] Parse initial environment from `envp`
- [ ] Create data structure for storing variables
- [ ] Implement variable expansion in command processing
- [ ] Implement the `export` built-in
- [ ] Implement the `unset` built-in
- [ ] Implement the `env` built-in
- [ ] Set up environment passing for command execution
- [ ] Handle special variables like `$?`
- [ ] Handle edge cases and error conditions

## Notes for Testing

When writing your implementation:

1. Test incrementally, starting with basic functionality
2. Compare your shell's behavior with bash for reference
3. Make sure to handle error cases (invalid variable names, etc.)
4. Test with variables that have special characters
5. Verify environment is properly passed to executed commands

For testing environment passage to commands, create a simple C program that prints its environment:

```c
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
```

Compile this and use it to verify your environment variables are correctly passed to child processes.

## Advanced Topics (If Time Permits)

- Implement subshell variable scoping
- Handle variable expansions in command arguments
- Support for more complex expansions (${VAR:-default}, etc.)
- Handle the export of functions
- Implement locale variables
