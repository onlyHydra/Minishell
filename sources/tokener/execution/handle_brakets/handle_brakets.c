/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_brakets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:55:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/30 18:55:23 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Handle opening parenthesis in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if a left parenthesis was handled, 0 otherwise
 */
int	handle_left_parenthesis(char *input, t_parse_state *state)
{
	char	*token_value;

	if (input[state->i] == '(')
	{
		if (state->in_word && state->start < state->i)
			process_token(input, state, state->i, NULL);
		token_value = extract_string(input, state->i, state->i + 1);
		if (!token_value)
			return (0);
		add_token(state->tokens, token_value, LPAREN);
		state->i++;
		state->in_word = 0;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle closing parenthesis in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if a right parenthesis was handled, 0 otherwise
 */
int	handle_right_parenthesis(char *input, t_parse_state *state)
{
	char	*token_value;

	if (input[state->i] == ')')
	{
		if (state->in_word && state->start < state->i)
			process_token(input, state, state->i, NULL);
		token_value = extract_string(input, state->i, state->i + 1);
		if (!token_value)
			return (0);
		add_token(state->tokens, token_value, RPAREN);
		state->i++;
		state->in_word = 0;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle opening and closing parentheses in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if a brace was handled, 0 otherwise
 */
int	handle_brakets(char *input, t_parse_state *state)
{
	if (handle_left_parenthesis(input, state))
		return (1);
	if (handle_right_parenthesis(input, state))
		return (1);
	return (0);
}
