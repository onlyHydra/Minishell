/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_subsh_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:03:23 by schiper           #+#    #+#             */
/*   Updated: 2025/05/28 21:03:57 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/abstract_syntax_tree.h"
#include "components/execution.h"

t_node	*parser_primary(t_parsed_data **tokens)
{
	t_node	*node;

	node = parser_subshell(tokens);
	if (!node)
		node = parser_command(tokens);
	return (node);
}

static t_redir	*attempt_redir(t_parsed_data **tokens)
{
	t_redir			*redir_list;
	t_redir			*new_redir;
	t_token_type	type;
	char			*filename;

	redir_list = NULL;
	while (peek_token(tokens)->data
		&& is_redir_token_type(*peek_token_label(tokens)))
	{
		type = *peek_token_label(tokens);
		advance_token(tokens);
		if (!peek_token(tokens) || is_operator_token(*peek_token_label(tokens))
			|| is_redir_token_type(*peek_token_label(tokens)))
			return (free_redir_list(redir_list), NULL);
		filename = peek_token(tokens)->data;
		new_redir = allocate_redir(type, filename);
		if (!new_redir)
		{
			free_redir_list(redir_list);
			return (NULL);
		}
		append_redir(&redir_list, new_redir);
		advance_token(tokens);
	}
	return (redir_list);
}

t_node	*parser_subshell(t_parsed_data **tokens)
{
	t_node		*child;
	t_node_type	type;

	type = token_type_to_node_type(peek_token_label(tokens));
	if (!peek_token(tokens) || type != NODE_SUBSHELL_START)
		return (NULL);
	advance_token(tokens);
	child = parser_or(tokens);
	if (!child)
		return (NULL);
	type = token_type_to_node_type(peek_token_label(tokens));
	if (!peek_token(tokens) || type != NODE_SUBSHELL_END)
	{
		free_ast(&child);
		return (NULL);
	}
	advance_token(tokens);
	return (create_subshell_node(child, attempt_redir(tokens)));
}
