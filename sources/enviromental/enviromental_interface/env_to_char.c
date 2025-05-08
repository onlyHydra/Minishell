/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:45:27 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 16:32:20 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "models/envir_struct.h"
#include <stdlib.h>

static int	count_env(t_env_var *var)
{
	int			count;
	t_env_var	*copy;

	count = 0;
	copy = var;
	while (copy)
	{
		if (copy->value != NULL)
			count++;
		copy = copy->next;
	}
	return (count);
}

char	**envp_to_char(t_env_var *var)
{
	int		count;
	char	**envp;
	char	*line;

	envp = malloc(sizeof(char *) * (count_env(var) + 1 ));
	count = 0;
	while (var)
	{
		if (var->value != NULL)
		{
			line = ft_strjoin(var->name, "=");
			envp[count] = line;
			line = ft_strjoin(envp[count], var->value);
			free(envp[count]);
			envp[count++] = line;
		}
		var = var->next;
	}
	envp[count] = NULL;
	return (envp);
}
