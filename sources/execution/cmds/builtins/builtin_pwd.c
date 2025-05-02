/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:14:23 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 00:46:03 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "envir.h"




// int	execute_pwd(t_list **ep)
// {
// 	char		*pwd_cmd;
// 	t_env_var	*temp;

// 	temp = get_env_value(,"pwd");
// 	if (temp)
// 		ft_putendl_fd(temp->value, STDOUT_FILENO);
// 	else
// 	{
// 		pwd_cmd = getcwd(NULL, 0);
// 		ft_putendl_fd(pwd_cmd, STDOUT_FILENO);
// 		free(pwd_cmd);
// 	}
// 	return (EXIT_SUCCESS);
// }

