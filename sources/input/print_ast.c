/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:46:42 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 21:49:30 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/abstract_syntax_tree.h"
#include "components/envir.h"
#include "components/execution.h"
#include "interfaces/envir_interface.h"
#include "signal_handler.h"

static void	check_should_exit(t_exec_ctx ctx, char ***env, int exit_code)
{
	if (ctx.should_exit == 1 && ctx.subshell_flag == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_args(*env);
		env = NULL;
		rl_clear_history();
		clear_history();
		exit(exit_code);
	}
}

int	print_ast(t_parsed_data *data, char ***env, int exit_status)
{
	int				exit_code;
	t_parsed_data	*copy;
	t_exec_ctx		ctx;

	ctx.should_exit = 0;
	ctx.subshell_flag = 0;
	copy = data;
	ctx.parsed_data = data;
	ctx.envp = init_env_vars(*env);
	ctx.ast_root = parse_expression(&copy);
	ctx.exit_status = exit_status;
	ctx.env = *env;
	syntax_check(copy, ctx.ast_root, &exit_code);
	if (exit_code != 258)
		exit_code = dfs_walk(ctx.ast_root, &ctx, 0);
	free_ast(&ctx.ast_root);
	free_parsed_data(ctx.parsed_data);
	if (ctx.should_exit == 0)
		update_envp(ctx.envp, env);
	free_env_vars(&ctx.envp);
	ctx.envp = NULL;
	check_should_exit(ctx, env, exit_code);
	return (exit_code);
}
