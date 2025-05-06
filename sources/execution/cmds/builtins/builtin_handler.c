/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:02:56 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/06 16:48:29 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "envir.h"

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
 * Execute a built-in command
 */
int	execute_builtin(t_parsed_data *data, t_env_var **env_vars)
{
	int	fds[2];
	int	exit_flag;

	if (!data || !data->data)
		return (-1);
	fds[0] = STDIN_FILENO;
	fds[1] = STDOUT_FILENO;
	exit_flag = 1;
	if (ft_strcmp(data->data, "echo") == 0)
		return (builtin_echo(data, fds));
	/** FIX THOSE */
	else if (ft_strcmp(data->data, "exit") == 0)
		return (builtin_exit(data, &exit_flag));
	/**  */
	else if (ft_strcmp(data->data, "export") == 0)
		return (execute_export(data, env_vars));
	else if (ft_strcmp(data->data, "unset") == 0)
		return (execute_unset(data, env_vars));
	else if (ft_strcmp(data->data, "cd") == 0)
		return (builtin_cd(data, env_vars));
	else if (ft_strcmp(data->data, "pwd") == 0)
		return (builtin_pwd(env_vars));
	else if (ft_strcmp(data->data, "env") == 0)
		return (cmd_env(*env_vars));
	return (-1);
}

/**
 * Checks if command is a builtin and executes it
 * @param data: Parsed command data
 * @param env_vars: Environment variables
 * @param exit_status: Pointer to exit status
 * @return: 1 if command was handled, 0 if not a builtin
 */
int	handle_builtin(t_parsed_data *data, t_env_var **env_vars, int *exit_status)
{
	int	result;

	if (!data || !data->data)
		return (0);
	if (!is_builtin(data->data))
		return (0);
	result = execute_builtin(data, env_vars);
	if (ft_strcmp(data->data, "exit") == 0 && *exit_status != -1)
		exit(*exit_status);
	*exit_status = result;
	return (1);
}
