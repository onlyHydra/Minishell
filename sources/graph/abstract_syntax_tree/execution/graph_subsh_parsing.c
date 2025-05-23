/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_subsh_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:03:23 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 14:33:36 by iatilla-         ###   ########.fr       */
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
	return (create_subshell_node(child));
}
