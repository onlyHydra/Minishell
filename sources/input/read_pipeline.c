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

#include <stdlib.h>

void	refresh_prompt(void)
{
	rl_on_new_line();
	rl_redisplay();
}

int	read_loop(char **env)
{
	char	*user_input;

	if (env == NULL)
		return (1);
	while (1)
	{
		user_input = readline("mininshell> ");
		if (user_input == NULL)
			break ;
		if (*user_input != '\0')
			add_history(user_input);
		free(user_input);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	rl_clear_history();
	return (0);
}
