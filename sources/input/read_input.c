/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:37:37 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/07 15:50:54 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "envir.h"
#include "execution.h"
#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

/**
 * Execute the abstract syntax tree
 * @param data Parsed command data
 * @param env Environment variables array
 * @return Exit code from command execution
 */
static int	print_ast(t_parsed_data *data, char ***env)
{
	int				exit_code;
	t_parsed_data	*copy;
	t_exec_ctx		ctx;

	ctx.should_exit = 0;
	ctx.subshell_flag = 0;
	copy = data;
	ctx.parsed_data = data;
	ctx.envp = init_env_vars(*env);
	ctx.ast_root = parse_expression(&copy);
	if (!ctx.ast_root)
		return (free_parsed_data(ctx.parsed_data), 1);
	setup_execution_signals(); // Set signals for execution mode
	exit_code = dfs_walk(ctx.ast_root, &ctx, 0);
	setup_interactive_signals(); // Restore interactive signals after execution
	free_ast(&ctx.ast_root);
	free_parsed_data(ctx.parsed_data);
	if (ctx.should_exit == 0)
		update_envp(ctx.envp, env);
	free_env_vars(&ctx.envp);
	if (ctx.should_exit == 1 && ctx.subshell_flag == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(exit_code);
	}
	return (exit_code);
}

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
	labels = process_input(user_input, *envp);
	if (!labels)
		return (exit_status);
	data = tokens_to_parsed_data(labels);
	// check_syntax(data);
	free_token_struct(&labels);
	exit_status = print_ast(data, envp);
	// Reset the signal flag after processing
	g_signal_received = 0;
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
	setup_interactive_signals(); // Set up signals for the interactive shell
	while (1)
	{
		user_input = readline("minishell> ");
		if (user_input == NULL)
			break ;
		if (*user_input != '\0')
			exit_status = process_user_input(user_input, envp, exit_status);
		free(user_input);
		if (g_signal_received)
			g_signal_received = 0;
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
