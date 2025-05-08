/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:06:04 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 14:47:09 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error_message.h"
#include "libft.h"
#include <signal.h>

int	run_execve(char *filepath, char **argv, char **envp)
{
	int	error_code;

	error_code = 0;
	if (filepath == NULL || access(filepath, F_OK) == -1)
	{
		error_code = 127;
		print_execve_error( argv[0], error_code);
		return (error_code);
	}
	if (access(filepath, X_OK) == -1)
	{
		error_code = 126;
		print_execve_error(argv[0], error_code);
		return (error_code);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(filepath, argv, envp) == -1)
		error_code = 1;
	return (error_code);
}
