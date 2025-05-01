/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:42:09 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 01:48:08 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "minishell.h"

/**
 * Execute the unset command
 * Format: unset [name ...]
 */
int	execute_unset(t_parsed_data *data, t_env_var **env_vars)
{
	char	**args;
	int		result;

	if (!env_vars || !*env_vars)
		return (1);
	
	args = get_args_from_data(data);
	result = cmd_unset(env_vars, args);
	free_args(args);
	return (result);
}
