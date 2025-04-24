/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:32:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/24 23:43:43 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_struct.h"

/**
 * Extract and add an operator token (single or compound)
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @param start_pos: Starting position of the operator
 * @return: 1 on success
 */
static int	extract_operator_token(char *input, t_parse_state *state,
		int start_pos)
{
	char	*token_value;
	int		end_pos;

	if (check_for_twochar_operator(input, state) == 0)
	{
		end_pos = state->i + 2;
		token_value = extract_string(input, start_pos, end_pos);
		add_token(state->tokens, token_value, get_token_type(token_value[0]));
		state->i += 2;
	}
	else
	{
		end_pos = state->i + 1;
		token_value = extract_string(input, start_pos, end_pos);
		add_token(state->tokens, token_value, get_token_type(token_value[0]));
		state->i++;
	}
	return (1);
}

/**
 * Process operator characters in the input string
 * Identifies single and compound operators and adds them as tokens
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @return: 1 if an operator was processed, 0 otherwise
 */
int	handle_parsing_ops(char *input, t_parse_state *state)
{
	int	start_pos;

	if (is_operator_char(input[state->i]))
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i);
		start_pos = state->i;
		extract_operator_token(input, state, start_pos);
		while (input[state->i] && ft_is_whitespace(input[state->i]))
			state->i++;
		state->start = state->i;
		return (1);
	}
	return (0);
}
