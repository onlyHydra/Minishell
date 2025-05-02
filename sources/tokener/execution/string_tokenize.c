/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/05/02 02:19:08 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Process a token with awareness of filename expectations
 * @param input: Input string
 * @param state: Parsing state
 * @param end: End position of token
 * @param envp: Environment variables
 */
void	process_token(char *input, t_parse_state *state, int end, char **envp)
{
	char			*token_value;
	t_token_type	token_type;

	token_value = extract_string(input, state->start, end);
	if (!token_value)
		return ;
	token_type = decide_token_type(token_value, envp);
	if (token_type == ENV_VAR || is_environment_variable(token_value))
		token_value = extract_env_value(token_value, envp);
	if (state->is_first_token && is_string_command(token_value, envp))
		token_type = CMD;
	else if (state->expect_filename)
	{
		token_type = FILENAME;
		state->expect_filename = 0;
	}
	state->is_first_token = 0;
	if (!add_token(state->tokens, token_value, token_type))
		free(token_value);
	state->in_word = 0;
}

/**
 * This function is the core of the parsing process,
	processing a segment of input
 * by examining each character and delegating to specialized handlers.
 * It continues until it reaches the end of the segment or encounters an error.
 * At the end, it processes any remaining text as a token if necessary.
 *
 * The function uses a priority-based approach to character handling:

	* Handles parentheses: Opening '(' and closing ')' are treated as separate tokens
 * whitespace: Spaces, tabs that separate tokens and are skipped
 * quotes: Both single quotes (') and double quotes (") for literal strings
 * operators: Shell operators like |, <, >, >>, &&, ||, etc.
 * regular text: Normal characters that form command names and arguments
 *
 * If a character is handled by one handler,
	the loop continues to the next character
 *
 * @param params: Contains input string, segment boundaries,
	and environment variables
 * @param segment_state: Tracks current parsing state including position, flags,
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
		{
			if(handle_filename(params->input, segment_state))
				continue;
			continue ;
		}
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
 * Process the input string through tokenization, handling all character types
 * and constructing a token list
 *
 * @param input: The input string to process
 * @param params: The parameters guiding the tokenization process
 * @return: The generated token list
 */
t_token	*process_tokenization_loop(char *input, t_parse_params *params)
{
	t_parse_state	segment_state;

	init_parse_state(&segment_state, params->tokens, params->envp);
	params->input = input;
	segment_state.i = params->segment_start;
	segment_state.start = params->segment_start;
	segment_state.is_first_token = params->is_first_segment;
	parse_segment_characters(params, &segment_state);
	return (*(params->tokens));
}
