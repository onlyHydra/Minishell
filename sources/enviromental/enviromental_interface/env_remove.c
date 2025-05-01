/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromental_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:11:14 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 18:12:59 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * @brief Free an env variable node
 */
static void	free_env_node(t_env_var *node)
{
	if (!node)
		return ;
	free(node->name);
	free(node->value);
	free(node);
}

/**
 * @brief Remove an env variable
 */
int	remove_env_var(t_env_var **head, const char *name)
{
	t_env_var	*curr;
	t_env_var	*prev;

	if (!head || !*head || !name)
		return (1);
	curr = *head;
	if (ft_strcmp(curr->name, name) == 0)
	{
		*head = curr->next;
		free_env_node(curr);
		return (0);
	}
	prev = curr;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			prev->next = curr->next;
			free_env_node(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}
