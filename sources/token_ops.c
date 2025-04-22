/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:48:06 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 17:48:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Check for compound operators (>>, <<, &&, ||)
 *
 * @return: 0 if it's a compound op
 * @return: 1 if not
 */
int	handle_operator_helper(char *input, t_parse_state *state)
{
	if ((input[state->i] == '>' && input[state->i + 1] == '>')
		|| (input[state->i] == '<' && input[state->i + 1] == '<')
		|| (input[state->i] == '&' && input[state->i + 1] == '&')
		|| (input[state->i] == '|' && input[state->i + 1] == '|'))
		return (0);
	return (1);
}

/**
 *
 *
 *
 */
int	handle_operators(char *input, t_parse_state *state)
{
	char	*token_value;

	if (is_operator_char(input[state->i]))
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i, NULL);
		if (handle_operator_helper(input, state))
		{
			token_value = extract_token(input, state->i, state->i + 2);
			add_token(state->tokens, token_value,
				get_token_type(token_value[0]));
			state->i += 2;
		}
		else
		{
			token_value = extract_token(input, state->i, state->i + 1);
			add_token(state->tokens, token_value,
				get_token_type(token_value[0]));
			state->i++;
		}
		state->start = state->i;
		return (1);
	}
	return (0);
}
