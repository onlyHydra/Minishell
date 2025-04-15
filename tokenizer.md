# Minishell Tokenization

This document outlines the tokenization process for the Minishell project, explaining how the shell input is broken down into meaningful tokens that can be processed by the parser.

## Tokenization Overview

Tokenization is the first step in processing shell commands. It breaks the input string into tokens that represent distinct elements of the command, while respecting shell syntax rules like quotes and special characters.

### Token Types

Our tokenizer will identify these token types:

1. **WORD** - Command names, arguments, filenames
2. **PIPE** - Pipe character `|`
3. **REDIRECT_IN** - Input redirection `<`
4. **REDIRECT_OUT** - Output redirection `>`
5. **REDIRECT_APPEND** - Append redirection `>>`
6. **HEREDOC** - Here document `<<`
7. **ENV_VAR** - Environment variable (starting with `$`)
8. **EXIT_STATUS** - Exit status variable `$?`
9. **QUOTES** - Content within quotes (preserving the quote type information)

## Tokenization Algorithm

1. **Input Processing**: Read the input character by character
2. **State Management**: Use a state machine to track the current context
3. **Token Building**: Accumulate characters into tokens based on rules
4. **Special Handling**: Apply special rules for quotes, variables, etc.

### State Machine

The tokenizer will maintain these states:

- **NORMAL** - Processing regular text
- **IN_SINGLE_QUOTE** - Inside single quotes (no interpretation)
- **IN_DOUBLE_QUOTE** - Inside double quotes (interpret $)
- **IN_ENV_VAR** - Processing an environment variable

## Quote Handling

- **Single quotes (`'`)**: Text inside is taken literally with no special character interpretation
- **Double quotes (`"`)**: Text inside is taken literally except for `$` which expands variables

## Variable Expansion

- **Environment variables**: `$VAR` expands to the value of the environment variable
- **Exit status**: `$?` expands to the exit status of the last command

## Special Character Handling

- **Pipe (`|`)**: Separates commands for piping
- **Redirections**: Handle `<`, `>`, `<<`, `>>` as separate tokens
- **Whitespace**: Acts as token separator in normal state

## Implementation Flow

```
1. Initialize tokenizer state
2. For each character in input:
   - Handle based on current state and character
   - Update state if needed
   - Add character to current token or finalize token
3. Handle any remaining token
4. Perform variable expansion
```

## Tokenizer Interface

```c
typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_HEREDOC,
    TOKEN_ENV_VAR,
    TOKEN_EXIT_STATUS,
    // Add other types as needed
} t_token_type;

typedef struct s_token {
    char *value;
    t_token_type type;
    struct s_token *next;
} t_token;

t_token *tokenize(char *input);
void free_tokens(t_token *tokens);
```

## Algorithm Visualization

The tokenization process can be visualized as a graph where:
- Nodes represent states
- Edges represent transitions based on input characters
- Special nodes handle token creation and state resets

## Edge Cases

- **Empty input**: Return no tokens
- **Unclosed quotes**: Handle as error
- **Consecutive operators**: Tokenize separately
- **Leading/trailing whitespace**: Ignore
- **Escaped characters**: Not required by subject
- **Null character in input**: Terminate token

## Testing Strategy

1. Test basic command parsing
2. Test quotes (both types)
3. Test environment variable expansion
4. Test redirections and pipes
5. Test combinations of the above
6. Test error cases (e.g., unclosed quotes)

## Example Tokenization

Input: `echo "Hello $USER" > output.txt | grep "Hi"`

Tokens:
1. WORD: "echo"
2. WORD: "Hello $USER" (with variable expansion inside quotes)
3. REDIRECT_OUT: ">"
4. WORD: "output.txt"
5. PIPE: "|"
6. WORD: "grep"
7. WORD: "Hi" (in quotes)
