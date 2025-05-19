/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:24:52 by schiper           #+#    #+#             */
/*   Updated: 2025/05/19 18:47:59 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"
#include "interfaces/token_interface.h"
#include "signal_handler.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static void	fail_redir(const char *msg, int error_code, t_exec_ctx *ctx)
{
	if (msg && *msg)
	{
		write(STDERR_FILENO, "minishel: ", 10);
		perror(msg);
	}
	else
		perror("minishel");
	free_ast(&ctx->ast_root);
	free_parsed_data(ctx->parsed_data);
	exit(error_code);
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

void	apply_redirections(t_redir *redir_list, t_exec_ctx *ctx)
{
	t_redir	*r;
	int		fd;

	r = redir_list;
	while (r && r->filename)
	{
		if (r->type == HEREDOC)
		{
			if (dup2(r->fd_heredoc, STDIN_FILENO) < 0)
				fail_redir(r->filename, 1, ctx);
			close(r->fd_heredoc);
			r = r->next;
			continue ;
		}
		else
			fd = open_fd(r);
		if (fd < 0)
			fail_redir(r->filename, 1, ctx);
		if (r->type == REDIRECT_IN && dup2(fd, STDIN_FILENO) < 0)
			fail_redir(r->filename, 1, ctx);
		else if ((r->type == REDIRECT_OUT || r->type == REDIRECT_APPEND)
			&& dup2(fd, STDOUT_FILENO) < 0)
			fail_redir(r->filename, 1, ctx);
		close(fd);
		r = r->next;
	}
}
