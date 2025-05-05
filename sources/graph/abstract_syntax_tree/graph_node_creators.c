/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_node_creators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:21 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 19:22:51 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

/*For now Redirections are ignored*/
t_cmd	*build_command(t_parsed_data **tokens)
{
	t_cmd			*cmd;
	t_token_type	type;

	cmd = allocate_cmd();
	type = *peek_token_label(tokens);
	while (peek_token(tokens)->data && !is_operator_token(type))
	{
		type = *peek_token_label(tokens);
		if (is_redir_token_type(type))
		{
			add_redirection(&cmd, tokens, type);
			if (cmd->redir_list == NULL)
				return (free_cmd(&cmd),NULL);
		}
		else if (!is_operator_token(type))
		{
			cmd->cmd_path = ft_strdup((*tokens)->filepath);
			add_argv(&cmd, tokens);
		}
	}
	if (cmd->redir_list == NULL && cmd->argv == NULL)
		free_cmd(&cmd);
	return (cmd);
}

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
