/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/13 15:46:25 by iatilla-         ###   ########.fr       */
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
static int	is_continuous_word(char *input, t_parse_state *state)
{
	if (state->i == 0)
		return (0);
	if (ft_is_whitespace(input[state->i - 1]))
		return (0);
	if (is_operator(input, state->i - 1))
		return (0);
	return (1);
}

/**
 * Checks if the current character is a quote or part of a complex token
 * that may contain embedded quotes
 */
static int	is_complex_token_start(char *input, int i)
{
	if (input[i] == '\'' || input[i] == '"')
		return (1);
	if (i > 0 && !ft_is_whitespace(input[i - 1]) && !is_operator(input, i - 1))
		return (1);
	return (0);
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
	if (!segment_state->in_word && is_continuous_word(params->input,
			segment_state))
		segment_state->in_word = 1;
	while (segment_state->i < params->segment_end && !segment_state->error)
	{
		if (handle_whitespace(params->input, segment_state, params->envp))
			continue ;
		if (handle_parenthesis_char(params->input, segment_state, params->envp))
			continue ;
		if (is_complex_token_start(params->input, segment_state->i))
			if (handle_quoted_text(params->input, segment_state))
				continue ;
		if (handle_parsing_ops(params->input, segment_state, params->envp))
		{
			if (handle_filename(params->input, segment_state))
				continue ;
			continue ;
		}
		if (handle_regular_text(params->input, segment_state, params->envp))
			continue ;
		segment_state->i++;
	}
	if (params->input[segment_state->i] != '\0' && segment_state->in_word
		&& segment_state->start < segment_state->i && !segment_state->error)
		process_token(params->input, segment_state, params->envp);
	params->filepath = segment_state->filepath;
}
