/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromental_interface_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:36:54 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 02:08:22 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * @brief Get the value of an env variable
 */
char	*get_env_value(t_env_var *head, const char *name)
{
	t_env_var	*var;

	var = find_env_var(head, name);
	if (var)
		return (var->value);
	return (NULL);
}

/**

	* @brief Update the value of an existing env variable or create new if not exists
 */
int	update_env_var(t_env_var **head, const char *name, const char *value,
		int exported)
{
	t_env_var	*var;
	char		*new_value;

	if (!head || !name)
		return (1);
	var = find_env_var(*head, name);
	if (var)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (1);
		free(var->value);
		var->value = new_value;
		if (exported)
			var->exported = 1;
		return (0);
	}
	if (!add_env_var(head, (char *)name, (char *)value, exported))
		return (1);
	return (0);
}

/**
 * @brief Remove an env variable
 */
int	remove_env_var(t_env_var **head, const char *name)
{
	t_env_var	*current;
	t_env_var	*prev;

	if (!head || !*head || !name)
		return (1);
	current = *head;
	prev = NULL;
	if (ft_strcmp(current->name, name) == 0)
	{
		*head = current->next;
		free(current->name);
		free(current->value);
		free(current);
		return (0);
	}
	while (current && ft_strcmp(current->name, name) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (1);
	prev->next = current->next;
	free(current->name);
	free(current->value);
	free(current);
	return (0);
}

/**
 * @brief Free all env variables
 */
void	free_env_vars(t_env_var *head)
{
	t_env_var	*current;
	t_env_var	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}
