/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:48:06 by marvin            #+#    #+#             */
/*   Updated: 2025/04/23 20:21:38 by iatilla-         ###   ########.fr       */
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

int	is_whitespace(char c)
{
	if (c == ' ')
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
	int		start_pos;
	int		end_pos;

	if (is_operator_char(input[state->i]))
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i);
		start_pos = state->i;
		if (handle_operator_helper(input, state) == 0)
		{
			end_pos = state->i + 2;
			token_value = extract_token(input, start_pos, end_pos);
			add_token(state->tokens, token_value,
				get_token_type(token_value[0]));
			state->i += 2;
		}
		else
		{
			end_pos = state->i + 1;
			token_value = extract_token(input, start_pos, end_pos);
			add_token(state->tokens, token_value,
				get_token_type(token_value[0]));
			state->i++;
		}
		while (input[state->i] && is_whitespace(input[state->i]))
			state->i++;
		state->start = state->i;
		return (1);
	}
	return (0);
}
