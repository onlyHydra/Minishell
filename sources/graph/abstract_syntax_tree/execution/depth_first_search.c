/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:24 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 18:24:07 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>

int	dfs_walk(t_node *root, t_exec_ctx *ctx)
{
	int	left_result;

	if (!root)
		return (0);
	if (root->type == NODE_COMMAND)
		return (execute_command(root, ctx));
	if (root->type == NODE_AND)
	{
		left_result = dfs_walk(root->left, ctx);
		if (left_result != 0)
			return (left_result);
		return (dfs_walk(root->right, ctx));
	}
	if (root->type == NODE_OR)
	{
		left_result = dfs_walk(root->left, ctx);
		if (left_result == 0)
			return (left_result);
		return (dfs_walk(root->right, ctx));
	}
	if (root->type == NODE_PIPE)
		return (execute_pipe(root, ctx));
	if (root->type == NODE_SUBSHELL)
		return (execute_subshell(root, ctx));
	return (-1);
}
