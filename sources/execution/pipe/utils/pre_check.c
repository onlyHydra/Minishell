/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:39:12 by schiper           #+#    #+#             */
/*   Updated: 2025/05/05 14:59:40 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	pre_check(t_node *node, t_exec_ctx *ctx, int pipe_flag)
{
	int	exit_code;

	exit_code = dfs_walk(node, ctx, pipe_flag);
	free_ast(&ctx->ast_root);
	free_parsed_data(ctx->parsed_data);
	return (exit_code);
}
