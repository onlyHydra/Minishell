/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_allocations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:53:19 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 02:39:28 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_interface.h"
#include "libft.h"
#include "stdlib.h"

t_subshell	*allocate_subshell(t_node *child)
{
	t_subshell	*subshell;

	subshell = malloc(sizeof(t_subshell));
	if (!subshell)
		return (NULL);
	subshell->child = child;
	return (subshell);
}

t_node	*allocate_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->u_data.cmd = NULL;
	node->u_data.sub = NULL;
	return (node);
}

t_cmd	*allocate_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_path = NULL;
	cmd->argv = NULL;
	cmd->redir_list = NULL;
	return (cmd);
}

t_redir	*allocate_redir(int type, const char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}
