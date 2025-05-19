/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:28:47 by schiper           #+#    #+#             */
/*   Updated: 2025/05/19 18:47:55 by schiper          ###   ########.fr       */
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

void	preprocess_heredocs(t_node *root, t_exec_ctx *ctx)
{
	t_redir *r;

	if (!root)
		return ;
	if (root->type == NODE_COMMAND)
	{
		r = root->u_data.cmd->redir_list;
		while (r)
		{
			if (r->type == HEREDOC)
				handle_heredoc(r, ctx);
			r = r->next;
		}
		return ;
	}
	if (root->type == NODE_SUBSHELL)
		return (preprocess_heredocs(root->u_data.sub->child, ctx));
	preprocess_heredocs(root->left, ctx);
	preprocess_heredocs(root->right, ctx);
}