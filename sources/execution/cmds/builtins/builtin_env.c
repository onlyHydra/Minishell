/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:41:45 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 15:03:13 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"
#include "libft.h"

/**
 * Handle env command - displays all exported environment variables
 */
int	cmd_env(t_env_var *env_vars)
{
	t_env_var	*current;

	if (!env_vars)
		return (1);
	current = env_vars;
	while (current)
	{
		if (current->exported && current->value)
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
