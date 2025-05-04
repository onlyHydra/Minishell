/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs_for.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:20:35 by schiper           #+#    #+#             */
/*   Updated: 2025/05/04 22:13:13 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	apply_redirs_for(t_node *segm, t_exec_ctx *ctx)
{
	if (segm->type == NODE_COMMAND)
		apply_redirections(segm->u_data.cmd->redir_list);
	else if (segm->type == NODE_SUBSHELL)
		apply_all_subshell_redirs(segm->u_data.sub->child, ctx);
}
