/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs_for.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:20:35 by schiper           #+#    #+#             */
/*   Updated: 2025/05/21 20:24:37 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"

void	apply_redirs_for(t_node *segm, t_exec_ctx *ctx)
{
	int	status;

	status = 0;
	if (segm->type == NODE_COMMAND)
		apply_redirections(segm->u_data.cmd->redir_list, ctx, &status);
	else if (segm->type == NODE_SUBSHELL)
		apply_all_subshell_redirs(segm->u_data.sub->child, ctx);
	if (status)
		status = 0;
}
