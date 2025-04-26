/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:44:06 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 18:56:59 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Process a quoted string once it's identified
 * @param input: The input string
 * @param state: Parsing state
 * @param quote_type: Type of quote (single or double)
 * - @param envp: Environment variables
 * @return: End position of the quoted string
 */
int	process_quoted_string(char *input, t_parse_state *state,
		t_token_type quote_type)
{
	char			*token_value;
	t_token_type	token_type;
	int				end;
	char			quote_char;

	// Find the end of the quoted string
	end = state->i + 1;
	quote_char = (quote_type == SINGLE_QUOTE) ? '\'' : '"';
	// Find the closing quote
	while (input[end] && input[end] != quote_char)
		end++;
	if (input[end] == quote_char)
		end++; // Include the closing quote
	else
	{
		printf("Error: Unclosed quote.\n");
		state->error = 1;
		return (end);
	}
	// Extract the content without the quotes
	token_value = extract_string(input, state->i + 1, end - 1);
	// Always set quoted strings as STR_LITERAL, except for first token
	token_type = STR_LITERAL;
	if (state->is_first_token)
	{
		token_type = CMD;
		state->is_first_token = 0;
	}
	// Add the token with all whitespace preserved
	add_token(state->tokens, token_value, token_type);
	return (end);
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
 * - @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
/**
 * Handle quoted text in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_quotes(char *input, t_parse_state *state)
{
	char	quote_char;
	int		start_pos;
	int		j;
	char	*token_value;

	if (input[state->i] == '\'' || input[state->i] == '"')
	{
		quote_char = input[state->i];
		start_pos = state->i;
		j = state->i + 1;
		// Find the closing quote
		while (input[j] && input[j] != quote_char)
			j++;
		// If quote is closed, process it as a token
		if (input[j] == quote_char)
		{
			token_value = extract_string(input, start_pos + 1, j);
			add_token(state->tokens, token_value, STR_LITERAL);
			state->i = j + 1; // Move past the closing quote
			state->in_word = 0;
			return (1);
		}
		else
		{
			// Handle unclosed quotes (error case)
			state->error = 1;
			return (1);
		}
	}
	return (0);
}
