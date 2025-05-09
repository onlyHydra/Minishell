/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:45 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 23:43:48 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"
#include "components/envir.h"
#include "components/execution.h"
#include <fcntl.h>
#include <stdio.h>

// static void check_dollar_question()
// {

// }

static void	check_unset_export(t_cmd *cmd, t_exec_ctx *ctx, int *status,
		int pipe_flag)
{
	char	*cmd_name;
	int		exit_code;

	cmd_name = *cmd->argv;
	exit_code = -2;
	if (ft_strcmp(cmd_name, "export") == 0 && *(cmd->argv + 1) != NULL)
	{
		apply_redirections(cmd->redir_list, ctx);
		exit_code = execute_export(cmd->argv, &ctx->envp);
	}
	else if (ft_strcmp(cmd_name, "unset") == 0)
	{
		apply_redirections(cmd->redir_list, ctx);
		exit_code = execute_unset(cmd->argv, &ctx->envp);
	}
	else if (ft_strcmp(cmd_name, "cd") == 0)
		exit_code = builtin_cd(cmd->argv, &ctx->envp);
	else if (ft_strcmp(cmd_name, "exit") == 0 && pipe_flag == 0)
	{
		builtin_exit(cmd->argv, &exit_code);
		if (ctx->subshell_flag == 1)
			exit(exit_code);
		ctx->should_exit = 1;
	}
	*status = exit_code;
}

static int	pre_check_command(t_cmd *cmd, t_exec_ctx *ctx)
{
	int		exit_code;
	char	*filepath;
	char	**argv;

	filepath = cmd->cmd_path;
	argv = cmd->argv;
	if (ft_strcmp(filepath, "built-in") == 0)
		exit_code = handle_builtin(argv, &ctx->envp, &exit_code);
	else
		exit_code = run_execve(filepath, argv, envp_to_char(ctx->envp));
	free_ast(&ctx->ast_root);
	free_env_vars(&ctx->envp);
	free_parsed_data(ctx->parsed_data);
	free_args(ctx->env);
	return (exit_code);
}

int	execute_command(t_node *node, t_exec_ctx *ctx, int pipe_flag)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	pid = -1;
	cmd = node->u_data.cmd;
	check_unset_export(cmd, ctx, &status, pipe_flag);
	if (status == -2)
		pid = fork();
	if (pid == 0)
	{
		if (!pipe_flag)
			apply_redirections(node->u_data.cmd->redir_list, ctx);
		exit(pre_check_command(cmd, ctx));
	}
	else if (pid > 0 && status == -2)
	{
		waitpid(pid, &status, 0);
		if (((status)&0x7f) == 0)
			return (((status)&0xff00) >> 8);
		return (1);
	}
	return (status);
}
