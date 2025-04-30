/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_node_creators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:21 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 18:49:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

/*For now Redirections are ignored*/
t_cmd	*build_command(t_parsed_data **tokens)
{
	t_cmd	*cmd;

	cmd = allocate_cmd();
	while (!is_operator_token(*tokens))
	{
		if (*peek_token_label(tokens) == CMD)
			add_argv(&cmd, tokens);
	}
	return (cmd);
}
// advance_token(tokens);

t_node	*create_command_node(t_cmd *cmd)
{
	t_node	*node;

	node = allocate_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	node->u_data.cmd = cmd;
	return (node);
}

t_node	*create_subshell_node(t_node *child_ast)
{
	t_node	*node;

	node = allocate_node(NODE_SUBSHELL);
	if (!node)
		return (NULL);
	node->u_data.sub = allocate_subshell(child_ast);
	if (!node->u_data.sub)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_node	*create_binary_node(t_node_type type, t_node *left, t_node *right)
{
	t_node		*node;
	t_node_type	placeholder;

	placeholder = type;
	node = allocate_node(placeholder);
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}
