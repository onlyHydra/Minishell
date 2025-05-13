/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/13 15:12:56 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"

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
	int	i;
	int	first_non_flag;

	suppress_newline = 0;
	i = 0;
	first_non_flag = 0;
	// Process flags first
	while (args[i] && is_dash_n_flag(args[i]) == 0)
	{
		suppress_newline = 1;
		i++;
	}
	// Then print arguments
	while (args[i])
	{
		if (first_non_flag)
			ft_putstr_fd(" ", fds[1]);
		ft_putstr_fd(args[i], fds[1]);
		first_non_flag = 1;
		i++;
	}
	if (!suppress_newline)
		ft_putchar_fd('\n', fds[1]);
}

int	builtin_echo(char **args, int fds[2])
{
	if (!args)
		return (1);
	if (*args)
		print_echo_args(fds, args + 1);
	else
		ft_putchar_fd('\n', fds[1]);
	return (0);
}
