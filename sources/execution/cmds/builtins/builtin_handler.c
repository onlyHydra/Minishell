/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:02:56 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 19:20:14 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"
#include "components/envir.h"

/**
 * Check if a command is a built-in command
 */
int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/**
 * Checks if command is a builtin and executes it
 * @param data: Parsed command data
 * @param env_vars: Environment variables
 * @param exit_status: Pointer to exit status
 * @return: 1 if command was handled, 0 if not a builtin
 */
int	handle_builtin(char **data, t_env_var **env_vars, int *exit_status)
{
	int	result;

	if (!data || !data)
		return (0);
	result = execute_builtin(data, env_vars);
	*exit_status = result;
	return (result);
}

int	execute_builtin(char **argv, t_env_var **env_vars)
{
	int	fds[2];
	int	exit_flag;

	if (!argv)
		return (-1);
	fds[0] = STDIN_FILENO;
	fds[1] = STDOUT_FILENO;
	exit_flag = 1;
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv, fds));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv, &exit_flag));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (execute_export(argv, env_vars));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (execute_unset(argv, env_vars));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, env_vars));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(env_vars));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (cmd_env(*env_vars));
	return (-1);
}
