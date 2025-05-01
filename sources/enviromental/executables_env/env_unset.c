/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:33:02 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 01:57:49 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "minishell.h"

/**
 * Handle unset command
 */
int	cmd_unset(t_env_var **env_vars, char **args)
{
	int	i;
	int	exit_status;

	if (!env_vars || !args || !args[0])
		return (0);
	exit_status = 0;
	i = 0;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else if (remove_env_var(env_vars, args[i]) != 0)
			exit_status = -1;
		i++;
	}
	return (exit_status);
}
