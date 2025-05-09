/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_enviromental.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:41:23 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:47:16 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/envir.h"
#include "libft.h"
#include "signals.h"

/**
 * Allocate memory for name and value from the environment string
 * Returns 0 on failure, 1 on success
 */
static int	allocate_name_value(char *env_str, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign && *name != NULL)
	{
		*name = ft_strdup(env_str);
		*value = NULL;
		return (1);
	}
	*name = malloc(equal_sign - env_str + 1);
	if (!*name)
		return (0);
	ft_strlcpy(*name, env_str, equal_sign - env_str + 1);
	*value = ft_strdup(equal_sign + 1);
	if (!*value)
	{
		free(*name);
		return (0);
	}
	return (1);
}

/**
 * Add environment variable to the list, freeing resources on failure
 */
static int	add_env_var_to_list(t_env_var **head, char *name, char *value)
{
	if (!add_env_var(head, name, value, 1))
	{
		free(name);
		free(value);
		return (0);
	}
	return (1);
}

/**
 * Free allocated memory for the environment variables
 */
static void	free_env_var_resources(t_env_var **head, char *name, char *value)
{
	free(name);
	free(value);
	free_env_vars(head);
}

/**
 * Initialize environment variables from envp
 * This parses each NAME=VALUE string into our environment variable structure
 */
t_env_var	*init_env_vars(char **envp)
{
	t_env_var	*head;
	char		*name;
	char		*value;
	int			i;

	head = NULL;
	name = NULL;
	value = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (allocate_name_value(envp[i], &name, &value))
		{
			if (!add_env_var_to_list(&head, name, value))
			{
				free_env_var_resources(&head, name, value);
				return (NULL);
			}
			free(name);
			free(value);
		}
	}
	return (head);
}

/**
 * Initialize environment variables
 * @param envp: Environment variables
 * @return: Initialized env_vars or NULL on error
 */
t_env_var	*setup_environment(char **envp)
{
	t_env_var	*env_vars;

	if (envp == NULL)
		return (NULL);
	env_vars = init_env_vars(envp);
	if (!env_vars)
		return (NULL);
	setup_interactive_signals();
	return (env_vars);
}
