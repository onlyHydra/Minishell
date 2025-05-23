/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:24 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 13:34:22 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"
#include "models/envir_struct.h"
#include <stdio.h>
#include <unistd.h>

int	dfs_walk(t_node *root, t_exec_ctx *ctx, int pipe_flag)
{
	int	left_result;

	if (!root)
		return (0);
	if (root->type == NODE_COMMAND)
		return (execute_command(root, ctx, pipe_flag));
	if (root->type == NODE_AND)
	{
		left_result = dfs_walk(root->left, ctx, pipe_flag);
		if (left_result != 0)
			return (left_result);
		return (dfs_walk(root->right, ctx, pipe_flag));
	}
	if (root->type == NODE_OR)
	{
		left_result = dfs_walk(root->left, ctx, pipe_flag);
		if (left_result == 0)
			return (left_result);
		return (dfs_walk(root->right, ctx, pipe_flag));
	}
	if (root->type == NODE_PIPE)
		return (execute_n_pipe(root, ctx));
	if (root->type == NODE_SUBSHELL)
		return (execute_subshell(root, ctx, pipe_flag));
	return (-1);
}
