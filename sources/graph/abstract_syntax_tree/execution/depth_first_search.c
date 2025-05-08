/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:24 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 13:40:34 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>

int	dfs_walk(t_node *root, t_exec_ctx *ctx, int pipe_flag)
{
	int	left_result;
	int	exit_code;

	if (!root)
		return (0);
	exit_code = 0;
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
	ctx->exit_status = exit_code;
	return (-1);
}
