/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:41:45 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 01:45:20 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Handle env command
 */
int	cmd_env(t_env_var *env_vars)
{
	t_env_var	*current;

	current = env_vars;
	while (current)
	{
		if (current->exported && current->value && *current->value)
		{
			ft_putstr_fd(current->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		current = current->next;
	}
	return (0);
}
