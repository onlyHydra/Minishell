/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:09 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 19:21:26 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Handle whitespace in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_whitespace(char *input, t_parse_state *state, char **envp)
{
	if (input[state->i] == ' ' || input[state->i] == '\t')
	{
		// If we were building a word, complete it
		if (state->in_word)
		{
			process_token(input, state, state->i, envp);
			state->in_word = 0;
		}
		// Skip all consecutive whitespace
		while (input[state->i] && (input[state->i] == ' '
				|| input[state->i] == '\t'))
			(state->i)++;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle left & right braces in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_braces(char *input, t_parse_state *state)
{
	// Handle opening parenthesis
	if (input[state->i] == '(' && input[state->i + 1])
	{
		if (!state->in_word)
		{
			state->in_word = 1;
			state->start = state->i;
		}
		state->i++;
		return (1);
	}
	else if (input[state->i] == ')')
	{
		if (!state->in_word)
		{
			state->in_word = 1;
			state->start = state->i;
		}
		state->i++;
		return (1);
	}
	return (0);
}
