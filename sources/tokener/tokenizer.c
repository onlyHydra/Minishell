/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 23:54:03 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokener.h"

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
