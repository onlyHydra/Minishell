/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:31:45 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 02:08:52 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "execution.h"
#include "minishell.h"

/**
 * Main execution p
 *
 */
int	execution(t_parsed_data *data, t_env_var **env_vars)
{
	int	size;

	if (is_builtin_command(data->data) == 1)
	{
		size = ft_strlen(data->data);
		if (ft_strncmp(data->data, "export", size) == 0
			|| ft_strncmp(data->data, "unset", size) == 0
			|| ft_strncmp(data->data, "env", size) == 0)
		{
			return (handle_env_commands(data, env_vars));
		}
	}
	return (-1);
}
// if (ft_strncmp(data->data, "echo") == 0)
// 	return (handle_echo(data));
// else if (ft_strncmp(data->data, "cd") == 0)
// 	return (handle_cd(data));
// else if (ft_strncmp(data->data, "pwd") == 0)
// 	return (handle_pwd(data));
// else if (ft_strncmp(data->data, "exit") == 0)
// 	return (handle_exit(data));
