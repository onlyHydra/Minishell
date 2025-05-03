/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:42:16 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 22:52:57 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "minishell.h"

/**
 * Count the number of arguments in parsed_data (excluding the command)
 */
static int	count_args(t_parsed_data *data)
{
	int				count;
	t_parsed_data	*current;

	count = 0;
	current = data;
	while (current && current->data)
	{
		current++;
		count++;
	}
	return (count);
}

/**
 * Convert parsed_data arguments to string array for env commands
 * Skip the command name itself
 */
char	**get_args_from_data(t_parsed_data *data)
{
	int				count;
	char			**args;
	int				i;
	t_parsed_data	*current;

	count = count_args(data);
	i = 0;
	if (count <= 1)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * count);
	if (!args)
		return (NULL);
	current = data + 1;
	while (current && current->data && i < count - 1)
	{
		args[i] = ft_strdup(current->data);
		if (!args[i])
			return (free_args(args), NULL);
		current++;
		i++;
	}
	args[i] = NULL;
	return (args);
}

/**
 * Execute the export command
 * Format: export [name[=value] ...]
 */
int	execute_export(t_parsed_data *data, t_env_var **env_vars)
{
	char	**args;
	int		result;

	if (!env_vars || !*env_vars)
		return (1);
	args = get_args_from_data(data);
	result = cmd_export(env_vars, args);
	free_args(args);
	return (result);
}
