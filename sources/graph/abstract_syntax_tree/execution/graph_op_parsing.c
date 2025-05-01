/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_op_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:04:52 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 18:03:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

t_node	*parser_or(t_parsed_data **tokens)
{
	t_node	*left;
	t_node	*right;
	t_node	*or_node;

	left = parser_and(tokens);
	if (left == NULL)
		return (NULL);
	while (peek_token(tokens)->token != NULL
		&& token_type_to_node_type(peek_token_label(tokens)) == NODE_OR)
	{
		advance_token(tokens);
		right = parser_and(tokens);
		if (right == NULL)
		{
			free_ast(left);
			return (NULL);
		}
		or_node = create_binary_node(NODE_OR, left, right);
		left = or_node;
	}
	return (left);
}

t_node	*parser_and(t_parsed_data **tokens)
{
	t_node	*left;
	t_node	*right;

	left = parser_pipe(tokens);
	if (left == NULL)
		return (NULL);
	while (peek_token(tokens)->token != NULL
		&& token_type_to_node_type(peek_token_label(tokens)) == NODE_AND)
	{
		advance_token(tokens);
		right = parser_pipe(tokens);
		if (right == NULL)
		{
			free_ast(left);
			return (NULL);
		}
		left = create_binary_node(NODE_AND, left, right);
	}
	return (left);
}

t_node	*parser_pipe(t_parsed_data **tokens)
{
	t_node	*left;
	t_node	*right;

	left = parser_primary(tokens);
	if (left == NULL)
		return (NULL);
	while (peek_token(tokens)->token != NULL
		&& token_type_to_node_type(peek_token_label(tokens)) == NODE_PIPE)
	{
		advance_token(tokens);
		right = parser_primary(tokens);
		if (right == NULL)
		{
			free_ast(left);
			return (NULL);
		}
		left = create_binary_node(NODE_PIPE, left, right);
	}
	return (left);
}
