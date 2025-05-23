/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:24:52 by schiper           #+#    #+#             */
/*   Updated: 2025/05/21 20:53:02 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"
#include "interfaces/token_interface.h"
#include "signal_handler.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static void	fail_redir(const char *msg, int error_code, t_exec_ctx *ctx,
		int *e_code)
{
	*e_code = error_code;
	if (msg && *msg)
	{
		write(STDERR_FILENO, "minishel: ", 10);
		perror(msg);
	}
	else
		perror("minishel");
	free_ast(&ctx->ast_root);
	free_parsed_data(ctx->parsed_data);
}

static int	open_fd(t_redir *r)
{
	int	fd;

	if (r->type == REDIRECT_IN)
		fd = open(r->filename, O_RDONLY);
	else if (r->type == REDIRECT_OUT)
		fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (r->type == REDIRECT_APPEND)
		fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

void	apply_redirections(t_redir *redir_list, t_exec_ctx *ctx, int *exit)
{
	t_redir	*r;
	int		fd;

	r = redir_list;
	*exit = 0;
	while (r && r->filename)
	{
		if (r->type == HEREDOC)
		{
			if (dup2(r->fd_heredoc, STDIN_FILENO) < 0)
				return (fail_redir(r->filename, 1, ctx, exit));
			close(r->fd_heredoc);
			r = r->next;
			continue ;
		}
		fd = open_fd(r);
		if (fd < 0)
			return (fail_redir(r->filename, 1, ctx, exit));
		if (r->type == REDIRECT_IN && dup2(fd, STDIN_FILENO) < 0)
			return (fail_redir(r->filename, 1, ctx, exit));
		else if ((r->type == 62 || r->type == 3) && dup2(fd, STDOUT_FILENO) < 0)
			return (fail_redir(r->filename, 1, ctx, exit));
		close(fd);
		r = r->next;
	}
}
