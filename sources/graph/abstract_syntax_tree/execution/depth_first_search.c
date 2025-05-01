/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:24 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 20:45:19 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"
#include <stdio.h>

// int	dfs_walk(t_node *root)
// {
// 	int	left_result;
// 	int	right_result;

// 	if (!root)
// 		return (0);
// 	switch (root->type)
// 	{
// 	case NODE_COMMAND:
// 		return (execute_command(root));
// 	case NODE_AND:
// 		left_result = dfs_walk(root->left);
// 		if (left_result != 0)
// 			return (left_result);
// 		return (dfs_walk(root->right));
// 	case NODE_OR:
// 		left_result = dfs_walk(root->left);
// 		if (left_result == 0)
// 			return (left_result);
// 		return (dfs_walk(root->right));
// 	case NODE_PIPE:
// 		return (execute_pipe(root));
// 	case NODE_SUBSHELL:
// 		return (execute_subshell(root));
// 	default:
// 		return (-1);
// 	}
// }
static void	print_indent(int level)
{
	for (int i = 0; i < level; i++)
		printf("  ");
}

void	dfs_walk(t_node *root)
{
	static int	depth = 0;
	t_redir		*copy;

	if (!root)
		return ;
	print_indent(depth);
	printf("Node type: ");
	switch (root->type)
	{
	case NODE_COMMAND:
		printf("COMMAND\n");
		if (root->u_data.cmd && root->u_data.cmd->argv)
		{
			print_indent(depth);
			printf("Command: %s\n", root->u_data.cmd->argv[0]);
			copy = root->u_data.cmd->redir_list;
			while (copy != NULL)
			{
				printf("Redirc Type : %d filename : %s \n", copy->type,
					copy->filename);
				copy = copy->next;
			}
		}
		break ;
	case NODE_PIPE:
		printf("PIPE\n");
		break ;
	case NODE_AND:
		printf("AND\n");
		break ;
	case NODE_OR:
		printf("OR\n");
		break ;
	case NODE_SUBSHELL:
		printf("SUBSHELL\n");
		depth++;
		dfs_walk(root->u_data.sub->child);
		depth--;
		return ; // subshell has its own subtree, no left/right traversal
		break ;
	default:
		printf("UNKNOWN\n");
		break ;
	}
	depth++;
	if (root->left)
	{
		print_indent(depth - 1);
		printf("Left:\n");
		dfs_walk(root->left);
	}
	if (root->right)
	{
		print_indent(depth - 1);
		printf("Right:\n");
		dfs_walk(root->right);
	}
	depth--;
}
