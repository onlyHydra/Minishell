/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:27:26 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Checks if the character at the current position is part of a continuous word
 * Words are considered continuous if there's no whitespace between characters
 * 
 * @param input: The input string
 * @param state: The current parsing state
 * @return: 1 if character should be part of the current word, 0 otherwise
 */
static int is_continuous_word(char *input, t_parse_state *state)
{
    // If we're at the beginning of input, this is a new word
    if (state->i == 0)
        return 0;
    
    // If previous character is whitespace, this is a new word
    if (ft_is_whitespace(input[state->i - 1]))
        return 0;
    
    // If previous character is an operator, this is a new word
    if (is_operator(input, state->i - 1))
        return 0;
    
    // Otherwise, this is part of the current word
    return 1;
}

/**
 * This function is the core of the parsing process,
 * processing a segment of input by examining each character
 * and delegating to specialized handlers.
 * It continues until it reaches the end of the segment or encounters an error.
 * At the end, it processes any remaining text as a token if necessary.
 *
 * The function uses a priority-based approach to character handling:
 *
 * Handles parentheses: Opening '(' and closing ')'
 * whitespace: Spaces, tabs that separate tokens and are skipped
 * quotes: Both single quotes (') and double quotes (") for literal strings
 * operators: Shell operators like |, <, >, >>, &&, ||, etc.
 * regular text: Normal characters that form command names and arguments
 *
 * If a character is handled by one handler,
 * the loop continues to the next character
 *
 * @param params: Contains input string, segment boundaries,
 * and environment variables
 * @param segment_state: Tracks current parsing state including position, flags,
 * and errors
 */
void	parse_segment(t_parse_params *params, t_parse_state *segment_state)
{
	// Set in_word if the first character continues from a previous segment
	if (!segment_state->in_word && is_continuous_word(params->input, segment_state))
	{
		segment_state->in_word = 1;
	}

	while (segment_state->i < params->segment_end && !segment_state->error)
	{
		// Handle whitespace first to separate tokens
		if (handle_whitespace(params->input, segment_state, params->envp))
			continue;
			
		// Handle parentheses as special tokens
		if (handle_parenthesis_char(params->input, segment_state, params->envp))
			continue;
			
		// Handle quoted text - our improved handler will detect if quotes
		// are part of a continuous word
		if (handle_quoted_text(params->input, segment_state))
			continue;
			
		// Handle operators (|, >, <, etc.)
		if (handle_parsing_ops(params->input, segment_state, params->envp))
		{
			if (handle_filename(params->input, segment_state))
				continue;
			continue;
		}
		
		// Handle regular text and environment variables
		if (handle_regular_text(params->input, segment_state, params->envp))
			continue;
			
		segment_state->i++;
	}
	
	// Process any remaining text as a token
	if (params->input[segment_state->i] != '\0' && segment_state->in_word
		&& segment_state->start < segment_state->i && !segment_state->error)
		process_token(params->input, segment_state, params->envp);
		
	params->filepath = segment_state->filepath;
}

