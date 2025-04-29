/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:44:06 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/29 13:41:31 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tokener.h"

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
 * Handle quoted text in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_quotes(char *input, t_parse_state *state)
{
	char	quote_char;
	int		j;
	char	*token_value;

	if (!input || !state || !input[state->i])
		return (0);
	if (input[state->i] == '\'' || input[state->i] == '"')
	{
		quote_char = input[state->i];
		j = state->i + 1;
		while (input[j] && input[j] != quote_char)
			j++;
		if (input[j] == quote_char)
		{
			token_value = extract_string(input, state->i + 1, j);
			if (!token_value)
				return (0);
			add_token(state->tokens, token_value, STR_LITERAL);
			state->i = j + 1;
			state->in_word = 0;
		}
		else
			state->error = 1;
		return (1);
	}
	return (0);
}
