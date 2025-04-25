/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:44:06 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 02:14:17 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * This function handles input that has no quotes at all
 * example: echo hello there && ls -l
 * @param input: input string
 * @param tokens: pointer to token list
 * @param i: index of input to start
 * - @param envp: environment variables
 * @return index of the last processed character
 */
int	handle_without_quotes(char *input, t_token **tokens, int i)
{
	int				j;
	char			*token;
	t_token_type	token_type;

	j = i;
	while (input[j] && (input[j] == ' ' || input[j] == '\t'))
		j++;
	if (j > i)
		i = j;
	if (is_operator_char(input[j]))
		return (handle_operator(input, tokens, j));
	j = i;
	while (input[j] && !is_operator_char(input[j]) && input[j] != ' '
		&& input[j] != '\t' && input[j] != '\'' && input[j] != '"')
		j++;
	if (j > i)
	{
		token = extract_string(input, i, j);
		token_type = decide_token_type(token);
		add_token(tokens, token, token_type);
	}
	return (j);
}

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

	end = handle_quoted_string(input, state->i, quote_type, &state->error);
	if (state->error)
	{
		printf("Error: Unclosed quote.\n");
		return (end);
	}
	token_value = extract_string(input, state->i + 1, end - 1);
	token_type = decide_token_type(token_value);
	if (state->is_first_token)
	{
		token_type = CMD;
		state->is_first_token = 0;
	}
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
int	handle_quotes(char *input, t_parse_state *state)
{
	t_token_type	quote_type;
	int				end;

	if (input[state->i] == '\'' || input[state->i] == '"')
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i);
		quote_type = (input[state->i] == '\'') ? SINGLE_QUOTE : DOUBLE_QUOTE;
		end = process_quoted_string(input, state, quote_type);
		state->i = end;
		state->start = state->i;
		return (1);
	}
	return (0);
}
