/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromental_interface_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:36:54 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 18:10:05 by iatilla-         ###   ########.fr       */
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
	* @brief Update the value of an existing env variable 
	or create new if not exists
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

/**
 * Check if variable name is valid
 * Valid names start with letter or underscore and contain only
 * alphanumeric characters and underscores
 */
int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
