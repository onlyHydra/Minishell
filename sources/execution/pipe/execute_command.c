/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:45 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 13:52:53 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "execution.h"
#include <fcntl.h>
#include <stdio.h>

static int	check_unset_export(t_cmd *cmd, t_exec_ctx *ctx)
{
	char	*cmd_name;
	int		exit_code;

	cmd_name = *cmd->argv;
	if (ft_strcmp(cmd_name, "export") == 0 && *(cmd->argv + 1) != NULL)
	{
		apply_redirections(cmd->redir_list, ctx);
		exit_code = execute_export(cmd->argv, &ctx->envp);
		return (exit_code);
	}
	if (ft_strcmp(cmd_name, "unset") == 0)
	{
		apply_redirections(cmd->redir_list, ctx);
		exit_code = execute_unset(cmd->argv, &ctx->envp);
		return (exit_code);
	}
	return (-2);
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
	return (exit_code);
}

static void print_exit_status(int exit_status)
{
	char *status_str;
	
	status_str = ft_itoa(exit_status);
	if (status_str)
	{
		write(STDOUT_FILENO, status_str, ft_strlen(status_str));
		write(STDOUT_FILENO, "\n", 1);
		free(status_str);
	}
}

int	execute_command(t_node *node, t_exec_ctx *ctx, int pipe_flag)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	pid = -1;
	status = -2;
	cmd = node->u_data.cmd;
	if (cmd->cmd_path && ft_strcmp(cmd->cmd_path, "$?") == 0)
	{
		print_exit_status(ctx->exit_status);
		return (ctx->exit_status);
	}
	if (cmd->argv && cmd->argv[0] && ft_strcmp(cmd->argv[0], "$?") == 0)
	{
		print_exit_status(ctx->exit_status);
		return (ctx->exit_status);
	}
	if (ft_strcmp(cmd->cmd_path, "built-in") == 0)
		status = check_unset_export(cmd, ctx);
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
