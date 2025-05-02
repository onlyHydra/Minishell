/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 15:09:31 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokener.h"

/**
 * Process the input string through tokenization, handling all character types
 * and constructing a token list
 *
 * @param input: The input string to process
 * @param params: The parameters guiding the tokenization process
 * @return: The generated token list
 */
t_token	*process_tokenization_wrapper(char *input, t_parse_params *params)
{
	t_parse_state	segment_state;

	init_parse_state(&segment_state, params->tokens, params->envp);
	params->input = input;
	segment_state.i = params->segment_start;
	segment_state.start = params->segment_start;
	segment_state.is_first_token = params->is_first_segment;
	parse_segment(params, &segment_state);
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
	result = process_tokenization_wrapper(input, &params);
	if (result)
	{
		post_process_command_tokens(result, envp);
		post_process_filename_tokens(result);
		
	}
	return (result);
}
