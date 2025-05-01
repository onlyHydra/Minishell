/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/01 02:38:27 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tokener.h"

/**
 * Unusable because we need to completly match Operators aswel
 * Checks if a token is a built-in command that needs special handling
 * @param token: Command to check
 * @return: 1 if it's a built-in command, 0 if not
 */
int	is_builtin_command(char *data)
{
	int	siz_tok;

	siz_tok = ft_strlen(data);
	if (!data)
		return (0);
	if (ft_strncmp(data, "echo", siz_tok) == 0 || ft_strncmp(data, "cd",
			siz_tok) == 0 || ft_strncmp(data, "pwd", siz_tok) == 0
		|| ft_strncmp(data, "export", siz_tok) == 0 || ft_strncmp(data, "unset",
			siz_tok) == 0 || ft_strncmp(data, "env", siz_tok) == 0
		|| ft_strncmp(data, "exit", siz_tok) == 0)
	{
		return (1);
	}
	return (0);
}
