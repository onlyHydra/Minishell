/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/05/01 16:25:32 by iatilla-         ###   ########.fr       */
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
	if (token_type == ENV_VAR)
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
 * Processes an operator and adds it to the token list using the params struct
 * @param params: Struct containing input, tokens list, and envp
 * @param i: Current index in the input string
 * @return new index after processing the operator (i + 1 or i + 2)
 */
static int	process_char_operator(t_parse_params *params, int i)
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
 * Processes input before an operator and handles the operator itself
 * @param params: Struct containing input, tokens list, and envp
 * @param i: Current index in the input string
 * @return new index after processing the operator
 */
int	process_char_before_op(t_parse_params *params, int i)
{
	int				new_pos;
	t_parse_params	segment_params;

	if (params->segment_start < i)
	{
		segment_params = *params;
		segment_params.segment_end = i;
		parse_segment_wrapper(&segment_params);
	}
	new_pos = process_char_operator(params, i);
	params->segment_start = new_pos;
	params->is_first_segment = 0;
	return (new_pos);
}

/**
 * Process a single character in the tokenization loop
 * @param input: input string
 * @param params: parsing parameters
 * @param i: current position in input
 * @param state: state tracking variables
 * @return: new position after processing
 */
static int	process_single_char(char *input, t_parse_params *params, int i,
		t_parse_state *state)
{
	int	skip;

	skip = handle_quotes_tokenize(input, i, &state->in_quote,
			&state->quote_char);
	if (skip)
		return (i + skip);
	if (!state->in_quote && (input[i] == '(' || input[i] == ')'))
	{
		if (params->segment_start < i)
		{
			params->segment_end = i;
			parse_segment_wrapper(params);
		}
		params->segment_start = i;
		params->segment_end = i + 1;
		parse_segment_wrapper(params);
		params->segment_start = i + 1;
		return (i + 1);
	}
	if (!state->in_quote && is_operator(input, i))
		return (process_char_before_op(params, i));
	return (i + 1);
}

/**
 * Main tokenization loop for the entire input string
 * Processes all segments including the final one
 * @param input: input string
 * @param params: parsing parameters
 * @return: head of tokens list
 */
t_token	*process_tokenization_loop(char *input, t_parse_params *params)
{
	int				current_pos;
	t_parse_state	state;
	int				next_i;

	if (!input || !params)
		return (NULL);
	current_pos = 0;
	state.quote_char = 0;
	state.in_quote = 0;
	while (input[current_pos] != '\0')
	{
		next_i = process_single_char(input, params, current_pos, &state);
		if (next_i > current_pos)
			current_pos = next_i;
		else
			current_pos++;
	}
	if (params->segment_start < current_pos)
	{
		params->segment_end = current_pos;
		parse_segment_wrapper(params);
	}
	return (*(params->tokens));
}
