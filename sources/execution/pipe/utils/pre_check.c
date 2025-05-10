/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:39:12 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 14:24:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/execution.h"
#include "interfaces/token_interface.h"

int	pre_check(t_node *node, t_exec_ctx *ctx, int pipe_flag)
{
	int	exit_code;

	exit_code = dfs_walk(node, ctx, pipe_flag);
	free_ast(&ctx->ast_root);
	free_parsed_data(ctx->parsed_data);
	return (exit_code);
}
