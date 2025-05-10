/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:53:47 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 19:20:45 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"
#include "interfaces/envir_interface.h"
#include "interfaces/token_interface.h"

int	execute_subshell(t_node *node, t_exec_ctx *ctx, int pipe_flag)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	exit_code = 1;
	pid = fork();
	if (pid == 0)
	{
		ctx->subshell_flag = 1;
		exit_code = dfs_walk(node->u_data.sub->child, ctx, pipe_flag);
		free_ast(&ctx->ast_root);
		free_env_vars(&ctx->envp);
		free_parsed_data(ctx->parsed_data);
		free_args(ctx->env);
		_exit(exit_code);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (((status)&0x7f) == 0)
			return (((status)&0xff00) >> 8);
		return (1);
	}
	return (1);
}
