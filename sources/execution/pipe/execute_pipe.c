/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:16:27 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 18:21:28 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	redirect_and_exec_left(t_node *left, t_exec_ctx *ctx, int pipe[2])
{
	int	exit_code;

	close(pipe[0]);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	exit_code = dfs_walk(left, ctx);
	free_ast(&ctx->ast_root);
	_exit(exit_code);
}

static void	redirect_and_exec_right(t_node *right, t_exec_ctx *ctx, int pipe[2])
{
	int	exit_code;

	close(pipe[1]);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	exit_code = dfs_walk(right, ctx);
	free_ast(&ctx->ast_root);
	_exit(exit_code);
}

static pid_t	fork_or_die(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	execute_pipe(t_node *root, t_exec_ctx *ctx)
{
	int		pipe_fds[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	if (create_pipe(pipe_fds) == -1)
		return (1);
	left_pid = fork_or_die();
	if (left_pid == 0)
		redirect_and_exec_left(root->left, ctx, pipe_fds);
	right_pid = fork_or_die();
	if (right_pid == 0)
		redirect_and_exec_right(root->right, ctx, pipe_fds);
	close_pipe(pipe_fds);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (((status) & 0x7f) == 0)
		return (((status) & 0xff00) >> 8);
	return (1);
}
