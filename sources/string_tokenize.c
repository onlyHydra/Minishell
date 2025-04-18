/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 17:59:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Check if a character is an operator
 * @param c: The character to check
 * @return: 1 if it's an operator, 0 otherwise
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
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
 * Handle backslash escapes in the input string
 * @param input: The input string
 * @param processed: The output string with processed escapes
 * @return: The processed string with escapes handled
 */
char	*handle_escapes(char *input)
{
	int		i;
	int		j;
	char	*processed;

	i = 0;
	j = 0;
	processed = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!processed)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1])
		{
			i++;
			processed[j++] = input[i++];
		}
		else
			processed[j++] = input[i++];
	}
	processed[j] = '\0';
	return (processed);
}

/**
 * Process a normal token and add it to the token list
 * @param input: Input string
 * @param state: Parsing state
 * @param end: End position of token
 */
void	process_token(char *input, t_parse_state *state, int end)
{
	char			*token_value;
	char			*processed_token;
	t_token_type	token_type;

	token_value = extract_token(input, state->start, end);
	processed_token = handle_escapes(token_value);
	free(token_value);
	if (processed_token && processed_token[0] == '-')
		token_type = FLAG;
	else
		token_type = CMD;
	add_token(state->tokens, processed_token, token_type);
	state->in_word = 0;
}

/**
 * Handle whitespace in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_whitespace(char *input, t_parse_state *state)
{
	if (input[state->i] == ' ' || input[state->i] == '\t')
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i);
		(state->i)++;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle backslash escapes in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_backslash(char *input, t_parse_state *state)
{
	if (input[state->i] == '\\' && input[state->i + 1])
	{
		if (!state->in_word)
		{
			state->in_word = 1;
			state->start = state->i;
		}
		state->i += 2;
		return (1);
	}
	return (0);
}

/**
 * Handle quoted strings in the input
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_quotes(char *input, t_parse_state *state)
{
	char			*token_value;
	t_token_type	quote_type;
	int				end;
	t_token_type	token_type;

	if (input[state->i] == '\'' || input[state->i] == '"')
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i);
		quote_type = (input[state->i] == '\'') ? SINGLE_QUOTE : DOUBLE_QUOTE;
		end = handle_quoted_string(input, state->i, quote_type, &state->error);
		if (state->error)
		{
			printf("Error: Unclosed %s quote.\n",
				(quote_type == SINGLE_QUOTE) ? "single" : "double");
			return (1);
		}
		token_value = extract_token(input, state->i + 1, end - 1);
		// Determine token type - could be FLAG if starts with '-'
		token_type = CMD;
		if (token_value && token_value[0] == '-')
			token_type = FLAG;
		add_token(state->tokens, token_value, token_type);
		state->i = end;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle environment variables
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_env_vars(char *input, t_parse_state *state)
{
	int	end;

	if (input[state->i] == '$')
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i);
		end = state->i + 1;
		while (input[end] && (ft_isalnum(input[end]) || input[end] == '_'))
			end++;
		if (input[state->i + 1] == '?')
		{
			add_token(state->tokens, extract_token(input, state->i, state->i
					+ 2), EXIT_STATUS);
			end = state->i + 2;
		}
		else
			add_token(state->tokens, extract_token(input, state->i, end),
				ENV_VAR);
		state->i = end;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * helper function for string tokenazation
 * @param input: The input string to tokenize
 * @param state: The state struct
 * @return: Linked list of tokens, or NULL if there's a syntax error
 */
int	handle_rest_cases(char *input, t_parse_state *state)
{
	if (handle_quotes(input, state))
	{
		if (state->error)
			return (0);
		return (1);
	}
	if (handle_operators(input, state))
		return (1);
	if (handle_env_vars(input, state))
		return (1);
	if (!state->in_word)
	{
		state->in_word = 1;
		state->start = state->i;
	}
	return (0);
}

/**
 * Check if the current token is likely a command
 * @param input: The input string to tokenize
 * @param state: Current parsing state
 * @return: 1 if it's a command, 0 otherwise
 */
int	check_for_cmd(char *input, t_parse_state *state)
{
	int	i;

	i = state->i;
	// Skip leading whitespace
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	// Check if we're at the start of a new command segment
	if (i == 0 || input[i - 1] == '|' || input[i - 1] == ';' || input[i
		- 1] == '>' || input[i - 1] == '<')
	{
		// If we're at a valid character (not an operator or quote)
		if (input[i] && input[i] != '|' && input[i] != ';' && input[i] != '>'
			&& input[i] != '<' && input[i] != '\'' && input[i] != '"')
		{
			return (1);
		}
	}
	return (0);
}

/**
 * Identify if a token is a flag
 * @param token: The token string
 * @return: 1 if it's a flag, 0 otherwise
 */
int	is_flag(char *token)
{
	return (token && token[0] == '-');
}

