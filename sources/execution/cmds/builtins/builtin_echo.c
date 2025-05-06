/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/06 17:01:04 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
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
	int	i;

	suppress_newline = 0;
	i = 0;
	// Check for -n flags at the beginning
	while (args[i] && is_dash_n_flag(args[i]) == 0)
	{
		suppress_newline = 1;
		i++;
	}
	// Print remaining arguments
	while (args[i])
	{
		ft_putstr_fd(args[i], fds[1]);
		if (args[i + 1])
			ft_putstr_fd(" ", fds[1]);
		i++;
	}
	if (!suppress_newline)
		ft_putchar_fd('\n', fds[1]);
}

/**
 * Convert t_parsed_data to string array for echo command
 */
static char	**get_echo_args(t_parsed_data *data)
{
	int				i;
	int				count;
	char			**args;
	t_parsed_data	*current;

	count = 0;
	current = data;
	while (current && current->data)
	{
		count++;
		current++;
	}
	// Allocate memory for arguments array (excluding "echo" itself)
	args = (char **)malloc(sizeof(char *) * count);
	if (!args)
		return (NULL);
	i = 0;
	current = data + 1; // Skip "echo" command
	while (current && current->data && i < count - 1)
	{
		args[i] = current->data;
		current++;
		i++;
	}
	args[i] = NULL;
	return (args);
}

/**
 * Main echo command handler.
 */
int	builtin_echo(t_parsed_data *data, int fds[2])
{
	char	**args;

	// int		status;
	args = get_echo_args(data);
	if (!args)
		return (1);
	if (*args)
		print_echo_args(fds, args);
	else
		ft_putchar_fd('\n', fds[1]);
	free(args);
	return (0);
}
