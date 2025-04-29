/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/04/29 13:41:10 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

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
	t_token_type	token_type;

	token_value = extract_string(input, state->start, end);
	if (!token_value)
		return ;
	token_type = decide_token_type(token_value, envp);
	if (state->is_first_token && is_string_command(token_value, envp))
		token_type = CMD;
	state->is_first_token = 0;
	if (!add_token(state->tokens, token_value, token_type))
		free(token_value);
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
static int	process_char(char *input, t_parse_params *params, int i,
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
			process_segment(params);
		}
		params->segment_start = i;
		params->segment_end = i + 1;
		process_segment(params);
		params->segment_start = i + 1;
		return (i + 1);
	}
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
		next_i = process_char(input, params, current_pos, &state);
		current_pos = (next_i > current_pos) ? next_i : current_pos + 1;
	}
	if (params->segment_start < current_pos)
	{
		params->segment_end = current_pos;
		process_segment(params);
	}
	return (*(params->tokens));
}

/**
 * @brief Returns a string for further token proccesing
 * @param input: The input string
 * @param start: Start index
 * @param end: End index
 * @return: The extracted token as a string
 */
char	*extract_string(char *input, int start, int end)
{
	int		len;
	char	*token;

	if (!input || start < 0 || end < start)
		return (NULL);
	len = end - start;
	token = (char *)malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	ft_memcpy(token, &input[start], len);
	token[len] = '\0';
	return (token);
}
