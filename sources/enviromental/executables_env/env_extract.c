/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:32:27 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 01:00:20 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Extract variable name from input string
 */
char	*extract_var_name(const char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	name = (char *)malloc(i + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i + 1);
	return (name);
}
