/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_interface_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 02:23:39 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:43:10 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/envir.h"
#include "libft.h"

/**
 * Allocate memory for a new environment variable node
 */
static t_env_var	*allocate_env_var_node(void)
{
	t_env_var	*new_var;

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	new_var->next = NULL;
	return (new_var);
}

/**
 * Set the properties of the environment variable node
 */
static int	set_env_var_properties(t_env_var *new_var, char *name, char *value,
		int exported)
{
	if (!name)
		return (0);
	new_var->name = ft_strdup(name);
	if (!new_var->name)
	{
		free(new_var);
		return (0);
	}
	if (value)
	{
		new_var->value = ft_strdup(value);
		if (!new_var->value)
		{
			free(new_var->name);
			free(new_var);
			return (0);
		}
	}
	else
		new_var->value = NULL;
	new_var->exported = exported;
	return (1);
}

/**
 * Create a new environment variable node
 */
t_env_var	*create_env_var(char *name, char *value, int exported)
{
	t_env_var	*new_var;

	new_var = allocate_env_var_node();
	if (!new_var)
		return (NULL);
	if (!set_env_var_properties(new_var, name, value, exported))
	{
		free(new_var);
		return (NULL);
	}
	return (new_var);
}

/**
 * @brief Add a new env variable node to the list
 */
t_env_var	*add_env_var(t_env_var **head, char *name, char *value,
		int exported)
{
	t_env_var	*new_var;
	t_env_var	*current;

	if (!head || !name)
		return (NULL);
	new_var = create_env_var(name, value, exported);
	if (!new_var)
		return (NULL);
	if (!*head)
	{
		*head = new_var;
		return (*head);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_var;
	return (*head);
}

/**
 * @brief Find an env variable by name
 */
t_env_var	*find_env_var(t_env_var *head, const char *name)
{
	t_env_var	*current;

	if (!head || !name)
		return (NULL);
	current = head;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
