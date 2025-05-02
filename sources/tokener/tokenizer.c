/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 02:43:40 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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


/**
 * Process user input and tokenize it
 * @param input: The user input string
 * @param envp: Environment variables
 * @return: Token structure or NULL if failed
 */
t_token	*process_input(char *input, char **envp)
{
	t_token			*tokens;
	t_parse_params	params;
	t_token			*result;

	if (!input || !*input)
		return (NULL);
	tokens = NULL;
	init_parse_params(&params, input, &tokens, envp);
	result = process_tokenization_loop(input, &params);
	if (result)
	{
		post_process_command_tokens(result, envp);
		post_process_filename_tokens(result);
	}
	return (result);
}
