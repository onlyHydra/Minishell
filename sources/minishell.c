/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:31:05 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 17:38:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

const char	*token_type_to_str(t_token_type type)
{
	switch (type)
	{
	case CMD:
		return ("CMD");
	case PIPE:
		return ("PIPE");
	case REDIRECT_IN:
		return ("REDIRECT_IN");
	case REDIRECT_OUT:
		return ("REDIRECT_OUT");
	case REDIRECT_APPEND:
		return ("REDIRECT_APPEND");
	case HEREDOC:
		return ("HEREDOC");
	case AND:
		return ("AND");
	case OR:
		return ("OR");
	case LPAREN:
		return ("LPAREN");
	case RPAREN:
		return ("RPAREN");
	case ENV_VAR:
		return ("ENV_VAR");
	case EXIT_STATUS:
		return ("EXIT_STATUS");
	default:
		return ("UNKNOWN");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_parsed_data	*parsed_data;

	if (argc)
	{
		parsed_data = tokenize_data(argv);
		if (parsed_data)
		{
			printf("Tokenization successful!\n");
			for (int i = 0; parsed_data[i].token; i++)
			{
				printf("Token %d: Type = %s, Value = '%s'\n", i,
					token_type_to_str(*parsed_data[i].token),
					parsed_data[i].data);
			}
			for (int i = 0; parsed_data[i].token; i++)
			{
				free(parsed_data[i].token);
				free(parsed_data[i].data);
			}
			free(parsed_data);
		}
		else
			printf("Tokenization failed or no input provided.\n");
	}
	if (envp)
		return (1);
	return (0);
}
