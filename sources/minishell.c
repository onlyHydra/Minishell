/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:31:05 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/04 18:38:01 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "input.h"
#include "tokener.h"

/**
 * Display token information for debugging
 * @param tokens: The token structure to display
 * @return: 0 for success
 */
int	display_tokens(t_token *tokens)
{
	t_parsed_data	*parsed_data;

	if (!tokens)
		return (1);
	parsed_data = tokens_to_parsed_data(tokens);
	if (parsed_data)
	{
		printf("Tokenization successful!\n");
		for (int i = 0; parsed_data[i].token; i++)
		{
			printf("Token %d: Type = %s, Value = '%s'\nfilepath= '%s'\n", i,
				token_type_to_str(*parsed_data[i].token), parsed_data[i].data,
				parsed_data[i].filepath);
		}
		for (int i = 0; parsed_data[i].token; i++)
		{
			free(parsed_data[i].token);
			free(parsed_data[i].data);
		}
		free(parsed_data);
		printf("\n");
		return (0);
	}
	else
	{
		printf("Tokenization failed.\n");
		return (1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	return (read_loop(envp));
}
