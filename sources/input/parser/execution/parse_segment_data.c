/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/30 18:50:47 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Main parsing loop
 * Process segment content character by character

 * Handles parentheses: Opening '(' and closing ')'
 are treated as separate tokens
 *  whitespace: Spaces, tabs that separate tokens and are skipped
 *  quotes: Both single quotes (') and double quotes (") for literal strings
 *  operators: Shell operators like |, <, >, >>, &&, ||, etc.
 *  regular text: Normal characters that form command names and arguments
 *
 * This function is the core of the parsing process,
	processing a segment of input
 * by examining each character and delegating to specialized handlers.
 * It continues until it reaches the end of the segment or encounters an error.
 * At the end, it processes any remaining text as a token if necessary.
 *
 * The function uses a priority-based approach to character handling:
 * 1. First checks for parentheses
 * 2. Then whitespace
 * 3. Then quoted text
 * 4. Then operators
 * 5. Finally regular text
 * If a character is handled by one handler,
	the loop continues to the next character
 *
 * @param params     Contains input string, segment boundaries,
	and environment variables
 * @param segment_state Tracks current parsing state including position, flags,
	and errors
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
