/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:14:15 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 01:48:42 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "minishell.h"

/*
 * Checks if the given string consists only of '-n', '-nnn', etc.
 * Returns 0 if true, -1 otherwise.
 */
int	is_dash_n_flag(const char *arg)
{
	if (!arg || !*arg)
		return (-1);
	if (*arg != '-')
		return (-1);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (-1);
		arg++;
	}
	return (0);
}

/**
 * Prints the arguments for echo command.
 * Handles suppression of trailing newline with -n options.
 */
void	print_echo_args(int fds[2], char **args)
{
	int	suppress_newline;

	suppress_newline = 0;
	if (is_dash_n_flag(*args) == 0)
	{
		suppress_newline = 1;
		args++;
	}
	while (*args)
	{
		if (is_dash_n_flag(*args) == 0)
		{
			args++;
			continue;
		}
		ft_putstr_fd(*args, fds[1]);
		args++;
		if (*args)
			ft_putstr_fd(" ", fds[1]);
	}
	if (!suppress_newline)
		ft_putendl_fd("", fds[1]);
}

/**
 * Main echo command handler.
 */
// int	builtin_echo(t_cmd_node cmd_node, int fds[2])
// {
// 	char	**argv;
// 	char	**args;
// 	int		status;

// 	argv = list_to_argv(cmd_node.arguments, "");
// 	if (!argv)
// 		return (1);
// 	args = argv;
// 	args++; // skip "echo" itself
// 	status = 0;
// 	if (*args)
// 		print_echo_args(fds, args);
// 	else
// 		ft_putendl_fd("", fds[1]);
// 	free_char_array(argv);
// 	return (status);
// }

