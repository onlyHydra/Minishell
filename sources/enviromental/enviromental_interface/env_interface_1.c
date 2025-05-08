/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_interface_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:36:54 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:43:10 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/envir.h"

/**
 * Retrieves the value associated with a given environment variable name.
 *
 * @param head Pointer to the head of the environment variable list.
 * @param name The name of the environment variable to look up.
 * @return The value of the variable if found, otherwise NULL.
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
 * Updates the value of an existing environment variable or creates a new one.
 *
 * @param head Pointer to the head of the environment variable list.
 * @param name The name of the variable to update or create.
 * @param value The new value to assign to the variable. If NULL,
	an empty string is used.

	* @param exported Flag indicating whether the variable
		should be marked as exported (1) or not (0).
 * @return 0 on success, 1 on failure.
 */
int	update_env_var(t_env_var **head, const char *name, const char *value,
		int exported)
{
	t_env_var	*var;

	if (!head || !name)
		return (1);
	var = find_env_var(*head, name);
	if (var)
	{
		if (var->value)
			free(var->value);
		if (value)
			var->value = ft_strdup(value);
		else
			var->value = NULL;
		if (exported)
			var->exported = 1;
		return (0);
	}
	else
	{
		if (!add_env_var(head, (char *)name, (char *)value, exported))
			return (1);
		return (0);
	}
}

/**
 * Frees all memory associated with the environment variable list.
 *
 * @param head Pointer to the head of the environment variable list.
 */
void	free_env_vars(t_env_var **head)
{
	t_env_var	*current;
	t_env_var	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	head = NULL;
}
