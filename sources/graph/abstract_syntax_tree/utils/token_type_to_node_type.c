/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_to_node_type.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:32:31 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 18:48:54 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_syntax_tree.h"

t_node_type	token_type_to_node_type(const t_token_type *token_type)
{
	if (*token_type == CMD)
		return (NODE_COMMAND);
	else if (*token_type == AND)
		return (NODE_AND);
	else if (*token_type == OR)
		return (NODE_OR);
	else if (*token_type == PIPE)
		return (NODE_PIPE);
	return (NODE_UNKNOWN);
}
