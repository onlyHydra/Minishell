/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costum_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/06 14:06:45 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/**
 * Changes directory to the user's HOME if set.
 */
int	change_to_home_directory(t_env_var **env_vars)
{
	char	*home_value;

	home_value = get_env_value(*env_vars, "HOME");
	if (!home_value || !*home_value)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(home_value) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(home_value);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Updates OLDPWD and PWD environment variables after directory change
 */
void	update_dirs(t_env_var **env_vars)
{
	char	*current_path;
	char	*old_pwd;

	// Get current path
	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		perror("getcwd");
		return ;
	}
	// Get old PWD and update OLDPWD
	old_pwd = get_env_value(*env_vars, "PWD");
	if (old_pwd)
		update_env_var(env_vars, "OLDPWD", old_pwd, 1);
	// Update PWD
	update_env_var(env_vars, "PWD", current_path, 1);
	free(current_path);
}

/**
 * Validates cd arguments count
 */
static int	validate_cd_arguments(t_parsed_data *data)
{
	int				count;
	t_parsed_data	*current;

	count = 0;
	current = data;
	// Count arguments (excluding the command itself)
	while (current && current->data)
	{
		count++;
		current++;
	}
	if (count > 2) // More than "cd" + one path
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Custom implementation of `cd` command.
 */
int	builtin_cd(t_parsed_data *data, t_env_var **env_vars)
{
	t_parsed_data	*target;

	if (validate_cd_arguments(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	// Get argument (if any)
	target = data + 1;
	// If no argument, change to HOME
	if (!target || !target->data)
	{
		if (change_to_home_directory(env_vars) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		// Change to specified directory
		if (chdir(target->data) == -1)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			perror(target->data);
			return (EXIT_FAILURE);
		}
	}
	// Update environment variables
	update_dirs(env_vars);
	return (EXIT_SUCCESS);
}
