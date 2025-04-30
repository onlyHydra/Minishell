/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/30 15:57:29 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Main parsing loop
 * Process segment content character by character
 * Handles parentheses, whitespace, quotes, operators and regular text [IPDATE MORE DETAILED]
 */
static void	parse_segment_characters(t_parse_params *params,
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
