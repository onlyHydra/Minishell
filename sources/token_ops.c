/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:48:06 by marvin            #+#    #+#             */
/*   Updated: 2025/04/25 03:05:09 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**

	* if you want a wrapper function you might consider using token_interface2.c function to check some stuff
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
 * I gues it just goes through string and searched all the operators maybe
 *
 */
int	handle_operators(char *input, t_parse_state *state)
{
	char	*token_value;
	int		start_pos;
	int		end_pos;

	if (is_operator(input,state->i))
	{
		if (state->start < state->i && state->in_word)
			process_token(input, state, state->i);
		start_pos = state->i;
		if (handle_operator_helper(input, state) == 0)
		{
			end_pos = state->i + 2;
			token_value = extract_string(input, start_pos, end_pos);
			add_token(state->tokens, token_value,
				get_token_type(token_value[0]));
			state->i += 2;
		}
		else
		{
			end_pos = state->i + 1;
			token_value = extract_string(input, start_pos, end_pos);
			add_token(state->tokens, token_value,
				get_token_type(token_value[0]));
			state->i++;
		}
		while (input[state->i] && ft_is_whitespace(input[state->i]))
			state->i++;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * @param input: string
 * @param tokens: all tokens
 * @param j: index to start
 *
	- @param envp: enviromental variables for command checking in decide_token_type()
 * @return: the index of the ending point of the input
 */
int	handle_operator(char *input, t_token **tokens, int j)
{
	char	*token;

	if ((input[j] == '>' && input[j + 1] == '>') || (input[j] == '<' && input[j
			+ 1] == '<') || (input[j] == '&' && input[j + 1] == '&')
		|| (input[j] == '|' && input[j + 1] == '|'))
	{
		token = extract_string(input, j, j + 2);
		add_token(tokens, token, decide_token_type(token));
		return (j + 1);
	}
	token = extract_string(input, j, j + 1);
	add_token(tokens, token, decide_token_type(token));
	return (j);
}
