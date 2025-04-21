/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_node_creators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:16:21 by schiper           #+#    #+#             */
/*   Updated: 2025/04/21 15:08:32 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_functions.h"


/*For now Redirections are ignored*/
t_cmd	*build_command(t_parsed_data **tokens)
{
	t_cmd	*cmd;
    cmd = allocate_cmd();
	while (!is_operator_token(*tokens))
	{
		if ((*tokens)->token == CMD)
			add_argv(cmd, (*tokens)->data);
		advance_token(tokens);
	}
	return (cmd);
}

t_node *create_command_node(t_cmd *cmd)
{
    t_node *node;
    
}