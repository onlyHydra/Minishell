/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:45 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 22:09:32 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <fcntl.h>
#include <stdio.h>

static int	pre_check_command(t_cmd *cmd, t_exec_ctx *ctx)
{
	int		exit_code;
	char	*filepath;
	char	**argv;
	char	**envp;

	filepath = cmd->cmd_path;
	argv = cmd->argv;
	envp = ctx->envp;
	exit_code = run_execve(filepath, argv, envp);
	free_cmd(&cmd);
	free_ast(&ctx->ast_root);
	free_parsed_data(ctx->parsed_data);
	return (exit_code);
}

int	execute_command(t_node *node, t_exec_ctx *ctx)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	cmd = node->u_data.cmd;
	pid = fork();
	if (pid == 0)
	{
		if (apply_redirections(cmd->redir_list) < 0)
		{
			perror("redirections");
			_exit(1);
		}
		_exit(pre_check_command(cmd, ctx));
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
