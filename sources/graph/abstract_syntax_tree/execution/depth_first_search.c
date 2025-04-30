/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:24 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 18:53:46 by iatilla-         ###   ########.fr       */
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
int	dfs_walk(t_node *root)
{
	if (!root)
		return (0);
	printf("Visiting node of type: ");
	switch (root->type)
	{
	case NODE_COMMAND:
		printf("NODE_COMMAND\n");
		if (root->u_data.cmd && root->u_data.cmd->argv)
			printf("Command: %s\n", root->u_data.cmd->argv[0]);
		break ;
	case NODE_PIPE:
		printf("NODE_PIPE\n");
		break ;
	case NODE_AND:
		printf("NODE_AND\n");
		break ;
	case NODE_OR:
		printf("NODE_OR\n");
		break ;
	case NODE_SUBSHELL:
		printf("NODE_SUBSHELL\n");
		break ;
	default:
		printf("NODE_UNKNOWN\n");
		break ;
	}
	dfs_walk(root->left);
	dfs_walk(root->right);
	return (0);
}
// Recursively traverse the left and right subtrees
// Return success (or handle specific logic for node types if needed)
