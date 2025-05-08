/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 23:44:55 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"
#include "minishell.h"

/**
 *
 *
 */
static int	builtin_pwd_part_two(t_env_var **env_vars)
{
	char	*pwd_value;

	if (env_vars && *env_vars)
	{
		pwd_value = get_env_value(*env_vars, "PWD");
		if (pwd_value)
		{
			ft_putendl_fd(pwd_value, STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

/**
 * Implements the pwd built-in command
 * Always uses getcwd() first to ensure we display the actual current directory
 */
int	builtin_pwd(t_env_var **env_vars)
{
	char	*current_dir;
	char	*pwd_value;

	current_dir = getcwd(NULL, 0);
	if (current_dir)
	{
		ft_putendl_fd(current_dir, STDOUT_FILENO);
		if (env_vars && *env_vars)
		{
			pwd_value = get_env_value(*env_vars, "PWD");
			if (!pwd_value || ft_strcmp(pwd_value, current_dir) != 0)
				update_env_var(env_vars, "PWD", current_dir, 1);
		}
		free(current_dir);
		return (EXIT_SUCCESS);
	}
	if (builtin_pwd_part_two(env_vars) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	perror("pwd");
	return (EXIT_FAILURE);
}
