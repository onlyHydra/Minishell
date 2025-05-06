/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:12:42 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/06 16:24:03 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "minishell.h"

/**
 * Free the existing environment variable array
 * @param envp: Array of environment variables to free
 */
static void	free_envp(char ***envp)
{
	int	i;

	if (!envp || !*envp)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = NULL;
}

/**
 * Count the number of environment variables in the linked list
 * that need to be exported to envp
 * @param env_vars: Linked list of environment variables
 * @return: Number of exported variables
 */
static int	count_exported_env_vars(t_env_var *env_vars)
{
	t_env_var	*current;
	int			count;

	count = 0;
	current = env_vars;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	return (count);
}

/**
 * Create a string in "NAME=VALUE" format for environment variable
 * @param var: Environment variable node
 * @return: Allocated string in "NAME=VALUE" format
 */
static char	*create_env_string(t_env_var *var)
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
 * Update the environment variables array with the current state
 * of the linked list.
 * @param env_vars: Linked list of environment variables
 * @param envp: Pointer to the environment variables array to update
 * @return: 0 on success, 1 on failure
 */
int	update_envp(t_env_var *env_vars, char ***envp)
{
	int			count;
	int			i;
	t_env_var	*current;
	char		**new_envp;

	count = count_exported_env_vars(env_vars);
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (1);
	i = 0;
	current = env_vars;
	while (current)
	{
		if (current->exported)
		{
			new_envp[i] = create_env_string(current);
			if (!new_envp[i])
				return (free_args(new_envp), 1);
			i++;
		}
		current = current->next;
	}
	new_envp[i] = NULL;
	free_envp(envp);
	*envp = new_envp;
	return (0);
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**local_envp;

	i = 0;
	while (envp[i])
		i++;
	local_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!local_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		local_envp[i] = ft_strdup(envp[i]);
		if (!local_envp[i])
		{
			free_args(local_envp);
			return (NULL);
		}
		i++;
	}
	local_envp[i] = NULL;
	return (local_envp);
}
