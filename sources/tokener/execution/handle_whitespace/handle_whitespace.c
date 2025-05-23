/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_whitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:09 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:44:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Handle whitespace in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_whitespace(char *input, t_parse_state *state, char **envp)
{
	if (ft_is_whitespace(input[state->i]))
	{
		if (state->in_word)
		{
			process_token(input, state, envp);
			state->in_word = 0;
		}
		while (input[state->i] && ft_is_whitespace(input[state->i]))
			state->i++;
		state->start = state->i;
		return (1);
	}
	return (0);
}
