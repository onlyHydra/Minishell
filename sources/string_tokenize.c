/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/04/23 17:05:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Process a normal token and add it to the token list
 * @param input: Input string
 * @param state: Parsing state
 * @param end: End position of token
 * @param envp: Environment variables
 */
void	process_token(char *input, t_parse_state *state, int end, char **envp)
{
	char			*token_value;
	char			*processed_token;
	t_token_type	token_type;

	token_value = extract_token(input, state->start, end);
	processed_token = handle_escapes(token_value);
	free(token_value);
	token_type = decide_token_type(processed_token, envp);
	if (state->is_first_token)
	{
		token_type = CMD;
		state->is_first_token = 0;
	}
	add_token(state->tokens, processed_token, token_type);
	state->in_word = 0;
}

/**
 * Process a single character in the tokenization loop
 * @param input: input string
 * @param params: parsing parameters
 * @param i: current position in input
 * @param state: state tracking variables
 * @return: new position after processing
 */
int	process_char(char *input, t_parse_params *params, int i,
		t_parse_state *state)
{
	int	skip;

	if ((skip = handle_quotes_tokenize(input, i, &state->in_quote,
				&state->quote_char)))
		return (i + skip);
	if ((skip = handle_escape(input, i)))
		return (i + skip);
	if (!state->in_quote && is_operator(input, i))
		return (handle_operator_segment(params, i));
	return (i + 1);
}

/**
 * Main tokenization loop
 * @param input: input string
 * @param params: parsing parameters
 * @return: head of tokens list
 */
t_token	*process_tokenization_loop(char *input, t_parse_params *params)
{
	int				i;
	t_parse_state	state;
	int				next_i;

	i = 0;
	state.quote_char = 0;
	state.in_quote = 0;
	while (input[i] != '\0')
	{
		next_i = process_char(input, params, i, &state);
		if (next_i == i)
			i++;
		else
			i = next_i;
	}
	// i = current position
	if (params->segment_start < i)
	{
		params->segment_end = i;
		process_segment(params);
	}
	return (*(params->tokens));
}

/**
 * Tokenizes the input string into a list of tokens, handling quotes, escapes,
	and operators
 * @param input: the input string to tokenize
 * @param envp: the environment variables array for variable expansion
 * @param exit_status: Last command exit status
 * @return pointer to the head of the linked list of tokens
 */
t_token	*tokenize_string(char *input, char **envp)
{
	t_token			*tokens;
	t_parse_params	params;

	tokens = NULL;
	init_parse_params(&params, input, &tokens, envp);
	return (process_tokenization_loop(input, &params));
}
