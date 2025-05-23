/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:32:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:44:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Check if the characters at current position form a compound operator (>>, <<,
	&&, ||)
 *
 * @param input: The input string being parsed
 * @param position: Current position in the input string
 * @return: 0 if it's a compound operator
 * @return: 1 if not
 */
static int	check_for_twochar_operator(char *input, int position)
{
	char	*potential_operator;

	potential_operator = extract_string(input, position, position + 2);
	if (twochar_operator(potential_operator) != STR_LITERAL)
		return (free(potential_operator), 0);
	return (free(potential_operator), 1);
}

/**
 * Process an operator token (single or compound)
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @param start_pos: Starting position of the operator
 */
static void	process_parsing_ops(char *input, t_parse_state *state,
		int start_pos)
{
	int				end_pos;
	char			*token_value;
	t_token_type	token;

	if (check_for_twochar_operator(input, state->i) == 0)
	{
		end_pos = state->i + 2;
		token_value = extract_string(input, start_pos, end_pos);
		token = decide_token_type(token_value, state->envp, state);
		add_token(state->tokens, token_value, token, NULL);
		state->i += 2;
	}
	else
	{
		end_pos = state->i + 1;
		token_value = extract_string(input, start_pos, end_pos);
		token = decide_token_type(token_value, state->envp, state);
		add_token(state->tokens, token_value, token, NULL);
		state->i++;
	}
}

/**
 * Process operator characters in the input string
 * Identifies single and compound operators and adds them as tokens
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @return: 1 if an operator was processed, 0 otherwise
 */
int	handle_parsing_ops(char *input, t_parse_state *state, char **envp)
{
	int	start_pos;

	if (is_operator(input, state->i))
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, envp);
		start_pos = state->i;
		process_parsing_ops(input, state, start_pos);
		while (input[state->i] && ft_is_whitespace(input[state->i]))
			state->i++;
		state->start = state->i;
		return (1);
	}
	return (0);
}
