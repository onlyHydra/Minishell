/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:22 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 23:53:54 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Check if the current position in the input string contains "$?"
 * which represents the exit status of the last command
 *
 * @param input: The input string
 * @param index: Current index in the string
 * @return: 1 if "$?" is found at this position, 0 otherwise
 */
int	is_exit_status_var(const char *input, int index)
{
	if (!input || index < 0)
		return (0);
	if (input[index] == '$' && input[index + 1] == '?')
		return (1);
	return (0);
}

/**
 * Process the exit status variable "$?" and add it as a token
 *
 * @param input: The input string
 * @param state: The current parsing state
 * @param exit_status: The exit status value from the last command
 * @return: 1 if processed successfully, 0 otherwise
 */
int	handle_exit_status(char *input, t_parse_state *state, int exit_status)
{
	char	*exit_status_str;

	if (is_exit_status_var(input, state->i))
	{
		if (state->in_word && state->start < state->i)
		{
			process_token(input, state, state->envp);
			state->in_word = 0;
		}
		exit_status_str = ft_itoa(exit_status);
		if (!exit_status_str)
			return (0);
		add_token(state->tokens, exit_status_str, ENV_VAR, NULL);
		state->i += 2;
		state->start = state->i;
		return (1);
	}
	return (0);
}
