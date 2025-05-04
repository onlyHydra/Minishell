/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:24:52 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 01:40:54 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	apply_redirections(t_redir *redir_list)
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
		else
			return (perror("minishel: "),-1);
		if (fd < 0)
			return (perror("minishel: "),-1);
		if (r->type == REDIRECT_IN && dup2(fd, STDIN_FILENO) < 0)
			return (perror("minishel: "),-1);
		else if ((r->type == REDIRECT_OUT || r->type == REDIRECT_APPEND)
			&& dup2(fd, STDOUT_FILENO) < 0)
			return (perror("minishel: "),-1);
		close(fd);
		r = r->next;
	}
	return (0);
}
