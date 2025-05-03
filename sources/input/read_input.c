/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:37:37 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/03 08:46:52 by schiper          ###   ########.fr       */
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
	t_node			*ast_root;
	t_node			*ast_copy;

	if (data == NULL)
		return (1);
	copy = data;
	ast_root = parse_expression(&copy);
	ast_copy = ast_root;
	exit_code = dfs_walk(ast_root, env);
	free_ast(ast_copy);
    free_parsed_data(data);
    ast_root = NULL;
    copy = NULL;
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

	// char			*expanded_input;
	add_history(user_input);
	labels = process_input(user_input, envp);
	if (!labels)
		return (exit_status);
	// expanded_input = 0;
	display_tokens(labels);
	data = tokens_to_parsed_data(labels);
	free_token_struct(labels);
	exit_status = execution(data, &env_vars);
	print_ast(data, envp);
	// free_parsed_data(data);
	// free_token_struct(labels);
	// if (expanded_input)
	// {
	//     free(expanded_input);
	// }
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
	t_env_var	*env_vars;

	env_vars = setup_environment(envp);
	if (!env_vars)
		return (1);
	command_loop(envp, env_vars);
	free_env_vars(env_vars);
    clear_history();
	rl_clear_history();
	return (0);
}
