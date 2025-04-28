/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:24 by schiper           #+#    #+#             */
/*   Updated: 2025/04/28 21:17:07 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_functions.h"

int	dfs_walk(t_node *root)
{
	int	left_result;
	int	right_result;

	if (!root)
		return (0);
	switch (root->type)
	{
	case NODE_COMMAND:
		return (execute_command(root));
	case NODE_AND:
		left_result = dfs_walk(root->left);
		if (left_result != 0)
			return (left_result);
		return (dfs_walk(root->right));
	case NODE_OR:
		left_result = dfs_walk(root->left);
		if (left_result == 0)
			return (left_result);
		return (dfs_walk(root->right));
	case NODE_PIPE:
		return (execute_pipe(root));
	case NODE_SUBSHELL:
		return (execute_subshell(root));
	default:
		return (-1);
	}
}
