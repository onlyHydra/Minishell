/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/04/22 14:22:19 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Check if a quote is closed properly
 * @param str: The string to check
 * @param start: Starting index of the quote
 * @param quote_char: The quote character to match (' or ")
 * @return: 1 if closed properly, 0 if unclosed
 */
int	is_quote_closed(char *str, int start, char quote_char)
{
	int	i;

	i = start + 1;
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
 * @param envp: Environment variables
 */
void	process_token(char *input, t_parse_state *state, int end, char **envp)
{
	char			*token_value;
	char			*processed_token;
	t_token_type	token_type;

	token_value = extract_token(input, state->start, end);
	processed_token = handle_escapes(token_value);
	free(token_value);
	// Determine token type using decide_token_type
	token_type = decide_token_type(processed_token, envp);
	// Override for first token if needed
	if (state->is_first_token)
	{
		token_type = CMD;
		state->is_first_token = 0;
	}
	add_token(state->tokens, processed_token, token_type);
	state->in_word = 0;
}

/**
 * This decides what kind of type the token has
 * @param token: the token with the value
 * @param envp: environment variables
 * @return: token_type
 */
t_token_type	decide_token_type(char *token, char **envp)
{
	if (!token || !*token)
		return (CMD); // Default for empty tokens
						// Check for operators
	if (token[0] == '-')
		return (FLAG);
	if (strlen(token) == 1)
	{
		if (token[0] == '|')
			return (PIPE);
		else if (token[0] == '>')
			return (REDIRECT_OUT);
		else if (token[0] == '<')
			return (REDIRECT_IN);
	}
	// Check for compound operators
	if (strlen(token) == 2)
	{
		if (strcmp(token, ">>") == 0)
			return (APPEND_OUT);
		else if (strcmp(token, "<<") == 0)
			return (HEREDOC);
		else if (strcmp(token, "&&") == 0)
			return (AND);
		else if (strcmp(token, "||") == 0)
			return (OR);
	}
	// Check if this could be a command
	if (executable(token, envp) == 0)
		return (CMD);
	// Default case - treat as a str_literal argument
	return (STR_LITERAL);
}

/**
 * Process a segment of input between operators
 * @param input: The input string
 * @param tokens: Pointer to the token list
 * @param start: Start position of the segment
 * @param end: End position of the segment
 * @param is_first: Flag indicating if this is the first segment
 * @param envp: Environment variables
 */
void	process_segment(char *input, t_token **tokens, int start, int end,
		int is_first, char **envp)
{
	t_parse_state	segment_state;

	init_parse_state(&segment_state, tokens);
	segment_state.i = start;
	segment_state.start = start;
	segment_state.is_first_token = is_first;
	// Process the segment
	while (segment_state.i < end && !segment_state.error)
	{
		if (handle_whitespace(input, &segment_state, envp))
			continue ;
		if (handle_backslash(input, &segment_state))
			continue ;
		if (handle_quotes(input, &segment_state, envp))
			continue ;
		if (handle_operators(input, &segment_state))
			continue ;
		if (!segment_state.in_word)
		{
			segment_state.in_word = 1;
			segment_state.start = segment_state.i;
		}
		segment_state.i++;
	}
	if (segment_state.in_word && segment_state.start < segment_state.i
		&& !segment_state.error)
		process_token(input, &segment_state, segment_state.i, envp);
}

/**
 * Tokenize an input string into a linked list of tokens
 * @param input: The input string to tokenize
 * @param envp: Environment variables array
 * @return: Linked list of tokens, or NULL if there's a syntax error
 */
t_token	*tokenize_string(char *input, char **envp)
{
	t_token			*tokens;
	int				i;
	int				is_first_segment;
	int				segment_start;
	int				in_quote;
	char			quote_char;
	char			*operator;
	t_token_type	op_type;

	tokens = NULL;
	i = 0;
	is_first_segment = 1;
	segment_start = 0;
	in_quote = 0;
	quote_char = 0;
	// First, scan for top-level operators to divide the string into segments
	while (input[i] != '\0')
	{
		// skip checking for top-level operators inside quotes
		if ((input[i] == '\'' || input[i] == '"') && !in_quote)
		{
			in_quote = 1;
			quote_char = input[i];
			i++;
			continue ;
		}
		else if (in_quote && input[i] == quote_char)
		{
			in_quote = 0;
			i++;
			continue ;
		}
		else if (in_quote)
		{
			i++;
			continue ;
		}
		// Skip backslash and the character it escapes
		if (input[i] == '\\' && input[i + 1])
		{
			i += 2;
			continue ;
		}
		// Check for top-level operators (|, ||, &&, ;) when not in quotes
		if (!in_quote && (input[i] == '|' || input[i] == ';' || (input[i] == '&'
					&& input[i + 1] == '&') || (input[i] == '|' && input[i
					+ 1] == '|')))
		{
			// Process segment before the operator
			if (segment_start < i)
				process_segment(input, &tokens, segment_start, i,
					is_first_segment, envp);
			// Process the operator itself as a token
			// Handle compound operators
			if ((input[i] == '&' && input[i + 1] == '&') || (input[i] == '|'
					&& input[i + 1] == '|'))
			{
				operator= extract_token(input, i, i + 2);
				op_type = decide_token_type(operator, envp);
				add_token(&tokens, operator, op_type);
				i += 2;
			}
			else // Single character operator
			{
				operator= extract_token(input, i, i + 1);
				op_type = decide_token_type(operator, envp);
				add_token(&tokens, operator, op_type);
				i++;
			}
			segment_start = i;
			is_first_segment = 0;
			continue ;
		}
		i++;
	}
	// Handle unclosed quotes
	if (in_quote)
	{
		printf("Error: Unclosed %s quote\n",
			(quote_char == '\'') ? "single" : "double");
		return (tokens); // Return what we have so far
	}
	// Process the last segment if there is one
	if (segment_start < i)
		process_segment(input, &tokens, segment_start, i, is_first_segment,
			envp);
	return (tokens);
}
