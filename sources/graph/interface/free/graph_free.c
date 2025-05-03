/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:56:46 by schiper           #+#    #+#             */
/*   Updated: 2025/05/03 07:24:16 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_interface.h"
#include <stdlib.h>

void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!*cmd)
		return ;
	if ((*cmd)->argv)
	{
		while ((*cmd)->argv[i])
			free((*cmd)->argv[i++]);
		free((*cmd)->argv);
	}
	free((*cmd)->cmd_path);
	free_redir_list((*cmd)->redir_list);
	free(*cmd);
	*cmd = NULL;
}

void	free_ast(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_COMMAND)
		free_cmd(&node->u_data.cmd);
	else if (node->type == NODE_SUBSHELL)
		free_subshell(node->u_data.sub);
	free(node);
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = temp;
	}
}

void	free_subshell(t_subshell *sub)
{
	if (!sub)
		return ;
	free_ast(sub->child);
	free(sub);
}
