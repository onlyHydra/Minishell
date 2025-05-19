/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_all_subshell_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:37:48 by schiper           #+#    #+#             */
/*   Updated: 2025/05/19 19:11:14 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"

void	apply_all_subshell_redirs(t_node *node, t_exec_ctx *ctx)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		apply_redirections(node->u_data.cmd->redir_list, ctx);
	else if (node->type == NODE_SUBSHELL)
		apply_all_subshell_redirs(node->u_data.sub->child, ctx);
	apply_all_subshell_redirs(node->left, ctx);
	apply_all_subshell_redirs(node->right, ctx);
}
