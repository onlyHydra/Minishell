/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/04/21 14:45:22 by schiper          ###   ########.fr       */
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
 */
void	process_token(char *input, t_parse_state *state, int end)
{
	char	*token_value;
	char	*processed_token;

	token_value = extract_token(input, state->start, end);
	processed_token = handle_escapes(token_value);
	free(token_value);
	add_token(state->tokens, processed_token, CMD);
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
		add_token(state->tokens, token_value, CMD);
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
 * Tokenize a single command string with enhanced quote and escape handling
 * @param input: The input string to tokenize
 * @return: Linked list of tokens, or NULL if there's a syntax error
 */
t_token	*tokenize_string(char *input)
{
	t_token			*tokens;
	t_parse_state	state;

	tokens = NULL;
	init_parse_state(&state, &tokens);
	while (input[state.i] && !state.error)
	{
		if (handle_whitespace(input, &state))
			continue ;
		if (handle_backslash(input, &state))
			continue ;
		else if (handle_rest_cases(input, &state))
			continue ;
		state.i++;
	}
	if (state.start < state.i && state.in_word)
		process_token(input, &state, state.i);
	return (tokens);
}
