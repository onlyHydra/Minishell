/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_regular_text.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:34:41 by schiper           #+#    #+#             */
/*   Updated: 2025/05/13 16:10:19 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Handle environment variables specifically
 */
static int	handle_env_var(char *input, t_parse_state *state, char **envp)
{
	int	j;

	if (is_exit_status_var(input, state->i))
		return (handle_exit_status(input, state, state->exit_status));
	if (is_environment_variable(input))
	{
		prepare_for_env_var(input, state, envp);
		j = find_env_var_end(input, state->i);
		return (process_env_token(input, state, envp, j));
	}
	return (0);
}

/**
 * Find the end of the current regular text segment
 */
static int	find_text_segment_end(char *input, int start)
{
	int	j;

	j = start;
	while (input[j] != '\0' && !is_operator(input, j) && input[j] != ' '
		&& input[j] != '\t' && !is_possible_quote(input, j) && input[j] != '('
		&& input[j] != ')' && input[j] != '$')
		j++;
	return (j);
}

/**
 * Start a new word and process any regular text
 */
static int	process_text_segment(char *input, t_parse_state *state, char **envp)
{
	int	j;

	if (!state->in_word)
	{
		state->in_word = 1;
		state->start = state->i;
	}
	j = find_text_segment_end(input, state->i);
	if (j > state->i)
	{
		state->i = j;
		if (!input[j] || ft_is_whitespace(input[j]) || is_operator(input, j))
			process_token(input, state, envp);
		return (1);
	}
	return (0);
}

/**
 * Handle regular text (without quotes or special characters)
 */
int	handle_regular_text(char *input, t_parse_state *state, char **envp)
{
	if (handle_env_var(input, state, envp))
		return (1);
	if (is_operator(input, state->i) || is_possible_quote(input, state->i)
		|| input[state->i] == '(' || input[state->i] == ')')
		return (0);
	return (process_text_segment(input, state, envp));
}
