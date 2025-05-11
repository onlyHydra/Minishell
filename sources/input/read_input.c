/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:37:37 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 21:46:59 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/abstract_syntax_tree.h"
#include "components/envir.h"
#include "components/execution.h"
#include "interfaces/envir_interface.h"
#include "signal_handler.h"

int	print_tokens(t_token *tokens);

/**
 * Handle user input when it's not empty
 * @param user_input: Input string
 * @param envp: Environment variables array
 * @param env_vars: Environment variables struct
 * @param exit_status: Current exit status
 * @return: New exit status
 */
static int	process_user_input(char *user_input, char ***envp, int exit_status)
{
	t_token			*labels;
	t_parsed_data	*data;

	add_history(user_input);
	labels = process_input(user_input, *envp, exit_status);
	data = tokens_to_parsed_data(labels);
	printf("\n============= TOKENIZATION ===========\n");
	print_tokens(labels);
	free_token_struct(&labels);
	exit_status = print_ast(data, envp, exit_status);
	return (exit_status);
}

/**
 * Main command processing loop
 * @param envp: Environment variables array
 * @param env_vars: Environment variables struct
 * @return: Exit status
 */
static int	command_loop(char ***envp)
{
	char	*user_input;
	int		exit_status;

	exit_status = 0;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	setup_interactive_signals();
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		user_input = readline("minishell> ");
		if (user_input == NULL)
			break ;
		if (*user_input != '\0')
			exit_status = process_user_input(user_input, envp, exit_status);
		free(user_input);
	}
	write(STDERR_FILENO, "exit\n", 5);
	return (exit_status);
}

/**
 * Modified main input reading loop that properly handles cleanup
 * user_input == NULL Handles EOF (Ctrl+D)
 * @param envp: Environment variables
 * @return: 0 for success, 1 for error
 */
int	read_loop(char **envp)
{
	char	**local_envp;
	int		exit_status;

	local_envp = copy_envp(envp);
	if (local_envp == NULL)
		return (-1);
	exit_status = command_loop(&local_envp);
	clear_history();
	rl_clear_history();
	free_args(local_envp);
	return (exit_status);
}
