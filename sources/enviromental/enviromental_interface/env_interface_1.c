/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_interface_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:36:54 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/06 16:08:12 by iatilla-         ###   ########.fr       */
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
 * Update the value of an existing env variable or create a new one
 * @param head: Pointer to the head of env_var list
 * @param name: Variable name
 * @param value: New value
 * @param exported: Flag to mark exported(1) or not (0)
 * @return 0 if successful, 1 if failed
 */
int	update_env_var(t_env_var **head, const char *name, const char *value,
		int exported)
{
	t_env_var	*var;

	if (!head || !name)
		return (1);
	// First check if variable already exists
	var = find_env_var(*head, name);
	if (var)
	{
		// Update existing variable
		if (var->value)
			free(var->value);
		// Set new value
		if (value)
			var->value = ft_strdup(value);
		else
			var->value = ft_strdup(""); // Empty string instead of NULL
		// If export flag is set, mark it as exported
		if (exported)
			var->exported = 1;
		return (0);
	}
	else
	{
		// Create new variable
		if (!add_env_var(head, (char *)name, (char *)value, exported))
			return (1);
		return (0);
	}
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
