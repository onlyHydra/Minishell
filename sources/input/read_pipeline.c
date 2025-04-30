/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:17 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 15:57:55 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "tokener.h"
#include <stdio.h>

// volatile sig_atomic_t	g_sigint_received = 0;

/**
 * Handle SIGINT (Ctrl+C)
 * In bash: Displays a new prompt on a new line
 */
void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * Set up signal handlers for interactive mode
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = SA_RESTART; // Restart interrupted system calls
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Main input reading loop
 * @param envp: Environment variables
 * @return: 0 for success, 1 for error
 */
int	read_loop(char **envp)
{
	t_token	*labels;
	char	*user_input;

	if (envp == NULL)
		return (1);
	setup_interactive_signals();
	while (1)
	{
		user_input = readline("minishell> ");
		if (user_input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			continue ;
		}
		if (*user_input != '\0')
		{
            //check for duplicate so if we use on function it's removed from it's current place placed on top
			add_history(user_input);
			labels = process_input(user_input, envp);
			if (labels)
			{
				/** CONTINUE WITH EXECUTION OF DATA
				data = labels_to_parsed_data(labels);
				**/
				display_tokens(labels);
				free_token_struct(labels);
			}
		}
		free(user_input);
	}
	rl_clear_history();
	return (0);
}
