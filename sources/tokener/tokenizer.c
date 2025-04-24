/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/24 19:53:34 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**

 * Wrapper function for processing a string to add labels
 * as tokens to words defined by isspace()
 * @param input: merged string  from input to tokenize
 * @param envp: the environment variables array
 * @return pointer to the head of the linked list of tokens
 * @warning This allocated memory you have to deallocate
 */
t_token	*wrapper_process_string(char *input, char **envp)
{
	t_token			*tokens;
	t_parse_params	params;

	tokens = NULL;
	init_parse_params(&params, input, &tokens, envp);
	return (process_tokenization_loop(input, &params));
}

/**
 * Tokenize the argv input with command identification
 * @param argv: The command line arguments
 * @return: Parsed data array
 */
t_parsed_data	*tokenize_input(char **argv, char **envp)
{
	int		total_len;
	char	*input_str;
	t_token	*tokens;

	if (!argv || !argv[1])
		return (NULL);
	total_len = calculate_total_length(argv);
	input_str = concatenate_arguments(argv, total_len);
	if (!input_str)
		return (NULL);
	tokens = wrapper_process_string(input_str, envp);
	free(input_str);
	if (!tokens)
		return (NULL);
	return (tokens_to_parsed_data(tokens));
}
