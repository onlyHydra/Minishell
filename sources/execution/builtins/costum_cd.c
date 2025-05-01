/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costum_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:14:12 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 01:47:42 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Changes directory to the user's HOME if set.
 */
// int	change_to_home_directory(t_list **env_list)
// {
// 	t_env_var	*home_var;

// 	home_var = get_env_var(*env_list, "HOME");
// 	if (!home_var || !home_var->value)
// 	{
// 		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	if (chdir(home_var->value) == -1)
// 	{
// 		ft_putstr_fd("cd: ", STDERR_FILENO);
// 		perror(home_var->value);
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

/**
 * Custom implementation of `cd` command.
 */
// int	builtin_cd(t_list **env_list, t_list *arguments)
// {
// 	char	*target_path;

// 	if (check_args(arguments) != EXIT_SUCCESS)
// 		return (EXIT_FAILURE);

// 	if (!arguments)
// 	{
// 		if (change_to_home_directory(env_list) != EXIT_SUCCESS)
// 			return (EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		target_path = ((t_argument *)arguments->content)->word;
// 		if (chdir(target_path) == -1)
// 		{
// 			ft_putstr_fd("cd: ", STDERR_FILENO);
// 			perror(target_path);
// 			return (EXIT_FAILURE);
// 		}
// 	}

// 	update_dirs(env_list);
// 	return (EXIT_SUCCESS);
// }
