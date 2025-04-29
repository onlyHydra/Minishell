/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/29 23:39:13 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Processes an operator and adds it to the token list using the params struct
 * @param params: Struct containing input, tokens list, and envp
 * @param i: Current index in the input string
 * @return new index after processing the operator (i + 1 or i + 2)
 */
static int	process_operator(t_parse_params *params, int i)
{
	char			*operator;
	t_token_type	op_type;

	if ((params->input[i] == '&' && params->input[i + 1] == '&')
		|| (params->input[i] == '|' && params->input[i + 1] == '|')
		|| (params->input[i] == '>' && params->input[i + 1] == '>')
		|| (params->input[i] == '<' && params->input[i + 1] == '<'))
	{
		operator= extract_string(params->input, i, i + 2);
		op_type = decide_token_type(operator, params->envp);
		add_token(params->tokens, operator, op_type);
		return (i + 2);
	}
	else
	{
		operator= extract_string(params->input, i, i + 1);
		op_type = decide_token_type(operator, params->envp);
		add_token(params->tokens, operator, op_type);
		return (i + 1);
	}
}

/**
 * Main parsing loop
 * Process segment content character by character
 * Handles parentheses, whitespace, quotes, operators and regular text
 * processes tokens in the end if its in a word, and the current position (i) is bigger than the start 
 */
void	parse_segment_characters(t_parse_params *params,
		t_parse_state *segment_state)
{
	while (segment_state->i < params->segment_end && !segment_state->error)
	{
		if (handle_parenthesis_char(params->input, segment_state, params->envp))
			continue ;
		if (handle_whitespace(params->input, segment_state, params->envp))
			continue ;
		if (handle_quoted_text(params->input, segment_state))
			continue ;
		if (handle_parsing_ops(params->input, segment_state, params->envp))
			continue ;
		if (handle_regular_text(params->input, segment_state, params->envp))
			continue ;
		segment_state->i++;
	}
	if (segment_state->in_word && segment_state->start < segment_state->i
		&& !segment_state->error)
		process_token(params->input, segment_state, segment_state->i,
			params->envp);
}

/**
 * Tokenizes a text segment between operators or input boundaries
 * Sets up segment state and initiates character-by-character parsing
 * @param params: Struct containing input, tokens list, and envp
 */
void	parse_segment_wrapper(t_parse_params *params)
{
	t_parse_state	segment_state;

	init_parse_state(&segment_state, params->tokens);
	segment_state.i = params->segment_start;
	segment_state.start = params->segment_start;
	segment_state.is_first_token = params->is_first_segment;
	parse_segment_characters(params, &segment_state);
}
