/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/29 14:16:37 by schiper          ###   ########.fr       */
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
	t_token			*result;

	tokens = NULL;
	init_parse_params(&params, input, &tokens, envp);
	result = process_tokenization_loop(input, &params);
	return (result);
}

/**
 * Process user input and tokenize it
 * @param input: The user input string
 * @param envp: Environment variables
 * @return: Token structure or NULL if failed
 */
t_token	*process_input(char *input, char **envp)
{
	t_token	*tokens;

	if (!input || !*input)
		return (NULL);
	tokens = wrapper_process_string(input, envp);
	if (tokens)
		post_process_command_tokens(tokens, envp);
	return (tokens);
}
