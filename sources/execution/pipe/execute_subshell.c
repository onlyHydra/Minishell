/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:53:47 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 14:35:59 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_subshell(t_node *node, t_exec_ctx *ctx, int pipe_flag)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	exit_code = 1;
	pid = fork();
	if (pid == 0)
	{
		exit_code = dfs_walk(node->u_data.sub->child, ctx, pipe_flag);
		free_ast(&ctx->ast_root);
		_exit(exit_code);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (((status)&0x7f) == 0)
			return (((status)&0xff00) >> 8);
		return (1);
	}
	perror("fork");
	return (1);
}
