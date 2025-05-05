/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_cmd_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:03:27 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 19:48:35 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

t_node	*parser_command(t_parsed_data **tokens)
{
	t_cmd	*cmd;

	if (tokens == NULL || (*tokens)->data == NULL)
		return (NULL);
	cmd = build_command(tokens);
	if (cmd == NULL)
		return (NULL);
	return (create_command_node(cmd));
}
