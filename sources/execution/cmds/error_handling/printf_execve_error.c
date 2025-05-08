/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_execve_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:15:31 by schiper           #+#    #+#             */
/*   Updated: 2025/05/07 18:35:52 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	print_execve_error(const char *cmd, int error_code)
{
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 3);
	}
	if (error_code == 127)
		write(STDERR_FILENO, "command not found\n", 18);
	else if (error_code == 126)
		write(STDERR_FILENO, "permission denied\n", 18);
	else
		write(STDERR_FILENO, "execution error\n", 16);
}
