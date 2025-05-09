/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:24:52 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 19:24:46 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"
#include "signal_handler.h"
#include "interfaces/token_interface.h"
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

static void	error_msg(t_redir *r)
{
	write(STDERR_FILENO,
		"minishel: warning: heredoc delimited by end-of-file (wanted `", 61);
	write(STDERR_FILENO, r->filename, strlen(r->filename));
	write(STDERR_FILENO, "`)\n", 3);
}
static int	handle_heredoc(t_redir *r, t_exec_ctx *ctx)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		fail_redir("pipe", 1, ctx);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			error_msg(r);
			break ;
		}
		if (ft_strcmp(line, r->filename) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	r->fd_heredoc = pipefd[0];
	return (0);
}

void	preprocess_heredocs(t_redir *redir_list, t_exec_ctx *ctx)
{
	t_redir	*r;

	r = redir_list;
	while (r)
	{
		if (r->type == HEREDOC)
			handle_heredoc(r, ctx);
		r = r->next;
	}
}

void	apply_redirections(t_redir *redir_list, t_exec_ctx *ctx)
{
	t_redir	*r;
	int		fd;

	r = redir_list;
	while (r && r->filename)
	{
		if (r->type == REDIRECT_IN)
			fd = open(r->filename, O_RDONLY);
		else if (r->type == REDIRECT_OUT)
			fd = open(r->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (r->type == REDIRECT_APPEND)
			fd = open(r->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (r->type == HEREDOC)
		{
			if (dup2(r->fd_heredoc, STDIN_FILENO) < 0)
				fail_redir(r->filename, 1, ctx);
			close(r->fd_heredoc);
			r = r->next;
			continue ;
		}
		if (fd < 0)
			fail_redir(r->filename, 1, ctx);
		close(fd);
		r = r->next;
	}
}
