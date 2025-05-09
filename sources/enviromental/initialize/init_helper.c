/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:34:01 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:54:54 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/envir.h"
#include "components/execution.h"

/**
 * Count the number of exported variables
 */
static int	count_exported_vars(t_env_var *head)
{
	int			count;
	t_env_var	*current;

	count = 0;
	current = head;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	return (count);
}

/**
 * Create "NAME=VALUE" string from env_var node
 */
static char	*make_env_string(t_env_var *var)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(var->name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, var->value);
	free(temp);
	return (result);
}

/**
 * Fill the env_array with exported variables
 */
static int	fill_env_array(char **env_array, t_env_var *head)
{
	t_env_var	*current;
	int			i;

	current = head;
	i = 0;
	while (current)
	{
		if (current->exported)
		{
			env_array[i] = make_env_string(current);
			if (!env_array[i])
			{
				free_args(env_array);
				return (0);
			}
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (1);
}

/**
 * Convert env_var list to char** array for execve
 */
char	**env_var_to_array(t_env_var *head)
{
	char	**env_array;
	int		count;

	count = count_exported_vars(head);
	if (count == 0)
		return (NULL);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, head))
		return (NULL);
	return (env_array);
}
