/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:11:05 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 17:59:34 by marvin           ###   ########.fr       */
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
 * Tokenizes the input string into a list of tokens, handling quotes, escapes,
	and operators
 * @param input: the input string to tokenize
 * @param envp: the environment variables array for variable expansion
 * @return pointer to the head of the linked list of tokens
 */
t_token	*tokenize_string(char *input, char **envp)
{
	t_token			*tokens;
	int				i;
	int				in_quote;
	char			quote_char;
	int				skip;
	t_parse_params	params;

	tokens = NULL;
	i = 0;
	in_quote = 0;
	quote_char = 0;
	// Initialize params once
	params.input = input;
	params.tokens = &tokens;
	params.segment_start = 0;
	params.is_first_segment = 1;
	params.envp = envp;
	while (input[i] != '\0')
	{
		if ((skip = handle_quotes_tokenize(input, i, &in_quote, &quote_char)))
		{
			i += skip;
			continue ;
		}
		if ((skip = handle_escape(input, i)))
		{
			i += skip;
			continue ;
		}
		if (!in_quote && is_operator(input, i))
		{
			i = handle_operator_segment(&params, i);
			continue ;
		}
		i++;
	}
	if (params.segment_start < i)
	{
		params.segment_end = i;
		process_segment(&params);
	}
	return (tokens);
}
