/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:38:45 by schiper           #+#    #+#             */
/*   Updated: 2025/05/02 15:49:13 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <fcntl.h>
#include <stdio.h>



int	execute_command(t_node *node, char **env)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	cmd = node->u_data.cmd;
	pid = fork();
	if (pid == 0)
	{
		if (apply_redirections(cmd->redir_list) < 0)
		{
			perror("redirections");
			exit(1);
		}
		exit(run_execve(cmd->cmd_path, cmd->argv, env));
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (((status)&0x7f) == 0)
			return (((status)&0xff00) >> 8);
		return (1);
	}
	perror("fork");
	return (1);
}