/**
 * Tokenize the strings that come after the cmd,
 * this can be 1. Options/Flags 2. some kind of a file_name 3. operators.
 * @param input: The input string to tokenize
 * @param state: Current parsing state
 * @return: the token with valid information
 */
t_token	*handle_follow_up_cmd(char *input, t_parse_state *state)
{
	char			*token_value;
	t_token_type	token_type;

	// Skip whitespace
	while (input[state->i] && (input[state->i] == ' '
			|| input[state->i] == '\t'))
		(state->i)++;
	state->start = state->i;
	// Process the command token
	while (input[state->i] && input[state->i] != ' ' && input[state->i] != '\t'
		&& input[state->i] != '|' && input[state->i] != '<'
		&& input[state->i] != '>' && input[state->i] != '\''
		&& input[state->i] != '"')
	{
		(state->i)++;
	}
	if (state->start < state->i)
	{
		token_value = extract_token(input, state->start, state->i);
		// Determine if this is a command or a flag
		token_type = CMD;
		if (is_flag(token_value))
			token_type = FLAG;
		add_token(state->tokens, token_value, token_type);
	}
	state->start = state->i;
	state->in_word = 0;
	return (*state->tokens);
}

/**
 * Process a segment of input between operators
 * @param input: The input string
 * @param tokens: Pointer to the token list
 * @param start: Start position of the segment
 * @param end: End position of the segment
 * @param is_first: Flag indicating if this is the first segment
 */
void	process_segment(char *input, t_token **tokens, int start, int end,
		int is_first)
{
	t_parse_state	segment_state;
	int				i;
	char			quote;
	int				quote_start;
	char			*token_value;
	int				word_start;
	char			*processed_token;
			t_token_type token_type;

	i = start;
	// Initialize segment parsing state
	init_parse_state(&segment_state, tokens);
	segment_state.i = start;
	segment_state.start = start;
	// Skip leading whitespace
	while (i < end && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (i >= end) // Empty segment after whitespace removal
		return ;
	// Process words in the segment
	while (i < end)
	{
		// Handle quoted strings
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			quote_start = i;
			i++; // Move past opening quote
			// Find closing quote
			while (i < end && input[i] != quote)
				i++;
			if (i >= end) // Unclosed quote within segment
			{
				printf("Error: Unclosed %s quote\n",
					(quote == '\'') ? "single" : "double");
				return ;
			}
			// Extract the quoted string without quotes
			token_value = extract_token(input, quote_start + 1, i);
			add_token(tokens, token_value, STR_LITERAL);
			i++; // Move past closing quote
		}
		// Handle regular words
		else if (input[i] != ' ' && input[i] != '\t')
		{
			word_start = i;
			// Find end of word
			while (i < end && input[i] != ' ' && input[i] != '\t'
				&& input[i] != '\'' && input[i] != '"')
				i++;
			token_value = extract_token(input, word_start, i);
			processed_token = handle_escapes(token_value);
			free(token_value);
			// Determine token type
			if (is_first && word_start == start)
				// First token in first segment is a command
				token_type = CMD;
			else if (processed_token && processed_token[0] == '-')
				token_type = FLAG;
			else
				token_type = STR_LITERAL;
			add_token(tokens, processed_token, token_type);
		}
		else
		{
			// Skip whitespace
			i++;
		}
	}
}

/**
 * Tokenize an input string into a linked list of tokens
 * @param input: The input string to tokenize
 * @return: Linked list of tokens, or NULL if there's a syntax error
 */
t_token	*tokenize_string(char *input)
{
	t_token			*tokens;
	t_parse_state	state;
	int				i;
	int				is_first_segment;

	tokens = NULL;
	int segment_start, segment_end;
	i = 0;
	is_first_segment = 1;
	// Initialize parsing state
	init_parse_state(&state, &tokens);
	segment_start = 0;
	// First, scan for operators to divide the string into segments
	while (input[i] != '\0')
	{
		// Skip quoted sections when looking for operators
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (!input[i]) // Unclosed quote
			{
				printf("Error: Unclosed single quote\n");
				return (tokens);
			}
			i++; // Move past the closing quote
			continue ;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
				i++;
			if (!input[i]) // Unclosed quote
			{
				printf("Error: Unclosed double quote\n");
				return (tokens);
			}
			i++; // Move past the closing quote
			continue ;
		}
		// Check for operators
		if (is_operator_char(input[i]))
		{
			// Process segment before the operator
			segment_end = i;
			if (segment_start < segment_end)
				process_segment(input, &tokens, segment_start, segment_end,
					is_first_segment);
			// Process the operator itself as a token
			char *operator= extract_token(input, i, i + 1);
			add_token(&tokens, operator, OPERATOR);
			segment_start = i + 1;
			is_first_segment = 0;
		}
		i++;
	}
	// Process the last segment if there is one
	if (segment_start < i)
		process_segment(input, &tokens, segment_start, i, is_first_segment);
	return (tokens);
}
