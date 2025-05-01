/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:31:05 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 20:39:58 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "input.h"
#include "tokener.h"

// For Testing Purpose
const char	*token_type_to_str(t_token_type type)
{
	switch (type)
	{
	case CMD:
		return ("CMD");
	case STR_LITERAL:
		return ("STR_LITERAL");
	case REDIRECT_APPEND:
		return ("REDIRECT_APPEND");
	case HEREDOC:
		return ("HEREDOC");
	case ENV_VAR:
		return ("ENV_VAR");
	case AND:
		return ("AND");
	case OR:
		return ("OR");
	case LPAREN:
		return ("LPAREN");
	case RPAREN:
		return ("RPAREN");
	case FLAG:
		return ("FLAG");
	case PIPE:
		return ("PIPE");
	case REDIRECT_IN:
		return ("REDIRECT_IN");
	case REDIRECT_OUT:
		return ("REDIRECT_OUT");
	case SEMICOLON:
		return ("SEMICOLON");
	case SINGLE_QUOTE:
		return ("SINGLE_QUOTE");
	case DOUBLE_QUOTE:
		return ("DOUBLE_QUOTE");
	default:
		return ("UNKNOWN");
	}
}

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
			printf("Token %d: Type = %s, Value = '%s'\n", i,
				token_type_to_str(*parsed_data[i].token), parsed_data[i].data);
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

// execve_envp = concatenate(envp,our_env_list);
// (ls -l | grep .c) && echo "done"