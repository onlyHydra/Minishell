/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:17 by schiper           #+#    #+#             */
/*   Updated: 2025/04/26 14:51:57 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "token_struct.h"
#include "tokener.h"
#include <stdlib.h>

void	refresh_prompt(void)
{
	rl_on_new_line();
	rl_redisplay();
}

/**
 * Main input reading loop
 * @param envp: Environment variables
 * @return: 0 for success, 1 for error
 */
int	read_loop(char **envp)
{
	t_token	*tokens;
	char	*user_input;

	// t_parsed_data	*data;
	if (envp == NULL)
		return (1);
	while (1)
	{
		user_input = readline("minishell> ");
		if (user_input == NULL)
			break ;
		if (*user_input != '\0')
		{
			add_history(user_input);
			tokens = process_input(user_input, envp);
			if (tokens)
			{
				/** CONTINUE WITH EXECUTION OF DATA
				data = tokens_to_parsed_data(tokens);
				**/
				// display_tokens(tokens);
				free_token_struct(tokens);
			}
		}
		free(user_input);
		refresh_prompt();
	}
	rl_clear_history();
	return (0);
}
