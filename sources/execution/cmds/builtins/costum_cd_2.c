/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costum_cd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:14:29 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 01:47:48 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"


/**
 * Updates OLDPWD environment variable to the previous PWD value.
 */
// void	update_oldpwd_variable(t_list **env_list, char *fallback_path)
// {
// 	t_env_var	*oldpwd_var;
// 	t_env_var	*pwd_var;

// 	oldpwd_var = get_env_var(*env_list, "OLDPWD");
// 	pwd_var = get_env_var(*env_list, "PWD");

// 	if (oldpwd_var)
// 	{
// 		free(oldpwd_var->value);
// 		if (pwd_var && pwd_var->value)
// 			oldpwd_var->value = ft_strdup(pwd_var->value);
// 		else
// 			oldpwd_var->value = ft_strdup(fallback_path);
// 	}
// }

// /**
//  * Updates both OLDPWD and PWD after a directory change.
//  */
// void	sync_working_directories(t_list **env_list)
// {
// 	char		*current_path;
// 	t_env_var	*pwd_var;

// 	current_path = getcwd(NULL, 0);
// 	if (!current_path)
// 	{
// 		perror("getcwd");
// 		return ;
// 	}

// 	update_oldpwd_variable(env_list, current_path);

// 	pwd_var = get_env_var(*env_list, "PWD");
// 	if (pwd_var)
// 	{
// 		free(pwd_var->value);
// 		pwd_var->value = current_path;
// 	}
// 	else
// 		free(current_path);
// }

// /**
//  * Validates that only zero or one argument is given to cd.
//  */
// int	validate_cd_arguments(t_list *arguments)
// {
// 	if (ft_lstsize(arguments) > 1)
// 	{
// 		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

