/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 00:39:45 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_struct.h"
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
	t_token			*result;

	tokens = NULL;
	init_parse_params(&params, input, &tokens, envp);
	result = process_tokenization_loop(input, &params);
	return (result);
}

/**
 * Tokenize the line input with command identification
 * @param line: The command line arguments
 * @return: Parsed data array
 */
t_parsed_data	*tokenize_input(char **line, char **envp)
{
	int				total_len;
	char			*input_str;
	t_token			*tokens;
	t_parsed_data	*parsed_data;

	if (!line || !line[1])
		return (NULL);
	total_len = calculate_total_length(line);
	input_str = concatenate_arguments(line, total_len);
	if (!input_str)
		return (NULL);
	tokens = wrapper_process_string(input_str, envp);
	free(input_str);
	if (!tokens)
		return (NULL);
	parsed_data = tokens_to_parsed_data(tokens);
	free_token_struct(tokens);
	return (parsed_data);
}
