/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:19:28 by schiper           #+#    #+#             */
/*   Updated: 2025/05/14 18:40:21 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"
#include "interfaces/graph_interface.h"

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
		if (i == n - 1 && ((status)&0x7f) == 0)
			code = ((status)&0xff00) >> 8;
		i++;
	}
	return (code);
}

int	execute_n_pipe(t_node *root, t_exec_ctx *ctx, int pipe_flag)
{
	t_node	*segments[SEG_COUNT];
	int		n;
	pid_t	pids[SEG_COUNT];
	int		i;
	t_node	*tmp;

	n = collect_pipe_segments(root, segments, SEG_COUNT);
	i = 0;
	if (!pipe_flag)
		while (i < n)
		{
			if (segments[i]->type == NODE_COMMAND)
				preprocess_heredocs(segments[i]->u_data.cmd->redir_list, ctx);
			else
			{
				tmp = flatten_pipe(segments[i], 2);
                preprocess_heredocs(tmp->left->u_data.cmd->redir_list, ctx);
                preprocess_heredocs(segments[i]->u_data.cmd->redir_list, ctx);
			}
			i++;
		}
	body(n, segments, ctx, pids);
	return (wait_children(n, pids));
}
