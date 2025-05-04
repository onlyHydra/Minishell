/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:37:37 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/04 20:04:57 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include "envir.h"
#include "execution.h"
#include "minishell.h"

static int	print_ast(t_parsed_data *data, char **env)
{
	int				exit_code;
	t_parsed_data	*copy;
	t_exec_ctx		ctx;

	if (!data)
		return (1);
	copy = data;
	ctx.parsed_data = data;
	ctx.envp = env;
	ctx.ast_root = parse_expression(&copy);
	if (!ctx.ast_root)
		return (free_parsed_data(ctx.parsed_data), 1);
	exit_code = dfs_walk(ctx.ast_root, &ctx);
	free_ast(&ctx.ast_root);
	free_parsed_data(ctx.parsed_data);
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
static int	process_user_input(char *user_input, char **envp,
		t_env_var *env_vars, int exit_status)
{
	t_token			*labels;
	t_parsed_data	*data;

	add_history(user_input);
	labels = process_input(user_input, envp);
	if (!labels)
		return (exit_status);
	data = tokens_to_parsed_data(labels);
	free_token_struct(&labels);
	if (env_vars == NULL)
		exit_status = 0;
	exit_status = print_ast(data, envp);
	return (exit_status);
}

/**
 * Main command processing loop
 * @param envp: Environment variables array
 * @param env_vars: Environment variables struct
 * @return: Exit status
 */
static int	command_loop(char **envp, t_env_var *env_vars)
{
	char	*user_input;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		user_input = readline("minishell> ");
		if (user_input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*user_input != '\0')
			exit_status = process_user_input(user_input, envp, env_vars,
					exit_status);
		free(user_input);
	}
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
	command_loop(envp, NULL);
	clear_history();
	rl_clear_history();
	return (0);
}
