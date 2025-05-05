/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:42:47 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 14:37:56 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	dup_and_close_prev(int *prev_fd)
{
	dup2(*prev_fd, STDIN_FILENO);
	close(*prev_fd);
}

static void	dup_and_close(int pipe_fd[2])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

static void	close_update_prev(int pipe_fd[2], int *prev_fd)
{
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	body(int n, t_node *segments[SEG_COUNT], t_exec_ctx *ctx,
		pid_t pids[SEG_COUNT])
{
	int	i;
	int	prev_fd;
	int	pipe_fd[2];

	prev_fd = -1;
	i = -1;
	while (++i < n)
	{
		if (i + 1 < n)
			create_pipe(pipe_fd);
		pids[i] = fork_or_die();
		if (pids[i] == 0)
		{
			if (prev_fd != -1)
				dup_and_close_prev(&prev_fd);
			if (i + 1 < n)
				dup_and_close(pipe_fd);
			apply_redirs_for(segments[i], ctx);
			_exit(pre_check(segments[i], ctx, 1));
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i + 1 < n)
			close_update_prev(pipe_fd, &prev_fd);
	}
}
