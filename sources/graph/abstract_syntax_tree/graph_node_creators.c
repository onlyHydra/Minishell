/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_node_creators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:21 by schiper           #+#    #+#             */
/*   Updated: 2025/05/02 19:11:39 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

/*For now Redirections are ignored*/
t_cmd	*build_command(t_parsed_data **tokens)
{
	t_cmd			*cmd;
	t_token_type	type;

	cmd = allocate_cmd();
	if (!cmd)
		return (NULL);
	while (peek_token(tokens)->data && !is_operator_token(*tokens))
	{
		type = *peek_token_label(tokens);
		if (type == CMD){
            cmd->cmd_path = (*tokens)->filepath;
			add_argv(&cmd, tokens);
        }
		else if (is_redir_token_type(type))
			add_redirection(&cmd, tokens);
		else
			advance_token(tokens);
	}
	if (cmd->argv == NULL)
		free_cmd(&cmd);
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
