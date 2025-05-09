/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:19:28 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 12:46:04 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"

static int	wait_children(int n, pid_t pids[SEG_COUNT])
{
	int	status;
	int	code;
	int	i;

	i = 0;
	status = 0;
	code = 1;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1 && ((status) & 0x7f) == 0)
			code = ((status) & 0xff00) >> 8;
		i++;
	}
	return (code);
}

int	execute_n_pipe(t_node *root, t_exec_ctx *ctx)
{
	t_node	*segments[SEG_COUNT];
	int		n;
	pid_t	pids[SEG_COUNT];

	n = collect_pipe_segments(root, segments, SEG_COUNT);
	body(n, segments, ctx, pids);
	return (wait_children(n, pids));
}
