/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:16:27 by schiper           #+#    #+#             */
/*   Updated: 2025/05/02 15:57:13 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	redirect_and_exec_left(t_node *left, int pipe_write_end, char **env)
{
	close(STDOUT_FILENO);
	dup2(pipe_write_end, STDOUT_FILENO);
	close(pipe_write_end);
	exit(dfs_walk(left, env));
}

static void	redirect_and_exec_right(t_node *right, int pipe_read_end,
		char **env)
{
	close(STDIN_FILENO);
	dup2(pipe_read_end, STDIN_FILENO);
	close(pipe_read_end);
	exit(dfs_walk(right, env));
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

int	execute_pipe(t_node *root, char **env)
{
	int		pipe_fds[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status;

	if (create_pipe(pipe_fds) == -1)
		return (1);
	left_pid = fork_or_die();
	if (left_pid == 0)
		redirect_and_exec_left(root->left, pipe_fds[1], env);
	right_pid = fork_or_die();
	if (right_pid == 0)
		redirect_and_exec_right(root->left, pipe_fds[0], env);
	close_pipe(pipe_fds);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	if (((status)&0x7f) == 0)
		return (((status)&0xff00) >> 8);
	return (1);
}
