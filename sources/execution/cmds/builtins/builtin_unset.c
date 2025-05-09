/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:42:09 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:45:33 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"
#include "components/error_message.h"
#include "libft.h"
#include "utils.h"

/**
 * Handle unset command
 * Format: unset [name ...]
 */
int	cmd_unset(t_env_var **env_vars, char **args)
{
	int	i;
	int	status;

	if (!env_vars || !*env_vars || !args)
		return (1);
	status = 0;
	i = 0;
	while (args[i])
	{
		if (is_valid_var_name(args[i]))
			remove_env_var(env_vars, args[i]);
		else
			status = print_unset_error(args[i]);
		i++;
	}
	return (status);
}

/**
 * Execute the unset command from parsed data
 */
int	execute_unset(char **args, t_env_var **env_vars)
{
	int	result;

	if (!args)
		return (1);
	result = cmd_unset(env_vars, args);
	return (result);
}
