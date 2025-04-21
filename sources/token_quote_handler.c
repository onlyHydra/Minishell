

#include "header.h"

/**
 * This function handles input that has no quotes at all
 * example: echo hello there && ls -l
 * @param input: input string
 * @param tokens: pointer to token list
 * @param i: index of input to start
 *
 * @return index of the last processed character
 */
int	handle_without_quotes(char *input, t_token **tokens, int i, char **envp)
{
	int				j;
	char			*token;
	t_token_type	token_type;

	j = i;
	// Skip leading whitespace
	while (input[j] && (input[j] == ' ' || input[j] == '\t'))
		j++;
	if (j > i)
		i = j; // Update starting position after whitespace
	// Check if we're at an operator
	if (is_operator_char(input[j]))
	{
		// Handle compound operators (>>, <<, &&, ||)
		if ((input[j] == '>' && input[j + 1] == '>') || (input[j] == '<'
				&& input[j + 1] == '<') || (input[j] == '&' && input[j
				+ 1] == '&') || (input[j] == '|' && input[j + 1] == '|'))
		{
			token = extract_token(input, j, j + 2);
			add_token(tokens, token, decide_token_type(token, envp));
			return (j + 1); // +1 because the caller will increment again
		}
		// Single character operator
		token = extract_token(input, j, j + 1);
		add_token(tokens, token, decide_token_type(token, envp));
		return (j); // Return the current position
	}
	// Handle a regular word (command or argument)
	j = i;
	while (input[j] && !is_operator_char(input[j]) && input[j] != ' '
		&& input[j] != '\t' && input[j] != '\'' && input[j] != '"')
	{
		j++;
	}
	// If we found a non-empty word
	if (j > i)
	{
		token = extract_token(input, i, j);
		token_type = decide_token_type(token, envp);
		add_token(tokens, token, token_type);
	}
	return (j);
}

/**
 * Check if a quote is closed properly
 * @param str: The string to check
 * @param start: Starting index of the quote
 * @param quote_char: The quote character to match (' or ")
 * @return: 1 if closed properly, 0 if unclosed
 */
int	is_quote_closed(char *str, int start, char quote_char)
{
	int i = start + 1; // Skip the opening quote
	while (str[i] && str[i] != quote_char)
		i++;
	return (str[i] == quote_char);
}

/**
 * Handles parsing of quoted strings with proper error detection
 * @param str: The string to parse
 * @param i: Current index in the string
 * @param quote_type: Type of quote (single or double)
 * @param error: Pointer to store error status (1 for error, 0 for success)
 * @return: The ending index of the quoted string
 */
int	handle_quoted_string(char *str, int i, t_token_type quote_type, int *error)
{
	char	quote_char;

	if (quote_type == SINGLE_QUOTE)
		quote_char = '\'';
	else
		quote_char = '"';
	if (!is_quote_closed(str, i, quote_char))
	{
		*error = 1;
		return (i);
	}
	i++;
	while (str[i] && str[i] != quote_char)
		i++;
	if (str[i] == quote_char)
		i++;
	return (i);
}

/**
 * Handle quoted strings in the input
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_quotes(char *input, t_parse_state *state, char **envp)
{
	char			*token_value;
	t_token_type	quote_type;
	int				end;
	t_token_type	token_type;

	if (input[state->i] == '\'' || input[state->i] == '"')
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i, envp);
		quote_type = (input[state->i] == '\'') ? SINGLE_QUOTE : DOUBLE_QUOTE;
		end = handle_quoted_string(input, state->i, quote_type, &state->error);
		if (state->error)
		{
			printf("Error: Unclosed %s quote.\n",
				(quote_type == SINGLE_QUOTE) ? "single" : "double");
			return (1);
		}
		token_value = extract_token(input, state->i + 1, end - 1);
		// Determine token type using decide_token_type
		token_type = decide_token_type(token_value, envp);
		// Override for first token if needed
		if (state->is_first_token)
		{
			token_type = CMD;
			state->is_first_token = 0;
		}
		add_token(state->tokens, token_value, token_type);
		state->i = end;
		state->start = state->i;
		return (1);
	}
	return (0);
}
