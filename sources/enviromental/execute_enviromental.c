/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_enviromental.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:55:20 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 02:08:12 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "execution.h"
#include "minishell.h"
#include "models/token_struct.h"

/**
 * Main execution handler for environment commands
 * Integrates with the overall command execution system
 */
int	handle_env_commands(t_parsed_data *data, t_env_var **env_vars)
{
	if (!data || !data->data || !env_vars)
		return (1);
	if (ft_strcmp(data->data, "export") == 0)
		return (execute_export(data, env_vars));
	else if (ft_strcmp(data->data, "unset") == 0)
		return (execute_unset(data, env_vars));
	else if (ft_strcmp(data->data, "env") == 0)
		return (cmd_env(*env_vars));
	return (-1);
}
