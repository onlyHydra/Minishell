/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:17 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 00:11:06 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "tokener.h"
#include "envir.h"
#include "execution.h"
#include <stdio.h>

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
	sa_int.sa_flags = SA_RESTART; 
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
	t_token		*labels;
	char		*user_input;
	char		*expanded_input;
	t_env_var	*env_vars;
	int			exit_status;

	if (envp == NULL)
		return (1);
	env_vars = init_env_vars(envp);
	if (!env_vars)
		return (1);
	exit_status = 0;
	setup_interactive_signals();
	while (1)
	{
		user_input = readline("minishell> ");
		if (user_input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}
		if (*user_input != '\0')
		{
			add_history(user_input);
			expanded_input = expand_env_vars(user_input, env_vars, exit_status);
			if (expanded_input)
			{
				labels = process_input(expanded_input, envp);
				if (labels)
				{
					/** CONTINUE WITH EXECUTION OF DATA **/
					t_parsed_data *data = tokens_to_parsed_data(labels);
					exit_status = execution(data, &env_vars);
					display_tokens(labels);
					free_token_struct(labels);
				}
				free(expanded_input);
			}
		}
		free(user_input);
	}
	free_env_vars(env_vars);
	rl_clear_history();
	return (0);
}
