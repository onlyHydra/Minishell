/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_white_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:09 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/23 20:20:11 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// token_white_space.c
/**
 * Handle whitespace in the input string
 * @param input: The input string
 * @param state: Parsing state
 * - @param envp: Environment variables
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
 * Handle backslash escapes in the input string
 * @param input: The input string
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
